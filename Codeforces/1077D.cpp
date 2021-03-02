#include <cstdio>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

const int N=200005;

struct Num{
	int time,val;
}nums[N];

int k,n,a[N],cnt=0,b[N],ans[N],cnt2=0;
map<int,int> m;

bool operator<(Num a,Num b) {
	return a.time>b.time;	
}

int main(void) {
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;++i) {
		scanf("%d",a+i);
		if (m.count(a[i]))
			++m[a[i]];
		else
			m[a[i]]=1;
	} 
	for (auto it=m.begin();it!=m.end();++it) {
		nums[cnt].time=it->second;
		nums[cnt++].val=it->first;
	}
	sort(nums,nums+cnt);
	int l=1,r=n,t=0;
	while (l<=r) {
		t=(l+r)>>1;
		cnt2=0;
		for (int i=0;i<cnt;++i) {
			for (int j=0;j<nums[i].time/t;++j)
				b[cnt2++]=nums[i].val;
			if (cnt2>=k)
				break;	
		}
		if (cnt2>=k) {
			l=t+1;
			memcpy(ans,b,k*sizeof(int));
		} else
			r=t-1;
	}
	for (int i=0;i<k;++i)
		printf((i==k-1)?"%d\n":"%d ",ans[i]);
	return 0;
}
