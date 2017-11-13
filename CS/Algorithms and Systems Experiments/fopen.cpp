#include <stdio.h>
int main(){
FILE* fp = fopen("/Users/CharlesBSwarts/Desktop/AlPachino.mpg","r");
printf("%p\n",fp);

FILE* fp2 = fopen("blahblahblah","w");

printf("%p\n",fp2);

}