/*
	Author: Charles Swarts
	Date: 11/30/2017
	Title: Implementation of TCP connection variables and function signatures.
*/

#ifndef __X_H_INCLUDED__   // if x.h hasn't been included yet...
#define __X_H_INCLUDED__   //   #define this so the compiler knows it has been included



#include <arpa/inet.h>
#include <cstdio>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <thread>
#include <time.h>
#include <unistd.h>
#define ALPHA .875
#define BETA .75
#define PACKET_SIZE 4032
#define MSS 3928
#define BUFFERSIZE 0x100000 // approximately equals .04s * 4MB/s
#define BUFFERMASK 0xfffff
#define REAL_TIMER 0
#define ONLY_ONCE NULL
#define _NONE 'A'
#define _SYN 'B'
#define _SYN_ACK 'C'
#define _ACK 'D'
#define _FIN 'E'
#define _FIN_ACK 'F'
#define int_abs(a) ((a>>31)^a)-(a>>31)
#define _lock(a) pthread_mutex_lock(a)
#define _unlock(a) pthread_mutex_unlock(a)
#define _wait(a,b) pthread_cond_wait(a,b)
#define _signal(a) pthread_cond_signal(a)
#define _broadcast(a) pthread_cond_broadcast(a)
#define min(a,b) (a<b?a:b)

// #define ___DEBUG_MODE__
#ifdef ___DEBUG_MODE__
#define err(x) fprintf(stderr,"%s\n",x);
#define pre_err(x) fprintf(stderr,"%s: ",x);
#define int_err(m,x) fprintf(stderr,"%s: %d\n",m,x);
#define char_err(m,x) fprintf(stderr,"%s: %c\n",m,x);
#define slow() usleep(200000);
#else
#define err(x)
#define pre_err(x)
#define int_err(m,x)
#define char_err(m,x)
#define slow()
#endif

typedef unsigned int uint;
int ring_buffer_distance(int a, int b){
	// a is thing in the front.
	// b is thing in the back.
	// if b is allowed to become a the output is fine.
	// is b is not allowed to become a then subtract
	// 1 from the output and bitwise AND with BUFFERMASK.
	return ( (a-b+BUFFERSIZE) & (BUFFERMASK) );
}

using namespace std;


class connection{
public:
	// The file descriptor for UDP sendto and receivefrom.
	const int fildes;
	// used to for sendto and receivefrom.
	struct sockaddr_in from;
	socklen_t fromlen;
	// Normally we need a coordinate for this connection (src_ip, dest_ip, src_port, dest_port)
	// Our connection doesn't need coordinate because only one connection.

	std::thread transmitter;
	std::thread receiver;

	//TRANSMITTER AND EVERYONE
	// Basically any time you want to wake the transmitter, you have to
	// aquire this mux and signal this condition variable.
	pthread_mutex_t transmitter_wake_mux;
	pthread_cond_t transmitter_wake_cond;

	//TRANSMITTER
	/*
	      ACKed        SEQ_num    sendable_end
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |
	*/
	char send_packet[PACKET_SIZE];
	uint SEQ_num; pthread_mutex_t SEQ_num_mux; // The sequence number of the last packet Alice sent.
	// int sent; // sent = SEQ_num & BUFFERMASK
	

	//RECEIVER
	/*
	      delivered     ACK_num    OOO_received_start
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |
	*/
	char receive_packet[PACKET_SIZE];
	int duplicate_acks;
	int delivered; pthread_mutex_t delivered_mux;
	
	
	// int received;

	//TRANSMITTER AND RECEIVER
	
	bool resend_packet; pthread_mutex_t resend_packet_mux;
	bool send_ACK; pthread_mutex_t send_ACK_mux;// Used to signal transmitter to send a blank message with an ack if it has to.
	bool timer_set;
	// This is the flow control window size of Bob. It's equation is 
	// fwnd = last ACK fwnd - (sent - ACK_num from their last packet)
	// Initially it is the bufferSize. It updates every time we send a packet.

	// This is the number of packets we can have in flight at one time based on the 
	// capacity of Bob. It is updated every time a new message comes in.
	int fwnd; pthread_mutex_t fwnd_mux;

	uint timed_SEQ_num; // doesn't need a mux because of timing
	uint ACK_num; pthread_mutex_t ACK_num_mux; // The sequence number of Bob's last packet Alice acknowledged.
	uint ACKed; pthread_mutex_t ACKed_mux;// The sequence number of Alice's last packet Bob acknowledged.

	//TRANSMITTER RECEIVER TIMER_HANDLER

	// #  sends  	receives 	next
	// 0  nothing	syn  		2
	// 1  syn		syn_ack  	3 
	// 2  syn_ack	ack  	 	4
	// 3  ack		data 	  	4
	// 4  data		fin 		6
	// 5  fin		fin_ack  	7
	// 6  fin_ack	ack 		8
	// 7  ack		nothing 	8
	// 8  closed		
	int connection_state; pthread_mutex_t connection_state_mux;
	pthread_cond_t new_state;

	// Finally, these variables are stored to keep track of errors and congestion.

	// 0 for slow start 1 for Congestion Avoidance 2 for Fast Recovery
	int congestion_state; pthread_mutex_t congestion_state_mux;
	// recorded in #MSS.
	int ssthresh; pthread_mutex_t ssthresh_mux;

	// This is how many packets we have in flight at one time based on network congestion.
	int cwnd; pthread_mutex_t cwnd_mux;
	
	struct timeval RTT_begin;
	struct timeval RTT_end;
	struct timeval RTT;
	struct timeval Deviation;
	struct itimerval interval;

	//USER and RECEIVER

	/*
	      delivered    ACK_num    OOO_received_start
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |
	*/

	pthread_mutex_t receive_buf_full_mux, nothing_deliverable_mux;
	pthread_cond_t receive_buf_full, nothing_deliverable;
	char receive_buffer[BUFFERSIZE];

	// Out Of Order receive is used because really we can only keep track of one out of one gap.
	int OOO_received_start; 
	int OOO_received_length; 
	bool OOO_segment; 	
	//USER and TRANSMITTER
	
	/*
	      ACKed        SEQ_num    sendable_end
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |
	*/

	
	int sendable_end; pthread_mutex_t sendable_end_mux;
	char send_buffer[BUFFERSIZE];
	// Used to signal user if send buffer is full or transmitter if send buffer is empty.
	pthread_mutex_t full_send_buf_mux, nothing_to_send_mux;
	pthread_cond_t full_send_buf, nothing_to_send;
	
	
//			INTERFACE	
	connection(int fildes);
	~connection();

	void connect(struct sockaddr_in to);
	void close();
	// The user program can call send and deliver.
	// All send does is copy the data from the user to the send buffer.
	int send(char* buffer, int bytes);
	// All deliver does is copy any deliverable data from the receive buffer to the user.
	// Returns 0 if the connection is closed otherwise returns number of bytes put into buffer.
	int deliver(char* buffer, int max_bytes);


//			INTERNAL OPERATIONS

	// A thread will manage each of the receiving and transmitting of data.
	void transmit(); 
		void transmit_packet(int sendable);
		void retransmit_packet();
		void fill_packet(int start, int length);
		void emit(char flag, int bytes);

	void receive();//receive sends signals to transmit for acks and retransmisions.
		void handle_recvd_packet(int bytes_received);
	// This is a SIGALRM signal handler;
	void handle_timer();

	

	// And finally these are used to recalculate and set the timeout
	void update_RTT_estimates();
	void timer_logic(int sequence_number);
	void set_timer();
	void double_RTT();
	int get_receive_buf_cap();
	int get_send_buf_cap();
	int get_sendable();
	int get_deliverable();


	void initialize_muxes_and_conds();
};

#endif 

#include "Receiver_Functions.cpp"
#include "Transmitter_Functions.cpp"
#include "connection.cpp"
