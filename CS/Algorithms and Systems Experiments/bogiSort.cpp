#include <cstdio>



// # i ← 1
// # while i < length(A)
// #     x ← A[i]
// #     j ← i - 1
// #     while j >= 0 and A[j] > x
// #         A[j+1] ← A[j]
// #         j ← j - 1
// #     end while
// #     A[j+1] ← x[4]
// #     i ← i + 1
// # end while

int insertionSort(int* A,int length){
	int i=1;
	int swapCount=0;
	while(i<length){
		int x = A[i];
		int j = i-1;
		while (j>= 0 && A[j] > x){
			A[j+1] = A[j];
			swapCount++;
			j = j-1;
		}
		for(int k=0; k<length; k++){
			printf("%d, ",A[k]);
		} printf("\n");
		A[j+1] = x;
		i++;
	}
	return swapCount;
}

int bogiSort(int* A, int length){

	int answer = 0;
	if(length<=16){
		return insertionSort(A, length);
	}
	else{
		for(int i=0; i<3; i++){
			for(int j=2; j>=i; j--){
				int tempanswer = bogiSort(&A[j*length/4],length/2);
				printf("")
				answer+=tempanswer;
				// bogiSort(A[jn/4...(j+ 2)n/4−1])
			}
		}
	}
	return answer;
}


int main(){


	int blah [64];
	for(int i=0; i<64; i++){
		blah[i]=32-i;
	}

	int answer = bogiSort(blah,64);

	for(int i=0; i<64; i++){
		printf("%d, ",blah[i]);
	} printf("\n");
	printf("%d\n",answer);

	return 0;
}