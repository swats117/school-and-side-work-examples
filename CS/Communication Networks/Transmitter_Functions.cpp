#ifndef __Transmitter_INCLUDED__
#define __Transmitter_INCLUDED__
#include "connection.h"

void connection::transmit(){
	err("in transmit");
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
//-----------------------Initial handshake----------------------------
	_lock(&connection_state_mux);
		while( connection_state == 0 ){
			_wait(&new_state,&connection_state_mux);
			int_err("new_state",connection_state);
			slow()
		}
		while( connection_state == 1 ){
			int_err("new_state",connection_state);
			err("SYN Emitted");
			emit(_SYN,0);
			timer_logic(SEQ_num+0);
			pthread_cond_wait(&new_state,&connection_state_mux);
		}
		while( connection_state == 2 ){
			err("SYN_ACK Emitted");
			emit(_SYN_ACK,0);
			timer_logic(SEQ_num+0);
			_wait(&new_state,&connection_state_mux);
		}
		while( connection_state == 3 ){
			err("ACK Emitted (1)");
			emit(_ACK,0);
			timer_logic(SEQ_num+0);
			_wait(&new_state,&connection_state_mux);
		}
	_unlock(&connection_state_mux);
//-----------------------Initial handshake----------------------------





//-------------------------Data Transfer------------------------------{
		while(true){
			err("entering data transfer loop")
			_lock(&connection_state_mux);
				int_err("connection_state",connection_state)
				if(connection_state != 4){
					_unlock(&connection_state_mux);
					break;
				}
			_unlock(&connection_state_mux);
			err("still transfering data")
			int sendable;
//------------Wait For Data or ACK or Retransmit or Fin---------------
			_lock(&transmitter_wake_mux);
				while( ((sendable = get_sendable())==0) &&
						(resend_packet==false) && 
						(send_ACK==false) && 
						(connection_state==4))
				{
					if(sendable == 0){
						_lock(&nothing_to_send_mux);
							_signal(&nothing_to_send);
						_unlock(&nothing_to_send_mux);
					}
					err("waiting for data or retransmit or fin")
					_wait(&transmitter_wake_cond,&transmitter_wake_mux);
					err("transmitter woken")
				}
			_unlock(&transmitter_wake_mux);
//------------Wait For Data or ACK or Retransmit or Fin---------------

//---------------------Handle Retransmission--------------------------
			if(resend_packet==true){
				err("retransmitting packet")
				retransmit_packet();
			}
//---------------------Handle Retransmission--------------------------

//--------------------------Send Data---------------------------------
			if( (sendable>0) || (send_ACK==true) ){
				err("transmitting packet")
				transmit_packet(sendable);
				send_ACK=false;
			}
//--------------------------Send Data---------------------------------

		} err("Done Sending Data, Beginning terminal handshake")
//-------------------------Data Transfer------------------------------}

		int_err("connection_state",connection_state)
//----------------------terminal handshake----------------------------
		_lock(&connection_state_mux);
			while(connection_state == 5 ){
				err("FIN Emitted")
				emit(_FIN,0);
				_wait(&new_state,&connection_state_mux);
			}
			while(connection_state == 6 ){
				err("FIN_ACK Emitted")
				emit(_FIN_ACK,0);
				_wait(&new_state,&connection_state_mux);
			}
			while(connection_state == 7 ){
				err("ACK Emitted")
				emit(_ACK,0);
				_wait(&new_state,&connection_state_mux);
			}
		_unlock(&connection_state_mux);
//----------------------terminal handshake----------------------------
		err("Done with transmit")
}

int connection::send(char* buffer, int bytes){
	err("Sending bytes")

//-------------------Check Connection is Open-------------------------
	_lock(&connection_state_mux);
		if(connection_state!=4){
			_unlock(&connection_state_mux);
			return -3;
		}
	_unlock(&connection_state_mux);	
//-------------------Check Connection is Open-------------------------

	err("Connection is still open")

//------------------------adjust bytes--------------------------------
	if(bytes > MSS){
		bytes = MSS;
	}
//------------------------adjust bytes--------------------------------

//-----------------check send_buffer has capacity---------------------
	int send_buf_cap;
	while( ( send_buf_cap = get_send_buf_cap() ) - bytes < 0){
		int_err("send_buf_cap",send_buf_cap)
		_lock(&full_send_buf_mux);
			_wait(&full_send_buf,&full_send_buf_mux);
		_unlock(&full_send_buf_mux);
	}
//-----------------check send_buffer has capacity---------------------
	
	err("Beginning to Fill Buffer")

//-------------------------fill buffer--------------------------------
	_lock(&sendable_end_mux);
		for(int i=0; i<bytes; i++){
			int_err("Location in send buffer",(sendable_end+i+1)&(BUFFERMASK))
			char_err("Character",buffer[i])
			send_buffer[(sendable_end+i+1)&(BUFFERMASK)] = buffer[i];
		}
		sendable_end += bytes;
		sendable_end &= (BUFFERMASK);
	_unlock(&sendable_end_mux);
//-------------------------fill buffer--------------------------------
	
	err("User Signalling Transmitter that Buffer has Contents")

//---------------------signal transmitter-----------------------------
	_lock(&transmitter_wake_mux);
		err("Signal Tranmitter to Wake up")
		_signal(&transmitter_wake_cond);
	_unlock(&transmitter_wake_mux);
//---------------------signal transmitter-----------------------------

	err("exit send call")
	return bytes;
}

void connection::transmit_packet(int sendable){
	err("Transmitting Packet")
	/*
	Receive Buffer:
	      delivered   ACK_num    OOO_received_start
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |

	Send Buffer:
		  ACKed    	 SEQ_num     sendable_end
	        |           |           |
	    	V           V           V
	| | | | | | | | | | | | | | | | | | | | | | | | | | | |
	*/
//---------------Calculate How Much Data Can Be Sent------------------
	int packets_in_flight = ring_buffer_distance( (SEQ_num&BUFFERMASK), ACKed);
	int bound = min(fwnd, cwnd) - packets_in_flight;
		bound = min(bound, MSS);
	int length = min(bound,sendable);
//---------------Calculate How Much Data Can Be Sent------------------

//---------------------Create and Send Packet-------------------------
	fill_packet( ( (SEQ_num+1) & BUFFERMASK), length);
	emit(_NONE, length);
//---------------------Create and Send Packet-------------------------


//--------------------Update Sequence Number--------------------------{
	_lock(&SEQ_num_mux);
		SEQ_num += length;
//--------------------------Set Timer---------------------------------
		timer_logic(SEQ_num);
//--------------------------Set Timer---------------------------------
	_unlock(&SEQ_num_mux);
//--------------------Update Sequence Number--------------------------}
	err("Done Transmitting Packet")
}

void connection::timer_logic(int sequence_number){
	err("entered timer_logic")
	if(timer_set==false){
		err("resetting timer")
		timed_SEQ_num = sequence_number;
		set_timer();
		timer_set = true;
	}
	err("exited timer_logic")
}
void connection::set_timer(){

//-------------------Calculate How long to wait-----------------------
	interval.it_value.tv_sec = RTT.tv_sec + 4 * Deviation.tv_sec;
	interval.it_value.tv_usec = RTT.tv_usec + 4 * Deviation.tv_usec;
//-------------------Calculate How long to wait-----------------------

//----------------Set timeout value for the socket.-------------------
	setsockopt(fildes,SOL_SOCKET,SO_RCVTIMEO,&interval.it_value,sizeof(struct timeval));
//----------------Set timeout value for the socket.-------------------

	int_err("interval seconds",interval.it_value.tv_sec)
	int_err("interval microseconds",interval.it_value.tv_usec)

//-------------Record Time When Packet is Transmitted-----------------
	gettimeofday(&RTT_begin,NULL);
//-------------Record Time When Packet is Transmitted-----------------
	err("set the timer")

}

int connection::get_send_buf_cap(){
	int output;
	_lock(&ACKed_mux);
	_lock(&sendable_end_mux);
		int_err("ACKed",ACKed)
		int_err("sendable_end",sendable_end)
		output = ring_buffer_distance(ACKed, sendable_end);
	_unlock(&sendable_end_mux);
	_unlock(&ACKed_mux);

	output = (output-1) & BUFFERMASK;

	int_err("calculated send buffer capacity",output)
	return output;
}
int connection::get_sendable(){
	int output;
	_lock(&sendable_end_mux);
	_lock(&SEQ_num_mux);
		int_err("sendable_end",sendable_end)
		int_err("SEQ_num",SEQ_num)
		output = ring_buffer_distance(sendable_end, SEQ_num);
	_unlock(&SEQ_num_mux);
	_unlock(&sendable_end_mux);

	int_err("calculated sendable bytes",output)
	return output;
}

void connection::fill_packet(int start, int length){
	slow()
	err("filling packet")
	int_err("sequence_number",start)
	for(int i=0; i<length; i++){
		char_err("character: ",send_buffer[( (start+i) & (BUFFERMASK) )])
		send_packet[i+13] = send_buffer[( (start+i) & (BUFFERMASK) )];
	}
	err("filled packet")
}



void connection::retransmit_packet(){
	int distance = ring_buffer_distance((SEQ_num&BUFFERMASK),ACKed);
	fill_packet(ACKed+1,min(distance,MSS));
	*((int*)(&send_packet[0])) = htonl(SEQ_num-distance);
	*((int*)(&send_packet[4])) = htonl(ACK_num);
	_lock(&fwnd_mux);
		*((int*)(&send_packet[8])) = htonl(fwnd);
	_unlock(&fwnd_mux);
	*(&send_packet[12]) = _NONE;

	uint size = min(distance,MSS) + 13;
	sendto(fildes, (void *) send_packet, size, 0, (struct sockaddr*)&from, fromlen);
	err("retransmitted packet")
}


void connection::emit(char flag, int bytes){
	*((int*)(&send_packet[0])) = htonl(SEQ_num);
	*((int*)(&send_packet[4])) = htonl(ACK_num);
	*((int*)(&send_packet[8])) = htonl(fwnd);
	*(&send_packet[12]) = flag;
	// The transmitter puts the message in the buffer because we don't know 
	// where in the ring the message will be
	uint size = bytes + 13;
	sendto(fildes, (void *) send_packet, size, 0, (struct sockaddr*)&from, fromlen);
	err("emitted packet")
	slow()
}

#endif