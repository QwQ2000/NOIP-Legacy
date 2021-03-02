#include <cstdio>
#include <algorithm>

using namespace std;

const int N=100005;

int n,k,a[N];

int main(void) {
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;++i)
		scanf("%d",a+i);
	sort(a,a+n);
	int n2=unique(a,a+n)-a;
	int sum=0;
	for (int i=0;i<k;++i)
		if (i>=n2)
			printf("0\n");
		else {
			printf("%d\n",a[i]-sum);
			sum+=a[i]-sum;
		}	
	return 0;
}
