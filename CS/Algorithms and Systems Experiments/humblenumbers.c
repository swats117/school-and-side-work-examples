/*
	Algorithm to produce the "humble numbers."
	Humble numbers have only 2,3,5, and 7 as factors.
*/

#include <stdio.h>
#include <string.h>

// #define errprint(a,b) fprintf(stderr, a,b);

char* determine_suffix(int i);
int max(int a, int b, int c, int d);

int main(){

	
	int results[6000*sizeof(int)];
	results[0]=1;
	// memset(&results[1],0,6000*sizeof(int));

	int input;
	int current_limit=1;

	int* limit_2=&results[1];
	int* limit_3=&results[1];
	int* limit_5=&results[1];
	int* limit_7=&results[1];
	int current_2=2;
	int current_3=3;
	int current_5=5;
	int current_7=7;

	while(scanf("%d",&input)){
		if(input==0) break;

		while( input>current_limit){
			// errprint("input: %d, ",input);
			// errprint("current_2: %d, ",current_2);
			// errprint("current_3: %d, ",current_3);
			// errprint("current_5: %d, ",current_5);
			// errprint("current_7: %d, \n",current_7);
			if(current_2<current_3){
				if(current_5<current_7){
					if(current_2<current_5){
						results[current_limit]=current_2;
						current_2= *limit_2*2;
						limit_2++;
					} else {
						if(current_2==current_5){
							current_2= *limit_2*2;
							limit_2++;
						}
						results[current_limit]=current_5;
						current_5= *limit_5*5;
						limit_5++;
					}
				} else /*7<5*/{
					if(current_5==current_7){
						current_5= *limit_5*5;
						limit_5++;
					}
					if(current_2<current_7){
						results[current_limit]=current_2;
						current_2= *limit_2*2;
						limit_2++;
					} else {
						if(current_2==current_7){
							current_2= *limit_2*2;
							limit_2++;
						}
						results[current_limit]=current_7;
						current_7= *limit_7*7;
						limit_7++;
					}
				}
			} else {
				if(current_2==current_3){
					current_2= *limit_2*2;
					limit_2++;
				}
				if(current_5<current_7){
					if(current_3<current_5){
						results[current_limit]=current_3;
						current_3= *limit_3*3;
						limit_3++;
					} else {
						if(current_3==current_5){
							current_3= *limit_3*3;
							limit_3++;
						}
						results[current_limit]=current_5;
						current_5= *limit_5*5;
						limit_5++;
					}
				} else /*7<5*/{
					if(current_5==current_7){
						current_5= *limit_5*5;
						limit_5++;
					}
					if(current_3<current_7){
						results[current_limit]=current_3;
						current_3= *limit_3*3;
						limit_3++;
					} else {
						if(current_3==current_7){
							current_3= *limit_3*3;
							limit_3++;
						}
						results[current_limit]=current_7;
						current_7= *limit_7*7;
						limit_7++;
					}
				}
			}
			current_limit++;
	  	}
	  	char* suffix=determine_suffix(input);
		printf("The %d%s humble number is %d.\n",input,suffix,results[input-1]);
	}
}


char* determine_suffix(int i){
	char* suffix="th";
	if(i%10==1){
  		suffix="st";
	} 
	else if (i%10==2){
		suffix="nd";
	}
	else if (i%10==3){
		suffix="rd";
	}
	if((i/10)%10==1){
		suffix="th";
	}
	return suffix;
}