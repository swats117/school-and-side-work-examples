#include <cstdio>


int main(){
	for(int i=5; i>=0; i--){
		for(int j=i+1; j<5; j++){
			printf("i:%d, j:%d\n",i,j);
		}
	}	
	return 0;
}