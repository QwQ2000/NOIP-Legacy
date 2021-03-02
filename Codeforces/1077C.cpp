#include <cstdio>

using namespace std;

typedef long long LL;

const int N=200005;

int n,a[N],mx,mxPos,mx2,ans[N],cnt;
LL sum;

int main(void) {
	scanf("%d",&n);
	for (int i=1;i<=n;++i) {
		scanf("%d",a+i);	
		sum+=a[i];
		if (a[i]>=mx) {
			if (mx>=mx2) 
				mx2=mx;
			mx=a[i];
			mxPos=i;
		} else if (a[i]>=mx2)
			mx2=a[i];
	}
	if (sum-mx==mx2*2)
		ans[cnt++]=mxPos;
	for (int i=1;i<=n;++i)
		if (i!=mxPos && sum-a[i]==mx*2)
			ans[cnt++]=i;
	printf("%d\n",cnt);
	for (int i=0;i<cnt;++i)
		printf((i==cnt-1)?"%d\n":"%d ",ans[i]);
	return 0;
} 
