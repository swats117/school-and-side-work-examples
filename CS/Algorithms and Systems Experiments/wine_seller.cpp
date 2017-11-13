#include <cstdio>


int solve(int* array, int array_size);
int solve_recurse(int** memos,int* array, int start, int current_level, int array_size);
int main(){


	int array_size=7;
	int bottles [7]={2,3,5,1,4,10,4};
	// int array_size=5;
	// int bottles [5]={2,3,5,1,4};


	int solution = solve(bottles,array_size);
	printf("The optimal solution is %d\n", solution);

}


int solve(int* array, int array_size){

	printf("in solve\n");
	int* memos[array_size];


	for(int i=1; i<array_size; i++){
		int* memo_row= new int[array_size-i];
		memos[i]=memo_row;
		for(int j=0;j<array_size-i;j++){
			memos[i][j] = solve_recurse(memos,array,j,i,array_size);
		}
	}
	return memos[array_size-1][0];
}

int solve_recurse(int** memos,int* array, int start, int current_level, int array_size)
{
	// base_case: current_level = 1
	// ab, bc, cd, de
	if(current_level==1){
		if(array[start]>array[start+1]){
			return (array_size*array[start]) + ((array_size-1)*array[start+1]);
		} else {
			return (array_size*array[start+1]) + ((array_size-1)*array[start]);
		}
	} 
	// recursive_case: current_level>1
	// ab...yz --> (ab...y)+(z*current_level) vs (a*current_level)+(b...yz)
	else {
		int left_amount =  memos[current_level-1][start]  + ((array_size - current_level)*array[start+current_level]);
		int right_amount = memos[current_level-1][start+1]+ ((array_size - current_level)*array[start]);
		if (left_amount>right_amount){
			return left_amount;
		}
		else{
			return right_amount;
		}
	}
}
