#include <stdio.h>

int main(){

  float input;
  float total=0.0;
  for(int i=0; i<12; i++){
  	scanf("%f",&input);
  	total += input;
  }  
  printf("%.2f\n",total);

  return 0;
 
}