#include <cstdio>

int main(){

	int number;
	while(scanf("%d",&number) && number !=0){

		int number1 = 0;
		int number2 = 0;
		bool number1turn = true;

		for(int i=31; i>=0; i--){
			if((number>>i)&1){
				if(number1turn==true){
					number1+= 1<<(i);
					number1turn=false;
				} else {
					number1turn=true;
				}
			} 
		}
		number2 = number - number1;

		if(number1turn) printf("%d %d\n", number2, number1);
		else printf("%d %d\n", number1, number2);



	}


	return 0;
}