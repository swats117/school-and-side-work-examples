/* 
 * File:   receiver_main.c
 * Author: 
 *
 * Created on
 */

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>
// #include <arpa/inet.h>
#include <netinet/in.h>
// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #include <pthread.h>

#include "connection.h"

struct sockaddr_in si_me, si_other;
int s, slen;

void diep(char *s) {
    perror(s);
    exit(1);
}



void reliablyReceive(unsigned short int myUDPport, char* destinationFile) {
    
    slen = sizeof (si_other);


    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        diep("socket");

    memset((char *) &si_me, 0, sizeof (si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(myUDPport);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("Now binding\n");
    if (::bind(s, (struct sockaddr*) &si_me, sizeof (si_me)) == -1)
        diep("bind");


    // create RDT connection

    // receive data

    // take data and put into file
    // size_t fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);

    FILE *fp;
    fp = fopen(destinationFile, "w");
    if (fp == NULL) {
        printf("Could not open file to send.");
        exit(1);
    }

    char local_buff [MSS+1];
    connection conn(s);

    int bytes_received;
    while(( bytes_received = conn.deliver(local_buff,MSS) ) != -2){
        fwrite(local_buff, 1, bytes_received, fp);
    }
    conn.close();

	/* Now receive data and send acknowledgements */    

    close(s);
	printf("%s received.", destinationFile);
    return;
}

/*
 * 
 */
int main(int argc, char** argv) {

    unsigned short int udpPort;

    if (argc != 3) {
        fprintf(stderr, "usage: %s UDP_port filename_to_write\n\n", argv[0]);
        exit(1);
    }

    udpPort = (unsigned short int) atoi(argv[1]);

    reliablyReceive(udpPort, argv[2]);
}

