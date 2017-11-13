#include <stdio.h>

int main(){
	
	int c = 0xdeadbeef;
	printf("%x\n",c);
	char buf[12];
	buf[11] = '\0';
	gets(buf);
	printf("%x\n",c);
	printf("%s",buf);

	return 0;
}