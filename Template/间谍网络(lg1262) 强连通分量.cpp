#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=3005,R=8005,INF=1e9;

int n=0,p=0,r=0;
int num[N],price[N];
int head[N],to[R],next[R],edge=0;
int q[N*N],front=0,back=0;
int vis[N];
int idx=0;
int stk[N],top=0;
int low[N],dfn[N];
int comp[N];
int n2=0;
int in[N];
int mn[N];

inline void addEdge(int u,int v) {
    to[edge]=v,next[edge]=head[u],head[u]=edge++;
}

inline void bfs() {
    while (front<back) {
        int x=q[front++];
        for (int e=head[x];~e;e=next[e]) {
            int& v=to[e];
            if (!vis[v]) {
                q[back++]=v;
                vis[v]=1;
            }
        }
    }
}

inline void tarjan(int x) {
    dfn[x]=low[x]=++idx;
    stk[top++]=x;
    vis[x]=1;
    for (int e=head[x];~e;e=next[e]) {
        int& v=to[e];
        if (!dfn[v]) {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        } else if (vis[v])
            low[x]=min(low[x],dfn[v]);
    }
    int u=0;
    if (low[x]==dfn[x]) {
        ++n2;
        do {
            u=stk[--top];
            comp[u]=n2;
            vis[u]=0;    
        } while (u!=x);
    }
}

int main(void) {
    memset(head,-1,sizeof(head));
    scanf("%d %d",&n,&p);
    for (int i=1;i<=p;++i)
        scanf("%d %d",num+i,price+i),q[back++]=num[i],vis[num[i]]=1;
    scanf("%d",&r);
    for (int i=1;i<=r;++i) {
        int u=0,v=0;
        scanf("%d %d",&u,&v);
        addEdge(u,v);
    }
    bfs();
    for (int i=1;i<=n;++i)
        if (!vis[i]) {
            printf("NO\n%d\n",i);
            exit(0);
        }
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=n;++i)
        if (!dfn[i])
            tarjan(i);
    for (int i=1;i<=n;++i)
    	for (int e=head[i];~e;e=next[e]) {
    		int u=comp[i],v=comp[to[e]];
    		if (u!=v)
    			++in[v];
    	}
    for (int i=1;i<=n2;++i)
    	mn[i]=INF;
    for (int i=1;i<=p;++i)
    	mn[comp[num[i]]]=min(mn[comp[num[i]]],price[i]);
    int ans=0;
    for (int i=1;i<=n;++i) 
        if (!in[i] && mn[i]!=INF)
            ans+=mn[i];
    printf("YES\n%d\n",ans);
    return 0;
} 

