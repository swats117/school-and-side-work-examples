#include <cstdio>

int main(){
	
	const char* input = "A";
	int key = 23;

	if(key>255 || key<0){
		printf("invalid key\n");
		exit();
	}

	for(int i=0; i<strlen(flag); i++){
		printf("%c",flag[i]);
	}

	return 0;
}

void enc(char* flag, int key){
	while(*flag){
		key = (key*13)+37;
		printf("%d",key);
		*flag ^= key;
		*(flag++) += 3;
	}
}