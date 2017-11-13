#include <cstdio>
#include <string.h>
#include <queue>
#include <unistd.h>
#define SIZE 9
using namespace std;

class split_info{
public:
	int start;
	int end;
	int x_coord;
	int y_coord;
	split_info(int start, int end, int x_coord, int y_coord): start(start), end(end), x_coord(x_coord), y_coord(y_coord) {}
};

int main(){
	
 // {4,1,8,4}
	int weights [SIZE] = {4,1,8,4,7,10,19,3,1};
	// int weights [SIZE] = {4,1,8,4,7};
	int memo_table [SIZE][SIZE];
	int weight_table [SIZE][SIZE];
	int split_table [SIZE][SIZE];
	memset(memo_table,0,SIZE*SIZE*4);
	memset(weight_table,0,SIZE*SIZE*4);
	memset(split_table,0,SIZE*SIZE*4);

	for(int i=0; i<SIZE; i++){
		for(int j=i; j<SIZE; j++){
			printf("%d, %d\n",j-i,j);
			// This sets the diagonal as the weights.
			if(i == 0){
				memo_table[j][j]=0;
				weight_table[j][j] = weights[j];
			} else {
				// First we set the uncalculated weight to infinity.
				memo_table[j-i][j] = 0x7fffffff;
				/*
								 (j)
				(j-i) ->[1, 2, 3, 4]
						[0, 1, 2, 3]
						[0, 0, 1, 2]
						[0, 0, 0, 1]
				*/
				printf("weight_table(%d,%d): %d\n", j-i,j-i,weight_table[j-i][j-i]);
				printf("weight_table(%d,%d): %d\n", j-i+1,j,weight_table[j-i+1][j]);
				weight_table[j-i][j] = weight_table[j-i][j-i]+weight_table[j-i+1][j];
				printf("weight_table: %d\n", weight_table[j-i][j]);
				for(int k=1; k<=i; k++){
					printf("below coord: (%d,%d)\n",j-i+k, j);
					printf("besid coord: (%d,%d)\n",j-i, j-(i+1-k));
					int value_below = memo_table[(j-i)+k][j];
					int value_besid = memo_table[j-i][j-(i+1-k)];
					printf("value_below: %d\n", value_below);
					printf("value_besid: %d\n", value_besid);
					int sum = value_below+value_besid;
					printf("old value: %d\n", memo_table[j-i][j]);
					printf("new sum: %d\n",sum);
					printf("new value for (%d,%d): %d\n",j-i,j,(memo_table[j-i][j]<sum?memo_table[j-i][j]:sum));
					
					if(sum < memo_table[j-i][j]){
						memo_table[j-i][j] = sum;
						split_table[j-i][j]= k;
					}
				}
				memo_table[j-i][j] += weight_table[j-i][j];
			}
		}
	}

	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			printf("%d ",memo_table[i][j]);
		}printf("\n");
	}
	printf("\n");
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			printf("%d ",split_table[i][j]);
		}printf("\n");
	}

	queue<split_info*> splits;
	// 				 size 
	split_info* first = new split_info(0,SIZE, 0, SIZE-1);
	splits.push(first);
	split_info* current;
	while( (current=splits.front()) ){
		// usleep(500000);
		splits.pop();
		


		int x_coord = current->x_coord;
		int y_coord = current->y_coord;
		int start = current->start;
		int end = current->end;

		// printf("x_coord: %d, y_coord: %d, start: %d, end: %d \n",x_coord,y_coord,start,end);

		if(current->x_coord==current->y_coord){
			// printf("skipp\n");
			delete current;
			continue;
		}

		int decision = split_table[current->x_coord][current->y_coord];
		int size = current->end - current->start;
		printf("decision: %d \n",decision+start);
		// printf("decision: %d size: %d\n",decision+start,size);

		int right_x_coord = current->x_coord + decision;
		int left_y_coord = current->y_coord - (size - decision);

		splits.push( new split_info(current->start,current->start+decision, current->x_coord,left_y_coord) );
		splits.push( new split_info(current->start+decision,current->end,  right_x_coord, current->y_coord) );

		delete current;
		// splits
	}
	printf("\n");
	


	return 0;
}
















