#include <cstdio>
#include <time.h>
#include <queue>

int main(){
	
	printf("begin\n");
	auto comp_less = [] (long long &a, long long &b) -> bool { return a > b; };
	std::priority_queue <long long,std::vector<long long>,decltype(comp_less)> above (comp_less);
	std::priority_queue <long long,std::vector<long long>,decltype(comp_less)> above2 (comp_less);

	clock_t t1, t2;

	t1=clock();
	for(long long i=0; i<1000000; i++){
		above.push(i);
	}
	t2=clock();

	printf("time for 1000000: %f\n",(float)t2-(float)t1);

	t1=clock();
	for(long long i=0; i<10000000; i++){
		above2.push(i);
	}
	t2=clock();

	printf("time for 10000000: %f\n",(float)t2-(float)t1);

	t1=clock();
	for(long long i=0; i<100000000; i++){
		above2.push(i);
	}
	t2=clock();

	printf("time for 100000000: %f\n",(float)t2-(float)t1);

	t1=clock();
	for(long long i=0; i<1000000000; i++){
		above2.push(i);
	}
	t2=clock();

	printf("time for 1000000000: %f\n",(float)t2-(float)t1);


	return 0;
}