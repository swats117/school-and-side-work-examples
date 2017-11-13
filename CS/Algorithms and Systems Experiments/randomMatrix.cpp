#include <stdio.h>
#include <random>
#include <time.h> 
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv){
	
	if(argc!=2){
		fprintf(stderr,"Please include an argument for the size of the matrix\n");
		exit(1);
	}
	int length;
	sscanf(argv[1], " %d", &length);


	srand((int)time(NULL));

	for(int i=0; i<length; i++){
		for(int j=0; j<length-1; j++){
			printf("%d, ",rand()%100);
		}printf("%d\n",rand()%100);
	}

	return 0;
}