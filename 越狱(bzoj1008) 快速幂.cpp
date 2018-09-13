#include <cstdio>

using namespace std;

typedef long long LL;

const int P=100003;

LL n=0,m=0;

LL pow(LL a,LL b) {
	LL ans=1;
	for (LL i=b;i;a=a*a%P,i>>=1)
		if (i&1)
			ans=ans*a%P;
	return ans;	
}

int main(void) {
	scanf("%lld %lld",&m,&n);
	printf("%lld\n",(pow(m,n)+P-(m%P*pow(m-1,n-1)%P)%P)%P);	
	return 0;
} 
