#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){

	int input = 0xF473F130;
	int input2 = 0x24B54F35;
	int input3 = 0x58F16248;
	int input4 = 0x55;

	

	unsigned int message [13];
	char* Ciphertext = "F4 73 F1 30 24 B5 4F 35 58 F1 62 48 55";
	sscanf(Ciphertext, "%x %x %x %x %x %x %x %x %x %x %x %x %x", &message[0],
	&message[1],&message[2],&message[3],
	&message[4],&message[5],&message[6],
	&message[7],&message[8],&message[9],
	&message[10],&message[11],&message[12]);

	char message2[14];
	message2[13] = '\0';
	for(int i=0; i<13; i++){
		message2[i]=(unsigned char)message[i];
		printf("%x",message2[i]);
		// printf("%x",message[i]);
	}
	char* Five_Message = "Flag=";
	printf("\n%s\n",message2);
	char keystream[6];
	keystream[5]='\0';
	for(int i=0; i<5; i++){
		keystream[i]=message2[i]^Five_Message[i];
		printf("%x",keystream[i]);
	}
	

	return 0;
}