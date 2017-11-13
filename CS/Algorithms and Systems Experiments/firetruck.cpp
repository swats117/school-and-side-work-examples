/* This was before I learned about DP, but essentially it was a routing
	algorithm for a fictional fire department */

#include <cstdio>
#include <stdio.h>
#include <string>
using namespace std;

template <typename T>
class stack{
private:
	int current;
	T internal_array[20];
public:
	stack():current(0){
		printf("\n");
	}

	void push(T element){
		if(current<20){
			internal_array[current]=element;
			current++;
		}
	}
	T pop(){
		if(current>0)
			return internal_array[--current+1];
		return (T)NULL;
	}
	void print_stack_contents(){
		// printf("path: ");
		if(current)
			printf("%s",to_string(internal_array[0]).c_str());
		for(int i=1; i<current; i++){
			printf(" %s",to_string(internal_array[i]).c_str());
		}
		printf("\n");
		
	}
};
class sll_link{
private:
	int value;
	sll_link* next;
public:
	sll_link(){
		next=NULL;
		value=-1;
	}
	sll_link(int value){
		next=NULL;
		this->value=value;
	}
	~sll_link(){
		if(next!=NULL){
			delete next;
		}
	}
	void set_next(sll_link* new_next){
		next=new_next;
	}
	sll_link* get_next(){
		return next;
	}
	int get_value(){
		return value;
	}
};
class sll{
private:
	sll_link* head;
	sll_link* current;
public:
	sll(){
		head=NULL;
		current=head;
	}
	sll_link* get_head(){
		return head;
	}
	void add_link(int value){
		sll_link* new_link = new sll_link(value);
		if(head==NULL){
			head=new_link;
			current=head;
		} else {
			current->set_next(new_link);
			current=new_link;

		}
		// printf("%d\n",current->get_value());
		
	}
	void print_sll(){
		sll_link* cur = head;
		while(cur){
			// printf("%d",cur->get_value());
			cur = cur->get_next();
		}
		// printf("\n");
	}
};
class sparse_graph{
private:
	sll* edge_lists[21];
public:
	sparse_graph(){
		for(int i=1; i<21;i++){
			edge_lists[i]=new sll();
		}
	}
	~sparse_graph(){
		for(int i=1; i<21; i++)
			delete edge_lists[i];
	}
	void add_edge(int a, int b){
		edge_lists[a]->add_link(b);
		edge_lists[b]->add_link(a);
		// printf("got through adding \n");
		edge_lists[a]->print_sll();
		edge_lists[b]->print_sll();
	}
	// returns an array of strings
	int solve_it(int destination){
		// printf("solving it\n");
		bool visited[21]={false};
		stack<int>* sofar = new stack<int>();
		int output = solve_it_recurse(1,destination,visited,sofar);
		delete sofar;

		return output;
	}
	int	solve_it_recurse(int start, int destination, bool* visited, stack<int>* sofar){
		if(start == destination){
			// printf("start is destination\n");
			sofar->push(start);
			sofar->print_stack_contents();
			sofar->pop();
			return 1;
		}
		// printf("in recursive, start:%d, destination:%d\n",start,destination);
		int valid_paths = 0;
		sll_link* current_link = edge_lists[start]->get_head();
		sofar->push(start);
		visited[start]=true;
		while(current_link){
			// printf("current link:(%d)\n",current_link->get_value());
			int value = current_link->get_value();
			if( visited[value] == false && value!=-1){
				
				valid_paths += solve_it_recurse(value, destination, visited, sofar);
				
			}
			current_link=current_link->get_next();
		}
		visited[start]=false;
		sofar->pop();

		return valid_paths;
	}
};



int main(){

	size_t k=0;
	char* line=NULL;

	int number;
	int fire_location_current = 0;
	int fire_location_next;
	int node_1;
	int node_2;
	sparse_graph* current_graph=NULL;
	int case_number=1;

	int bytes_recieved;
	while( (bytes_recieved = getline(&line, &k, stdin)) != -1){
		
		// If we recieve an edge, then make the edge in the graph.
		if( (number = sscanf(line,"%d %d\n",&node_1, &node_2)) == 2)
		{
			// printf("adding edge\n");
			if(node_1==0 && node_2==0){
				printf("CASE %d:",case_number);
				case_number++;
				int numpaths = current_graph->solve_it(fire_location_current);
				printf("There are %d routes from the firestation to streetcorner %d.\n",numpaths,fire_location_current);

				
				delete current_graph;
				current_graph = new sparse_graph();
			} else
			current_graph->add_edge(node_1,node_2);

		}  
		// If we recieve a new destination.
		else if ( (number = sscanf(line,"%d\n",&fire_location_next)) ==1 )
		{	// If we are just starting, we make a new graph.
			if(fire_location_current==0)
				current_graph = new sparse_graph();
			// If we are done, we delete the old graph and exit.
			else if(fire_location_next==0)
			{
				delete current_graph;
				break;
			} 
			fire_location_current = fire_location_next;
		}
	}
	// printf("done\n");


	return 0;
}
















