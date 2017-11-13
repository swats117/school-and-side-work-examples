#include <cstdio>
long long size_one = 1000000;
long long size_two = 10000000;

long long n = 0, a[size_one];

int main() {
    
    for (long long j=0; j<100000)
    {
        n++;
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