#include <cstdio>
int n = 0, a[10001];

int main() {
//    FileIn("test"); FileOut("test");
    while (scanf("%d", &a[++n])!=EOF) {
        for (int i=n-1; i>=1; i--)
            if (a[i] > a[i+1]){
            	int temp = a[i];
            	a[i]=a[i+1];
            	a[i+1]=temp;
            } 
            else break;
        if (n%2) printf("%d\n", a[(n+1)/2]);
        else printf("%d\n", (a[n/2] + a[n/2+1])/2);
    }
    return 0;
}