#include <arpa/inet.h>
#include <cstdio>
#include <sys/socket.h>
#include <sys/time.h>
#include <thread>
#include <unistd.h>

void thread_fun(int fildes){

	struct sockaddr_in from;
	socklen_t fromlen;
	char receive_packet[1];
	while(true){
		printf("receiving from\n");
		int answer = recvfrom(fildes, (void*)receive_packet, 1, 0, (struct sockaddr*)&from, &fromlen);
		printf("done receiving\n");
	}
}

int main(){

	printf("beginning program\n");
	

	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 100000;

	printf("creating socket\n");
	int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	// printf("setting socket options\n");
	// int result = setsockopt(s, SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(struct timeval));
	// printf("result is %d\n",result);
	// perror("at result");


	std::thread t1 = std::thread(thread_fun, s);

	usleep(2000000);

	timeout.tv_sec = 1;
	printf("setting socket options\n");
	int result = setsockopt(s, SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(struct timeval));
	printf("result is %d\n",result);
	// perror("at result");

	usleep(15000000);
	

	printf("done\n");
	return 0;
}


