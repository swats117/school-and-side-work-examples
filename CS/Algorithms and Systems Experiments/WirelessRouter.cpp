/* Note: algorithm suboptimal. */

/* You are given n locations l_1,...,l_n of people living on Red street. Here l_i is the distance of the ith
person from the beginning of the street in feet (Red street is straight), where l_1 < l_2 < · · · < l_n.
We would like to install k wireless routers to serve these people's needs.

Specifically, for a set of locations Y = {y_1 , . . . , y_k }, the cost of this solution 
to the ith customer is the distance of l_i to its nearest wireless routers in Y to the power four.
Formally, it is cost(li, Y ) = min y∈Y (y − l_i)^4 = (l_i − nn(l_i, Y ))^4, where nn(l_i, Y ) 
is the location of the nearest point to li in Y . 

Indeed, the further a person’s computer is from a wireless router, the stronger the signal 
his computer has to use to communicate with the router, and the energy of this signal grows 
as (say) a fourth power of the distance.

The cost of the solution Y is cost(Y ) =  i cost(l_i, Y ).
Given the n locations l_1,...,l_n and k, provide an algorithm,
as fast as possible (in n and k), that computes the set Y ⊆ {l_1, . . . , l_n}
of k routers, such that cost(Y ) is minimal. What is the running time of your algorithm? 
(Note, that the routers can be placed only in the given locations of the houses1.)
*/


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
	/* memo table structure
		
		Each row will represent the length of the substrings we are calculating for. 
		We also need to account for the number of routers given.

		first dimension will be length of substrings
		second dimension will be where we start from
		third dimension will be number of routers

		where generally the #routers<length(substring)
	*/
	int house_locations [LOCATIONS+2] = {0,1,5,8,10,11,16,21,30,45,47,0};
	// int house_locations [LOCATIONS+2] = {0, 3, 5, 7, 12, 20, 21, 0};


	house_locations [0]=INFINITY;
	house_locations [LOCATIONS+1]=INFINITY; 

	int memo_table [LOCATIONS+3][LOCATIONS+3][LOCATIONS+3];
	memset(memo_table, 0, (LOCATIONS+3)*(LOCATIONS+3)*(LOCATIONS+3)*sizeof(int));




	// outer for loop is for size of substring.
	// we assume the start and end locations of the substring have routers.
	for(int substr_len=2; substr_len<=(LOCATIONS+2); substr_len++){
		// first inner for loop is for number of routers.
		// the max number of routers is the number of locations - 2
		// because the start and end locations already have routers.
		for(int num_routers=0; num_routers<=ROUTERS; num_routers++){
			
			// second inner for loop is for starting position of substring.
			for(int substr_start=0; substr_start<=(LOCATIONS+2)-substr_len; substr_start++){

				// If we don't have any routers left to place. (j==0)
				// Then we calculate the remaining cost.
				
				// If we have one router left and one spot left, then all locations are covered
				// So the cost is 0. Or if we have a substring sized 2, then since both
				// ends have routers, all locations are covered and cost is 0.
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







