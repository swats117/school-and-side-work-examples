#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void enc(char* flag, int key);
void dec(char* flag, int key);

int main(){

	unsigned int outputs [15];
	char inputs2[16];
	inputs2[15]='\0';
	sscanf("3C F7 BF 3C D9 53 49 57 33 27 68 BA 70 28 65","%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",&outputs[0],&outputs[1],&outputs[2],
		&outputs[3],&outputs[4],&outputs[5],&outputs[6],
		&outputs[7],&outputs[8],&outputs[9],&outputs[10],
		&outputs[11],&outputs[12],&outputs[13],&outputs[14]);

	for(int i=0; i<15; i++){
		inputs2[i]=(char)outputs[i];
	}
	printf("%s\n",inputs2);

	char inputs3[16];
	for(int i=0; i<256; i++)
	{
		strcpy(inputs3,inputs2);
		dec(inputs3, i);
		if(inputs3[0]=='F'){
			printf("%d: %s\n", i, inputs3);
		}
		enc(inputs3, i);
	}

	return 0;
}

void enc(char* flag, int key){
	while(*flag){
		key = (key*13)+37;
		*flag ^= (char)key;
		*(flag++)+=3;
	}
}
void dec(char* flag, int key){
	while(*flag){
		*(flag)-=3;
		key = (key*13)+37;
		*flag ^= (char)key;
		flag++;
	}
}


