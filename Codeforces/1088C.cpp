#include <cstdio>
#include <cstdlib>

using namespace std;

const int N=2018;

int n=0,a[N],cnt=0,ans1[N],ans2[N],ans3[N];

void plus(int i,int x) {
	ans1[cnt]=1;
	ans2[cnt]=i;
	ans3[cnt++]=x;
	for (int j=1;j<=i;++j)
		a[j]=a[j]+x;
}

int main(void) {
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",a+i);
	int flag=1;
	*a=-1;
	for (int i=1;i<=n;++i)
		if (a[i]<=a[i-1]) {
			flag=0;
			break;
		}
	if (flag) {
		printf("0\n");
		exit(0);
	}
	if (a[n]<n-1)
		plus(n,n-1-a[n]);
	for (int i=n-1;i>0;--i) {
		int mod=a[i]%a[n],g=a[n]-n+i;
		if (mod<g)
			plus(i,g-mod);
		else if (mod>g)
			plus(i,a[n]+g-mod);
	}
	printf("%d\n",cnt+1);
	for (int i=0;i<cnt;++i)
		printf("%d %d %d\n",ans1[i],ans2[i],ans3[i]);
	printf("2 %d %d",n-1,a[n]);
	return 0;
}
