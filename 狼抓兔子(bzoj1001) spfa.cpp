#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long LL;

const int N=1233;
const LL INF=1e17;

int n=0,m=0;
LL e1[N][N],e2[N][N],e3[N][N];
int head[2000005],next[6000001],to[6000001],edge=0;
LL w[6000001];
int s=0,t=0;
queue<int> q;
LL dis[2000005];
int inq[2000005];

inline void addEdge(int u,int v,LL argw) {
	w[edge]=argw,to[edge]=v,next[edge]=head[u],head[u]=edge++;
	w[edge]=argw,to[edge]=u,next[edge]=head[v],head[v]=edge++;
}

inline void build() {
	/*总面数2(n-2)(m-2) 附加面编号2(n-2)(m-2)+1 +2 
	**第i行第j列的左下角编号为j+2j(i-1) 右上角编号为j+2j(i-1)+1 
	*/
	memset(head,-1,sizeof(head));
	s=2*(n-1)*(m-1)+1,t=2*(n-1)*(m-1)+2;
	for (int i=1;i<=n-1;++i)
		for (int j=1;j<=m-1;++j) {
			//左下角 
			int num=2*(i-1)*(m-1)+j*2-1;
			//左下角连左边 
			if (j==1) 
				addEdge(s,num,e2[i][j]);
			else
				addEdge(num-1,num,e2[i][j]);
			//左下角连下边 
			if (i==n-1)
				addEdge(num,s,e1[i+1][j]);
			else
				addEdge(num,num+2*(m-1)+1,e1[i+1][j]);
			//左下角连右上角 
			addEdge(num,num+1,e3[i][j]);
			//右上角 
			++num;	
			//右上角连上边
			if (i==1) 
				addEdge(num,t,e1[i][j]);
			//右上角连左下角
			if (j==m-1)
				addEdge(num,t,e2[i][j+1]);
		}	
}

LL spfa(int s,int t) {
	for (int i=1;i<=t;++i)
		dis[i]=INF;
	q.push(s);
	inq[s]=1;
	dis[s]=0;
	while (!q.empty()) {
		int x=q.front();
		q.pop();
		inq[x]=0;
		for (int e=head[x];~e;e=next[e]) {
			int& v=to[e];
			LL& w0=w[e];
			if (dis[v]>dis[x]+w0) {
				dis[v]=dis[x]+w0;
				if (!inq[v]) {
					q.push(v);
					inq[v]=1;
				}
			}
			
		}
	}
	return dis[t];
}

int main(void) {
	scanf("%d %d",&n,&m);
	if (n==1) {
		LL mn=INF;
		while (--m) {
			LL x=0;
			scanf("%lld",&x);
			mn=min(mn,x);
		}
		printf("%lld\n",mn);
		exit(0);
	} else if (m==1) {
		LL mn=INF;
		while (--n) {
			LL x=0;
			scanf("%lld",&x);
			mn=min(mn,x);
		}
		printf("%lld\n",mn);
		exit(0);
	}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m-1;++j)
			scanf("%lld",&e1[i][j]);
	for (int i=1;i<=n-1;++i)
		for (int j=1;j<=m;++j)
			scanf("%lld",&e2[i][j]);
	for (int i=1;i<=n-1;++i)
		for (int j=1;j<=m-1;++j)
			scanf("%lld",&e3[i][j]);
	build();
	printf("%lld\n",spfa(s,t));
	return 0;
} 

