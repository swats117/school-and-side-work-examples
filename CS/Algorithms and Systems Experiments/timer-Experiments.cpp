#include <cstdio>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#define REAL_TIMER 0
#define ONLY_ONCE NULL



struct itimerval interval;
struct timeval RTT_begin, RTT_end;

class timerHandler{
public:

	time_t currentTime;

	timerHandler();

	void handleAlarm(int signal){
		gettimeofday(&RTT_end,NULL);
		int elapsed_seconds = RTT_end.tv_sec - RTT_begin.tv_sec;
		int elapsed_micro_seconds = RTT_end.tv_usec - RTT_begin.tv_usec;

		printf("Current Time is %s", ctime(&currentTime));
		printf("elapsed seconds: %d, elapsed micro_seconds: %d\n",elapsed_seconds, elapsed_micro_seconds);
	}

};
timerHandler* signal_object;

timerHandler::timerHandler(){
	time(&currentTime);
	signal_object = this;
}

void mySignal(int signal){
	signal_object->handleAlarm(signal);
	exit(1);
}


int main(){

	timerHandler Bob;

	signal(SIGALRM,mySignal);
	
	// struct itimerval interval, RTT_begin, RTT_end;

	int micro_seconds = 200000;
	interval.it_value.tv_sec = 0;
	interval.it_value.tv_usec = micro_seconds;
	setitimer(REAL_TIMER, &interval ,ONLY_ONCE);

	
	gettimeofday(&RTT_begin,NULL);

	printf("Current Time is %s\n", ctime(&Bob.currentTime));
	while(true);
	return 0;
}


