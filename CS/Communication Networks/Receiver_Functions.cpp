#ifndef __Receiver_INCLUDED__   
#define __Receiver_INCLUDED__
#include "connection.h"


int connection::deliver(char* buffer, int max_bytes){
	err("Entered deliver")

//----Check Connection is Still Open Or There Is Deliverable Data-----
	_lock(&connection_state_mux);
		if( connection_state==8 && (get_deliverable() == 0) ){
			err("Closed Connection and Nothing Deliverable")
			_unlock(&connection_state_mux);	
			return -2;
		}
	_unlock(&connection_state_mux);	
//----Check Connection is Still Open Or There Is Deliverable Data-----

//-------------check if receive_buffer has anything-------------------
	int deliverable;
	while( ( deliverable = get_deliverable() ) == 0){
		err("still nothing deliverable")
		if(connection_state==8){
			break;
		}
		_lock(&nothing_deliverable_mux);
			_wait(&nothing_deliverable, &nothing_deliverable_mux);
		_unlock(&nothing_deliverable_mux);
	}
//-------------check if receive_buffer has anything-------------------
	err("There is something deliverable")


//------------------------adjust bytes--------------------------------
	if(deliverable < max_bytes){
		max_bytes = deliverable;
	}
//------------------------adjust bytes--------------------------------
	err("Moving contents into user buffer")
//--------------------move into user buffer---------------------------
	_lock(&delivered_mux);
		for(int i=0; i<max_bytes; i++){
			char_err("character in buffer",receive_buffer[(delivered+i+1) & BUFFERMASK])
			buffer[i] = receive_buffer[(delivered+i+1) & BUFFERMASK];
		}
		delivered += max_bytes;
		delivered &= BUFFERMASK;
	_unlock(&delivered_mux);
//--------------------move into user buffer---------------------------

//----------------------signal to receiver----------------------------
	_lock(&receive_buf_full_mux);
		err("D")
		_signal(&receive_buf_full);
	_unlock(&receive_buf_full_mux);
//----------------------signal to receiver----------------------------
	err("delivered bytes to user buffer")
	return max_bytes;
}

void connection::handle_timer(){
	err("timeout occured");
//----------------Double RTT And Disable Timer------------------------
	double_RTT();
	timer_set = false;
//----------------Double RTT And Disable Timer------------------------

	err("gathering connection_state_mux")
	_lock(&connection_state_mux);
	err("gathered connection_state_mux")
//------------------Resend Handshake Timeouts-------------------------
		if( (connection_state <= 3) || ((5 <= connection_state) && (connection_state <= 6))   ){
			err("Timeout in Begin Handshake or states 5 or 6")
			_broadcast(&new_state);
		} 
//------------------Resend Handshake Timeouts-------------------------

//----------------------Check Close Wait------------------------------
		else if(connection_state == 7){
			connection_state = 8;
			err("Signaling State is Closed")
			_broadcast(&new_state);
		} 
//----------------------Check Close Wait------------------------------

		else if(connection_state ==4){

//----------------------Enter Slow Start------------------------------
			congestion_state = 0;
			ssthresh = cwnd/2+1;
			cwnd = 1*MSS;
			duplicate_acks = 0;
//----------------------Enter Slow Start------------------------------

//-------------------Adjust Sequence Number---------------------------
			int distance = ring_buffer_distance( ((SEQ_num)&(BUFFERMASK)), ACKed);
			err("adjusting sequence number")
			SEQ_num -= distance;
//-------------------Adjust Sequence Number---------------------------
		}
	_unlock(&connection_state_mux);

//--------------------Wake the Transmitter----------------------------
	_lock(&transmitter_wake_mux);
		err("Waking the Transmitter")
		_signal(&transmitter_wake_cond);
	_unlock(&transmitter_wake_mux);
//--------------------Wake the Transmitter----------------------------
	err("Done Handling Timer")
}

void connection::receive(){
	err("in receive");
//-----------------------Initial handshake----------------------------

	while(connection_state <= 3 ){
		err("waiting for a packet");
		int bytes_received = recvfrom(fildes, (void*)receive_packet, PACKET_SIZE,
										0, (struct sockaddr*)&from, &fromlen);
		err("received a handshake packet");
//-----------------------Check For Timeout----------------------------
		if(bytes_received == -1){
			handle_timer();
			continue;
		}
//-----------------------Check For Timeout----------------------------

//----------------------Update RTT Estimates--------------------------
		gettimeofday(&RTT_end,NULL);
		update_RTT_estimates();
//----------------------Update RTT Estimates--------------------------

		char flag = *(&receive_packet[12]);
		slow()
		int_err("bytes_received",bytes_received)

//---------Change or Repeat State and Signal Transmitter--------------
		_lock(&connection_state_mux);
		err("Change or Repeat connection_state_mux gathered")
			if( ( connection_state == 0 ) && ( flag == _SYN ) ){
				connection_state=2;
				err("SYN received")
			}
			if( ( connection_state == 1 ) && ( flag == _SYN_ACK ) ){
				connection_state = 3;
				err("SYN_ACK received")
			}
			if( ( connection_state == 2 ) && ( flag == _ACK ) ){
				connection_state = 4;
				err("ACK received")
				send_ACK = true; // Just Bob knows the connection is established, we send a packet
			}
			if( ( connection_state == 3 ) && ( flag == _NONE ) ){
				connection_state = 4;
				err("Data recieved")
				handle_recvd_packet(bytes_received);
			}
			_broadcast(&new_state);
		_unlock(&connection_state_mux);
//---------Change or Repeat State and Signal Transmitter--------------
	}
//-----------------------Initial handshake----------------------------

	err("Entering Data Transfer State")

//-------------------------Data Transfer------------------------------{
	while(connection_state == 4){
		err("waiting for packet")
		int bytes_received = recvfrom(fildes, (void*)receive_packet, PACKET_SIZE,
											0, (struct sockaddr*)&from, &fromlen);
//-----------------------Check For Timeout----------------------------
		if(bytes_received == -1){
			handle_timer();
			continue;
		}
//-----------------------Check For Timeout----------------------------
		err("packet received")

//----------------------Handle Received Packet------------------------ 
		handle_recvd_packet(bytes_received); //handle_recvd packet handles RTT updates
//----------------------Handle Received Packet------------------------

//-----------------Check for Connection Termination-------------------
		char flag = *(&receive_packet[12]);
		if(flag == _FIN){
			err("Received FIN")
			_lock(&connection_state_mux);
				err("aquiring lock")
				connection_state = 6;
			_unlock(&connection_state_mux);
		} 
//-----------------Check for Connection Termination-------------------

//---------------Inform Transmitter to ack new packet-----------------
		_lock(&transmitter_wake_mux);
			err("informing transmitter to ack new packet")
			_signal(&transmitter_wake_cond);
		_unlock(&transmitter_wake_mux);
//---------------Inform Transmitter to ack new packet-----------------

	}
//-------------------------Data Transfer------------------------------}
	err("receiver entered terminal handshake")



//		Terminal Handshake



//----------------------terminal handshake----------------------------{
	while( 5 <= connection_state && connection_state <= 7 ){
		int bytes_received = recvfrom(fildes, (void*)receive_packet, PACKET_SIZE, 
											0, (struct sockaddr*)&from, &fromlen);
//-----------------------Check For Timeout----------------------------
		if(bytes_received == -1){
			handle_timer();
			continue;
		}
//-----------------------Check For Timeout----------------------------

//----------------------Update RTT Estimates--------------------------
		gettimeofday(&RTT_end,NULL);
		update_RTT_estimates();
//----------------------Update RTT Estimates--------------------------


		char flag = *(&receive_packet[12]);

//---------Change or Repeat State and Signal Transmitter--------------
		_lock(&connection_state_mux);
			if( ( connection_state == 5 ) && ( flag == _FIN_ACK ) ){
				connection_state = 7;
				err("FIN_ACK received")
			}
			if( ( connection_state == 6 ) && ( flag == _ACK ) ){
				connection_state = 8;
				err("ACK received, connection closed")
			}
			if( connection_state == 7 ){
				connection_state = 7;
				err("Resend ACK to close connection")
			}
			_broadcast(&new_state);
		_unlock(&connection_state_mux);
//---------Change or Repeat State and Signal Transmitter--------------
	}
//----------------------terminal handshake----------------------------}

//-----------Inform User of no more data is coming--------------------
		int_err("deliverable",get_deliverable())
		_lock(&nothing_deliverable_mux);
			err("Signal More Deliverable Data")
			_signal(&nothing_deliverable);
		_unlock(&nothing_deliverable_mux);
//-----------Inform User of no more data is coming--------------------
	err("Done with receive")
}


void connection::handle_recvd_packet(int bytes_received){
	err("Handling a received packet")
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
//--------------------Deconstruct the Packet--------------------------
	int message_length = bytes_received -13;
	uint Bob_seq_num = ntohl( * ((uint*)(&receive_packet[0])) );
	uint Bob_ack_num = ntohl( * ((uint*)(&receive_packet[1])) );
	uint Bob_fwdn_num = ntohl( * ((uint*)(&receive_packet[2])) );
//--------------------Deconstruct the Packet--------------------------
	err("message")
	err("message")
	err("message")
	err("message")
	err("message")
	err("message")
	err("message")
	// for(int i=0; i<bytes_received; i++){
	// 	fprintf(stderr,"%c",receive_packet[i]);
	// }
	int_err("message_length",message_length)
	err("end message")

//---------------------Update RTT Estimates---------------------------
	if(Bob_ack_num==timed_SEQ_num){
		gettimeofday(&RTT_end,NULL);
		update_RTT_estimates();
	}
//---------------------Update RTT Estimates---------------------------

//---------------Calculate Space in Receive Buffer--------------------
	int receive_cap  = get_receive_buf_cap();
//---------------Calculate Space in Receive Buffer--------------------

//-----------Make In Order Packet Contents Deliverable----------------{
	int_err("Bob_seq_num",Bob_seq_num)
	int_err("ACK_num",ACK_num&BUFFERMASK)
	if(Bob_seq_num == (ACK_num&BUFFERMASK)){
		err("putting bytes receive buffer")
		for(int i=0; i<min(message_length,receive_cap); i++){
			receive_buffer[(ACK_num+1+i)&(BUFFERMASK)] = receive_packet[i+13];
		}

		_lock(&ACK_num_mux);
			ACK_num+= min(message_length, receive_cap);
//-----------------Repair Gap If It Exists----------------------------
			if(OOO_segment==true){
				if(OOO_received_start==ACK_num+1){
					ACK_num+=OOO_received_length;
					OOO_segment=false;
				}
			}
//-----------------Repair Gap If It Exists----------------------------
		_unlock(&ACK_num_mux);

//-------------Inform User of new deliverable Data--------------------
		int_err("deliverable",get_deliverable())
		_lock(&nothing_deliverable_mux);
			err("Signal More Deliverable Data")
			_signal(&nothing_deliverable);
		_unlock(&nothing_deliverable_mux);
//-------------Inform User of new deliverable Data--------------------
	}
//-----------Make In Order Packet Contents Deliverable----------------}

//------------------Store Out of Order Packets------------------------
	else{
		int bytes_needed;
		if(OOO_segment==true){
			if(OOO_received_start + OOO_received_length + 1 == Bob_seq_num){
				bytes_needed = message_length;
				int end_of_OOO = OOO_received_start+OOO_received_length;
				for(int i=0; i<min(bytes_needed, receive_cap); i++){
					receive_buffer[(end_of_OOO+i+1)&(BUFFERMASK)] = receive_packet[i+12];
				}
				OOO_received_length += min(bytes_needed,receive_cap);
			}
			else{
				// drop the packet... design can only handle one OOO packet.
			}
		} else {
			int distance = (Bob_seq_num - ACK_num);
			bytes_needed = distance + message_length;
			
			for(int i=distance; i<min(bytes_needed, receive_cap); i++){
				receive_buffer[(ACK_num+i+1)&(BUFFERMASK)] = receive_packet[i+12];
			}

			OOO_received_start = Bob_seq_num;
			OOO_received_length = min(message_length,(receive_cap-distance));
			OOO_segment=true;
		}
	}
//------------------Store Out of Order Packets------------------------

//---------------------Handle Duplicate ACK---------------------------{
	if(Bob_ack_num == ACKed){
		duplicate_acks++;
		if(duplicate_acks == 3){
//---------------------Go into Fast Recovery--------------------------
			_lock(&congestion_state_mux);
				congestion_state = 2;
				ssthresh=cwnd/2 ;
				cwnd=ssthresh+3*MSS;
				resend_packet = true;
			_unlock(&congestion_state_mux);
//---------------------Go into Fast Recovery--------------------------
		}
		if(duplicate_acks > 3){
			cwnd+=MSS;
		}
	} 
//---------------------Handle Duplicate ACK---------------------------}

//------------------------Handle New ACK------------------------------
	else {
		duplicate_acks = 0;
		_lock(&ACKed_mux);
			ACKed = (Bob_ack_num & (BUFFERMASK));
			send_ACK=true;
		_unlock(&ACKed_mux);

		if(congestion_state==0){
			cwnd=cwnd+MSS;
			if(cwnd >= ssthresh){
				congestion_state=1;
			}
		} else if(congestion_state==1){
			cwnd=cwnd+(MSS*(MSS/cwnd));
		} else {
			cwnd=cwnd+MSS;
			congestion_state = 1;
		}

	}
//------------------------Handle New ACK------------------------------

	err("Done Handling Received Packet")
}

void connection::double_RTT(){
	RTT.tv_sec *= 2;
	RTT.tv_sec += (RTT.tv_usec * 2)/1000000;
	RTT.tv_usec = (RTT.tv_usec * 2)%1000000;
	if(RTT.tv_sec>5){
		RTT.tv_sec = 5;
	}
	err("doubled RTT")
}

int connection::get_receive_buf_cap(){
	int output;
	_lock(&delivered_mux);
	_lock(&ACK_num_mux);
		if(OOO_segment==true){
			int_err("OOO_received_start",OOO_received_start)
			int_err("OOO_received_length",OOO_received_start)
			int end_of_OOO = ((OOO_received_start+OOO_received_length)&BUFFERMASK);
			int_err("end_of_OOO",end_of_OOO)
			int_err("delivered",delivered)
			output = ring_buffer_distance(delivered, end_of_OOO);
		} else {
			int_err("delivered",delivered)
			int_err("ACK_num",ACK_num)
			output = ring_buffer_distance(delivered, ACK_num);
		}
	_unlock(&ACK_num_mux);
	_unlock(&delivered_mux);

	output = (output-1) & BUFFERMASK;

	int_err("calculated receive buffer capacity",output)
	return output;
}
int connection::get_deliverable(){
	int output;
	_lock(&delivered_mux);
	_lock(&ACK_num_mux);
		int_err("ACK_num",ACK_num)
		int_err("delivered",delivered)
		output = ring_buffer_distance(ACK_num, delivered);
	_unlock(&ACK_num_mux);
	_unlock(&delivered_mux);
	int_err("calculated deliverable",output)
	return output;
}

void connection::update_RTT_estimates(){
	err("updating RTT estimates")
//---------------------Calculate Current RTT--------------------------
	struct timeval current_RTT;
	current_RTT.tv_sec = RTT_end.tv_sec - RTT_begin.tv_sec;
	current_RTT.tv_usec = RTT_end.tv_usec - RTT_begin.tv_usec;
//---------------------Calculate Current RTT--------------------------

//----------------------Calculate Deviation---------------------------
	struct timeval current_deviation;
	current_deviation.tv_sec = int_abs( (current_RTT.tv_sec - RTT.tv_sec) );
	current_deviation.tv_usec = int_abs( (current_RTT.tv_usec - RTT.tv_usec) );
//----------------------Calculate Deviation---------------------------

//--------------------------Update RTT--------------------------------
	RTT.tv_sec = (int)((double)ALPHA * (double)RTT.tv_sec + (double)(1.0-ALPHA) * (double)current_RTT.tv_sec);
	RTT.tv_usec = (int)((double)ALPHA * (double)RTT.tv_usec + (double)(1.0-ALPHA) * (double)current_RTT.tv_usec);
//--------------------------Update RTT--------------------------------

//-----------------------Update Deviation-----------------------------
	Deviation.tv_sec = 	  (int)((double)BETA * (double)Deviation.tv_sec 
						+ (double)(1.0-BETA)*(double)current_deviation.tv_sec);
	Deviation.tv_usec =   (int)((double)BETA * (double)Deviation.tv_usec 
						+ (double)(1.0-BETA)*(double)current_deviation.tv_usec);
//-----------------------Update Deviation-----------------------------
	err("RTT estimates updated")
}

#endif