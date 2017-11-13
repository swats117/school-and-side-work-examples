
/*
	Author: Charles Swarts
	Date: 11/30/2017
	Title: Implementation of TCP connection functions.
*/

#ifndef __Connection_INCLUDED__
#define __Connection_INCLUDED__

#include "connection.h"

// int sendto(int sockfd, const void *msg, int len, unsigned int flags,
           // const struct sockaddr *to, socklen_t tolen);
// int recvfrom(int sockfd, void *buf, int len, unsigned int flags,
             // struct sockaddr *from, int *fromlen);

connection::connection(int fildes):
	fildes(fildes)
{
	/*
	Receive Buffer:
	      delivered     ACK_num    OOO_received_start
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |

	Send Buffer:
		  ACKed    	 SEQ_num     sendable_end
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |
	*/

	int micro_seconds = 200000;
	// interval.it_value.tv_sec = 0;
	// interval.it_value.tv_usec = micro_seconds;
	// setitimer(REAL_TIMER, &interval ,ONLY_ONCE);

	initialize_muxes_and_conds();

	err("creating a connection");
	fromlen = sizeof(struct sockaddr);
	

	// start out waiting for Syn	
	connection_state = 0;
	// in slow start
	congestion_state = 0;
	// we know the threshold, so we make ssthresh half of it.
	ssthresh = BUFFERSIZE/2;

	delivered = 0;
	
	ACKed = 0;
	send_ACK = false;
	timer_set = false;
	sendable_end = 0;


	// Is now actually the sequence number minus 1.
	SEQ_num = 0;
	ACK_num = 0;
	fwnd = BUFFERSIZE;
	cwnd = 1*MSS;

	duplicate_acks = 0;

	RTT.tv_sec = 1;
	RTT.tv_usec = 0;
	Deviation.tv_sec = 0;
	Deviation.tv_usec = 0;

	set_timer();// This is so UDP

// TODO: figure out how to use threads...
	transmitter = std::thread(&connection::transmit, this);
	receiver = std::thread(&connection::receive, this);
	err("Finished creating packet");
}


//			HELPER FUNCTIONS




void connection::connect(struct sockaddr_in to){
	from = to;
	_lock(&connection_state_mux);
		connection_state = 1;
		err("Sending Signal To Attempt Connect")
		_signal(&new_state);
	_unlock(&connection_state_mux);

	_lock(&connection_state_mux);
		while(connection_state!=4){
			err("havent connected yet")
			slow()
			_wait(&new_state,&connection_state_mux);
		}
	_unlock(&connection_state_mux);
	err("Connection Established")
}
void connection::close(){
//---------------Check If Connection Already Closed-------------------
	if(connection_state != 8){
//---------------Check If Connection Already Closed-------------------

//---------------Wait For All Data To Be Transmitted------------------
		while(get_sendable() != 0){
			_lock(&nothing_to_send_mux);
				_wait(&nothing_to_send,&nothing_to_send_mux);
			_unlock(&nothing_to_send_mux);
		}
//---------------Wait For All Data To Be Transmitted------------------

//---------------Initiate Closing Handshake Sequence------------------
		_lock(&connection_state_mux);
			connection_state = 5;
			err("Initiate Closing Handshake")
			_signal(&new_state);
		_unlock(&connection_state_mux);
//---------------Initiate Closing Handshake Sequence------------------

//----------------------Wake the Transmitter--------------------------
		_lock(&transmitter_wake_mux);
			err("Waking Transmitter to Close")
			_signal(&transmitter_wake_cond);
		_unlock(&transmitter_wake_mux);
//----------------------Wake the Transmitter--------------------------

//--------------Wait For Closing Handshake To Finish------------------
		_lock(&connection_state_mux);
			while(connection_state != 8){
				_wait(&new_state, &connection_state_mux);
			}
		_unlock(&connection_state_mux);
//--------------Wait For Closing Handshake To Finish------------------
	}
//------------------Join the Threads Gracefully-----------------------
	transmitter.join();
	receiver.join();
//------------------Join the Threads Gracefully-----------------------
	err("closed connection")
}


connection::~connection(){
	// pthread_mutex_destroy(pthread_mutex_t *mutex);

	pthread_mutex_destroy(&transmitter_wake_mux);
	pthread_mutex_destroy(&SEQ_num_mux);
	pthread_mutex_destroy(&delivered_mux);
	pthread_mutex_destroy(&resend_packet_mux);
	pthread_mutex_destroy(&send_ACK_mux);
	pthread_mutex_destroy(&fwnd_mux);
	pthread_mutex_destroy(&ACK_num_mux);
	pthread_mutex_destroy(&ACKed_mux);
	pthread_mutex_destroy(&connection_state_mux);
	pthread_mutex_destroy(&congestion_state_mux);
	pthread_mutex_destroy(&ssthresh_mux);
	pthread_mutex_destroy(&cwnd_mux);
	pthread_mutex_destroy(&receive_buf_full_mux);
	pthread_mutex_destroy(&nothing_deliverable_mux);
	pthread_mutex_destroy(&sendable_end_mux);
	pthread_mutex_destroy(&full_send_buf_mux);
	pthread_mutex_destroy(&nothing_to_send_mux);

	pthread_cond_destroy(&transmitter_wake_cond);
	pthread_cond_destroy(&new_state);
	pthread_cond_destroy(&receive_buf_full);
	pthread_cond_destroy(&nothing_deliverable);
	pthread_cond_destroy(&full_send_buf);
	pthread_cond_destroy(&nothing_to_send);

	err("destroyed connection")
}

void connection::initialize_muxes_and_conds(){

	transmitter_wake_mux = PTHREAD_MUTEX_INITIALIZER;
	SEQ_num_mux = PTHREAD_MUTEX_INITIALIZER;
	delivered_mux = PTHREAD_MUTEX_INITIALIZER;
	resend_packet_mux = PTHREAD_MUTEX_INITIALIZER;
	send_ACK_mux = PTHREAD_MUTEX_INITIALIZER;
	fwnd_mux = PTHREAD_MUTEX_INITIALIZER;
	ACK_num_mux = PTHREAD_MUTEX_INITIALIZER;
	ACKed_mux = PTHREAD_MUTEX_INITIALIZER;
	connection_state_mux = PTHREAD_MUTEX_INITIALIZER;
	congestion_state_mux = PTHREAD_MUTEX_INITIALIZER;
	ssthresh_mux = PTHREAD_MUTEX_INITIALIZER;
	cwnd_mux = PTHREAD_MUTEX_INITIALIZER;
	receive_buf_full_mux = PTHREAD_MUTEX_INITIALIZER;
	nothing_deliverable_mux = PTHREAD_MUTEX_INITIALIZER;
	sendable_end_mux = PTHREAD_MUTEX_INITIALIZER;
	full_send_buf_mux = PTHREAD_MUTEX_INITIALIZER;
	nothing_to_send_mux = PTHREAD_MUTEX_INITIALIZER;

	transmitter_wake_cond = PTHREAD_COND_INITIALIZER;
	new_state = PTHREAD_COND_INITIALIZER;
	receive_buf_full = PTHREAD_COND_INITIALIZER;
	nothing_deliverable = PTHREAD_COND_INITIALIZER;
	full_send_buf = PTHREAD_COND_INITIALIZER;
	nothing_to_send = PTHREAD_COND_INITIALIZER;

	err("initialized muxes and conds")
}

#endif
