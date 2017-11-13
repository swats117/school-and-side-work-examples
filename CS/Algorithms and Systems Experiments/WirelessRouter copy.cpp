#include <cstdio> 
#include <string.h>
#define LOCATIONS 10
#define ROUTERS 3
#define INFINITY 0x000003ff
#define INFINITY_TWO 0x7fffffff

int cost(int* locations, int length){


	int cost=0;
	int left_router = locations[0];
	int right_router = locations[length-1];

	for(int i=1; i<length-1; i++){
		int right_cost = locations[0]-locations[i];
		 right_cost *= right_cost;
		int left_cost = locations[length-1]-locations[i];
		left_cost *= left_cost;

		cost+= (left_cost<right_cost? left_cost*left_cost: right_cost*right_cost);
	}

	return cost;
}
int main(){
	int house_locations [LOCATIONS+2] = {0,1,5,8,10,11,16,21,30,45,47,0};
	house_locations [0]=INFINITY;
	house_locations [LOCATIONS+1]=INFINITY; 

	int memo_table [LOCATIONS+3][LOCATIONS+3][LOCATIONS+3];
	memset(memo_table, 0, (LOCATIONS+3)*(LOCATIONS+3)*(LOCATIONS+3)*sizeof(int));

	for(int substr_len=2; substr_len<=(LOCATIONS+2); substr_len++){
		for(int num_routers=0; num_routers<=ROUTERS; num_routers++){
			for(int substr_start=0; substr_start<=(LOCATIONS+2)-substr_len; substr_start++){

				if( num_routers >= substr_len-2 ){
					memo_table[substr_len][num_routers][substr_start] = 0;
					continue;
				}
				if(num_routers==0){
					int _cost = cost(&house_locations[substr_start],substr_len);
					memo_table[substr_len][num_routers][substr_start] = _cost;
					continue;
				}
				// Then, if we have at least one routers left to place, and more than one
				// location left in which to place them, then this is the recursive case.
				//
				// Our situation looks like this
				// Start l  l  l  l  l  End
				//
				// The recursive case calls for us to pick a location from among the inner locations, C,
				// we then add a router to that location.
				// We then add up cost from Start to the location we picked + cost from the location we
				// picked to End for each possible distribution of routers to the left and the right substrings.
				//
				// Consider the following example where we have 3r, C is the location we pick for the next router
				// and there are 5l inner locaitons.
				//
				// |    1r   |  2r   |		VS		|    2r   |  1r   |
				// Start l l C l l End 				Start l l C l l End
				//
				//   VS
				//
				// |   1r  |    2r   |		VS		|   2r  |    1r   |
				// Start l C l l l End 				Start l C l l l End 
				// 
				// Then we find the minimum among these and consider it as the cost.
				//
				// To aid in finding the minimum cost, we will make the cost of the current position
				// high.
				memo_table[substr_len][num_routers][substr_start] = INFINITY_TWO;
				//
				// k = start of substring.
				// inner substring starts at k+1
				// i = length of substring, substring ends at i+k
				// inner substring ends at i+k-1

				int num_routers_left = num_routers-1;

				for(int right_substr_start=substr_start+1; right_substr_start<substr_start+substr_len-1; right_substr_start++){
					
					for(int left_routers=0; left_routers<=num_routers_left; left_routers++){

						int right_routers = num_routers_left - left_routers;

						int left_substring_cost = memo_table[right_substr_start+1-substr_start][left_routers][substr_start];
						int right_substring_cost = memo_table[substr_start+substr_len-right_substr_start][right_routers][right_substr_start];

						int this_scenario_cost = left_substring_cost+right_substring_cost;
						int cur_min_scenario_cost = memo_table[substr_len][num_routers][substr_start];
						memo_table[substr_len][num_routers][substr_start] = (this_scenario_cost<cur_min_scenario_cost?this_scenario_cost:cur_min_scenario_cost);
					}
				}
			}
		}

	}	

	printf("answer: %d\n",memo_table[LOCATIONS+2][ROUTERS][0]);

	return 0;
}







