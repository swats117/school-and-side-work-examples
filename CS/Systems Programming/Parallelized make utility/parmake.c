/**
 * Parallel Make
 * CS 241 - Fall 2016
 * author: Charles Swarts
 * note: written well before Trump was president. extreme_vetting is a less humourous name now. :(
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

#include "parmake.h"
#include "queue.h"
#include "vector.h"
#include "rule.h"
#include "parser.h"

void startup(int argc, char** argv, int* numThreads, char** makefile);
void targetListMaker();
void extreme_vetting(rule_t* target);
void init_hist_werk_list();
void* copy_constructor(void* elem){return elem;}
void  destructor(void* elem){ /*void* temp = elem; (*((int*)temp))--;*/ return;}
int figureOutWhatToDo(rule_t* currentRule);
void rule_destructor(void* rule);
void run_commands(rule_t* currentRule);
void decrement_totalRulesRemaining();

queue_t* werkQueue; 
Vector* history;
Vector* targetList;
size_t totalRulesRemaining;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
	
/* 	Essential notes on program:
	Each rule has a state. The states each rule can be in are

	-1 := failed
	 0 := not vetted
	 1 := vetted
	 2 := sucessfully done and name of file
	 3 := sucessfully done and regular rule
	
	typedef struct {
  	char *target;         // Name of target
  	Vector *dependencies; // Vector of pointers to rules
  	Vector *commands;     // Vector of pointers to char arrays
  	int state;            // State of the rule. Defaults to 0
	} rule_t;

	// Return Value of figureOurWhatToDo.
 	// -1 := Don't run the commands, and draw again.
  	//  0 := Don't run the commands. State is already set to -1.
  	//  1 := Don't run the commands, and set state to 2.
  	//  2 := Run the commands and set state to 2
  	//  3 := Run the commands and set state to 3
*/
void* werkWerkWerkWerkWerk(void* threadID)
{
	(*((int*)threadID))++;
	// printf("\nI am thread %d, starting up\n", (*((int*)threadID)));
	// sleep(20);
	rule_t* currentRule;
	while( (currentRule = ((rule_t*)queue_pull(werkQueue))) )
	{	// sleep(1);
		// printf("\nT_ID: %d, working on rule: %s\n", (*((int*)threadID)), currentRule->target);
		int whatDo = figureOutWhatToDo(currentRule);

		switch(whatDo)
		{
			case -1:
				queue_push(werkQueue, currentRule);
				break;
			case  0:
				decrement_totalRulesRemaining();
				break;
			case  1:
				currentRule->state = 2;
				decrement_totalRulesRemaining();
				break;
			case  2:
				run_commands(currentRule);
				currentRule->state = ((currentRule->state==-1) ? -1 : 2);
				decrement_totalRulesRemaining();
				break;
			case  3:
				run_commands(currentRule);
				currentRule->state = ((currentRule->state==-1) ? -1 : 3);
				decrement_totalRulesRemaining();
				break;
		}
	}
	// printf("\nI, thread %d, am done\n", (*((int*)threadID)));
	return threadID;
}
// Treat this as main
int parmake(int argc, char **argv) 
{
	int numThreads = 1;
	char* makefile = NULL;
	startup(argc, argv, &numThreads, &makefile);
	init_hist_werk_list();
	// puts("\nMade it past startup");

	pthread_t thread[numThreads];
	for(int i=0; i<numThreads; i++)
	{
		int* id = malloc(sizeof(int));
		*(id) = i;
		pthread_create(&thread[i], NULL, werkWerkWerkWerkWerk, id);
	}
	// puts("\nStarted up the threads");
	// puts("\nInitialiezed history, werkList, and targetList");

	parser_parse_makefile(makefile, argv+optind, targetListMaker);

	// puts("\nParsed the makefile");

	pthread_mutex_lock(&mutex);
	while(totalRulesRemaining)
	{
		pthread_cond_wait(&cv, &mutex);
	}
	pthread_mutex_unlock(&mutex);

	for(int i=0; i<numThreads; i++)
	{
		queue_push(werkQueue, NULL);
	}

	for(int i=0; i<numThreads; i++)
	{
		void* status;
		pthread_join(thread[i], &status);
		// printf("\nFrom thread %d, came status %d\n", i, *((int*)status) );
		free(status);
	}
	// puts("Destroying the targetList");
	Vector_destroy(targetList);
	Vector_destroy(history);
	queue_destroy(werkQueue);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cv);

	return 0;
}
/* 	This function impliments a decision tree 
   
	IF any of the dependencies failed, fail the rule and return 0.
	IF any of the dependencies was not met, return -1.

	IF the rule is a non-file, mark as satified non-file and return 1.

	IF there are no dependencies, mark as satisfied file-rule return 0.

	IF there are dependencies{
	IF any of the dependencies is a non-file rule, return 1.
	ELSE IF any of the dependencies is has a newer modification time, return 1.
	ELSE return 0;}

   	Return Value
	
	 -1 := Don't run the commands, and draw again.
   	  0 := Don't run the commands. State is already set to -1.
   	  1 := Don't run the commands, and set state to 2.
   	  2 := Run the commands and set state to 2
   	  3 := Run the commands and set state to 3
   	 
*/
int figureOutWhatToDo(rule_t* currentRule)
{
	int AtLst1_normal_rule_flag=0;

	Vector* dependencies = currentRule->dependencies;

	size_t size = Vector_size(dependencies);
	for(size_t i=0; i<size; i++)
	{
		rule_t* dependency_i = Vector_get(dependencies, i);
		if(dependency_i->state == -1)  
		{
			currentRule->state = -1;
			return 0;
		}
		else if(dependency_i->state == 1)
		{
			return -1;
		}
		if(dependency_i->state == 3)
			AtLst1_normal_rule_flag=1;
	}
	if(access(currentRule->target,F_OK))
		return 3;

	if( !size  ) 
		return 1;

	if(AtLst1_normal_rule_flag)
		return 2;

	struct stat* status= (struct stat*)malloc(sizeof(struct stat));
	if(!stat(currentRule->target, status))
	{
		time_t current_mod_time = status->st_mtime;
	
		for(size_t i=0; i<size; i++)
		{
			rule_t* dependency_i = Vector_get(dependencies, i);

			if(!stat((dependency_i->target), status))
			{
				if( (difftime(current_mod_time, status->st_mtime)) <= 0 )
				{	
					free(status);
					return 2;
				}
			}
			else
				perror("figureOutWhatToDo");
		}
	}
	else
		perror("figureOutWhatToDo");
	free(status);
	return 1;
}
void targetListMaker(rule_t* target)
{// void Vector_append(Vector *vector, void *elem);
	// puts("targetListMaker was called");
	// printf("target is %p\n", target);
	// printf("target is %s\n", target->target);

	Vector_append(targetList, target);
	// puts("appended properly");
	extreme_vetting(target);
}
// typedef struct {
//   char *target;         // Name of target
//   Vector *dependencies; // Vector of pointers to rules
//   Vector *commands;     // Vector of pointers to char arrays
//   int state;            // State of the rule. Defaults to 0
// } rule_t;

//This is a recursive call.

//Base Case: we have no dependencies.
//We're vetted, set state to one, put ourself on the queue and return.

//Base Case: we have been visited before.
//Then we just return, because we were already handled.

//Recursive Case: we have dependencies.
//If there is a history, we check it for ourself.{
//If we see ourself in the history, then there is a circular dependence.
//So we already appeared and considered our dependencies.
//So we cut it short by marking ourself a failure
//(setting the state to -1) and returning.}
//
//Otherwise we add ourself to the history.
//We recursively call each dependency which hasn't been vetted.
//Afterward, we review each dependency.
//If one of them failed, then we failed. (Circular dependency failure)
//If we failed, we set the state to -1.
//Else we set the state to 1. (1 indicates vetted.)
//Since we were vetted, we go on the queue.
//totalRules gets incremented since there is a new rule.
//Since we are going back in time we remove ourself from history.

void extreme_vetting(rule_t* target)
{
	// puts("\npracticing extreme_vetting, it's the only way");
	// printf("Working on %s\n", target->target);
	// sleep(1);
	if(!target->state)
	{

		size_t size = Vector_size(target->dependencies);
		if(!size)
		{
			// puts("independent rule");
			target->state = 1;
			pthread_mutex_lock(&mutex);
			totalRulesRemaining++;
			pthread_mutex_unlock(&mutex);
			queue_push(werkQueue, target);
			return;
		}
		size_t recorded_time = Vector_size(history);
		// printf("History: ");
		for(size_t i=0; i<recorded_time; i++)
		{
			// printf(" %s, ",((rule_t*)Vector_get(history, i))->target);
			if(Vector_get(history, i) == target)
			{
				target->state = -1;
				return;
			}
		}
		// puts(".");
		Vector_append(history, target);

		// printf("Has dependencies: ");
		// for(size_t i=0; i<size; i++)
		// {
		// 	rule_t* dependency_i = Vector_get(target->dependencies,i);
		// 	printf(" %s, ", dependency_i->target);
		// }
		// puts(".");

		for(size_t i=0; i<size; i++)
		{
			rule_t* dependency_i = Vector_get(target->dependencies,i);
			
			if(dependency_i->state ==  0)
				extreme_vetting(dependency_i);
			if(dependency_i->state == -1)
				target->state = -1;
		}
		if(target->state != -1)
		{
			target->state = 1;
			pthread_mutex_lock(&mutex);
			totalRulesRemaining++;
			pthread_mutex_unlock(&mutex);
			queue_push(werkQueue, target);
		}
		Vector_delete(history, recorded_time);
		return;
	}
	else
		return;
}

void startup(int argc, char** argv, int* numThreads, char** makefile)
{
	int optout;
	opterr = 0;
	while( (optout = getopt(argc, argv, "f:j:")) != -1)
	{
		switch(optout)
		{
			case 'f':
				(*makefile) = optarg;
				break;
			case 'j':
				if( 0 == sscanf(optarg, "%d", numThreads) )
				{
					puts("NAN error");
				}
				break;
			default /*'?'*/:
				puts("invalid option");
				break;
		}
	}
	// Try to find default makefile.
	if(!(*makefile))
	{
		if( access("makefile",F_OK) )
		{
			if( access("Makefile",F_OK) ) 
				puts("error no makefile");
			else
				(*makefile) = "makefile";
		}
		else
			(*makefile) = "Makefile";
	}
	// Make sure given makefine is ok.
	else if( access((*makefile),F_OK) )
	{	
		puts("makefile name invalid");
	}
}

void rule_destructor(void* rule)
{
	// puts("\nrule_destructor was called");

	if(rule)
	{
		free(((rule_t*)rule)->target); // Can free null :)
		if(((rule_t*)rule)->dependencies)
	  	Vector_destroy(((rule_t*)rule)->dependencies);
	  	if(((rule_t*)rule)->commands)
	  	Vector_destroy(((rule_t*)rule)->commands);
		free((rule_t*)rule);
	}
}

void init_hist_werk_list()
{
	//Vector* Vector_create(copy_constructor_type c, destructor_type d);
	targetList = Vector_create(copy_constructor, rule_destructor);
	history = Vector_create(copy_constructor, destructor);
	//queue_t *queue_create(int maxSize, copy_constructor_type c, destructor_type d);
	werkQueue = queue_create(64, copy_constructor, destructor);
}

void run_commands(rule_t* currentRule)
{
	Vector* commands = currentRule->commands;
	size_t size = Vector_size(commands);
	char* command_i;
	for(size_t i=0; i<size; i++)
	{
		command_i = Vector_get(commands, i);
		
		if( system(command_i) != 0 )
		{
			currentRule->state = -1;
			break;
		}
	}
}

void decrement_totalRulesRemaining()
{
 	pthread_mutex_lock(&mutex);
	totalRulesRemaining--;
	if(!totalRulesRemaining)
		pthread_cond_signal(&cv);
	pthread_mutex_unlock(&mutex);	
}

// void helper_Vector_delete(Vector *v, size_t ind, const char *func) {
// 	printf("Vector delete called by %s\n", func);
// 	Vector_delete(v, ind);
// }





