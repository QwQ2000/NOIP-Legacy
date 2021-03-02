#include <cstdio>
#include <algorithm>
#include <vector>

const int N=100005;

using namespace std;

int n,m,cnt[N];
vector<int> a[N];

int main(void) {
	scanf("%d%d",&n,&m);
	int m0,s;
	for (int i=1;i<=n;++i) {
		scanf("%d%d",&m0,&s);
		a[m0].push_back(s);
	}
	int mx=-1;
	for (int i=1;i<=m;++i) {
		mx=max(int(a[i].size()),mx);
		sort(a[i].begin(),a[i].end(),[](int x,int y){return x>y;});
		for (int j=1;j<a[i].size();++j)
			a[i][j]+=a[i][j-1];
	}
	sort(a+1,a+1+m,[](vector<int> x,vector<int> y){return x.size()>y.size();});
	int ans=0,j=1;
	for (int i=mx-1;i>-1;--i) {
		s=0;
		while (i<a[j].size()) 
			++j;
		for (int k=1;k<j;++k)
			if (a[k][i]>0)
				s+=a[k][i]; 
		ans=max(s,ans);
	}
	printf("%d\n",ans);
	return 0;
}
