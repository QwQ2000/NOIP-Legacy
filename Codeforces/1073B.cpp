#include <cstdio>

using namespace std;

const int N=200005;

int in[N],a[N],n,b,ans,top=1,cur;

int main(void) {
	scanf("%d",&n);	
	for (int i=1;i<=n;++i) {
		scanf("%d",a+i);
		in[a[i]]=1;
	}
	for (int i=1;i<=n;++i) {
		scanf("%d",&b);
		ans=0;
		if (in[b])
			do {
				cur=a[top++];
				++ans;
				in[cur]=0;
			} while (in[b]);
		printf(i==n?"%d\n":"%d ",ans);
	}
	return 0;
} 
