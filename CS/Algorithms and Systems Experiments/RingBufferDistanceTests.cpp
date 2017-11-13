#include <cstdio>
#define BUFFERSIZE 0x100000 // approximately equals .04s * 4MB/s
#define BUFFERMASK 0xfffff

int ring_buffer_distance(int a, int b){
	int output;
	if(a==b){
		output = BUFFERSIZE;
	}
	( (a-b+BUFFERSIZE) & (BUFFERMASK) );
	return 
}

int main(){

	int ACKed = -1 & BUFFERMASK;
	int sendable_end = 0;
	printf("ACKed: %d\n",ACKed);
	printf("sendable_end: %d\n",sendable_end);

	int result = ring_buffer_distance(ACKed, sendable_end);

	printf("ring buffer distance%d\n", result);
	return 0;
}






















