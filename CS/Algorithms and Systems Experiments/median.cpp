/*
	An algorithm to keep track of the median of a set of numbers using two heaps.
*/

#include <cstdio>
#include <queue>

int main(){

	auto comp_less = [] (int &a, int &b) -> bool { return a > b; };
	auto comp_greater = [] (int &a, int &b) -> bool { return a < b; };

	std::priority_queue <int,std::vector<int>,decltype(comp_less)> above (comp_less);
	std::priority_queue <int,std::vector<int>,decltype(comp_greater)> below (comp_greater);
	int ternary = 0;
	int median = 0;
	int input;

	while(scanf("%d",&input)){
		if(ternary==0){
			if(input <= median){
				below.push(input);
				ternary = -1;
				median = below.top();
			} 
			else{
				above.push(input);
				ternary = 1;
				median = above.top();
			}
			
		} else if(ternary==1){
			if(input <= median){
				below.push(input);
				ternary = 0;
			}
			else{
				above.push(input);
				below.push(above.top());
				above.pop();
				ternary = 0;
			}
			median = (above.top() + below.top())/2;
		} else if(ternary==-1){
			if(input <= median){
				below.push(input);
				above.push(below.top());
				below.pop();
				ternary=0;
			}
			else{
				above.push(input);
				ternary=0;
			}
			median = (above.top() + below.top())/2;
		}
		// if(!above.empty()){
		// 	printf("above: %d\n",above.top());
		// }
		// if(!below.empty()){
		// 	printf("below: %d\n",below.top());
		// }
		// printf("ternary: %d\n",ternary);
		// printf("median: %d\n",median);
		printf("%d\n",median);
	}

	return 0;
}