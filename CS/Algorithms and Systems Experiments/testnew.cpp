#include <cstdio>

int main(){
	
	int* blah = new int[5];

	for(int i=0; i<5-1; i++){
		printf("%d, ",blah[i]);

	}printf("%d\n",blah[5-1]);

	delete[] blah;

	return 0;
}