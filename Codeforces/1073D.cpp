#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N=200005;

int n,cnt;
LL t,s,a[N],ans;

int main(void) {
	scanf("%d%I64d",&n,&t);	
	for (int i=1;i<=n;++i)
		scanf("%d",a+i);
	while (1) {
		s=cnt=0;
		for (int i=1;i<=n;++i)
			if (t>=a[i]) {
				t-=a[i];
				s+=a[i];
				++cnt;
			}
		if (!cnt)
			break;
		ans+=cnt+t/s*LL(cnt);
		t%=s;
	}
	printf("%I64d\n",ans);
	return 0;
}
