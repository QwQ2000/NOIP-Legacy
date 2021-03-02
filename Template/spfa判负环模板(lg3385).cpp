#include <cstdio>
#include <cstring>

using namespace std;

const int N=200005,INF=1e9;

int t=0;
int n=0,m=0;
int head[N],to[N*2],next[N*2],w[N*2],edge=0;
int vis[N],dis[N],flag=0;

inline void addEdge(int u,int v,int w0) {
    to[edge]=v,w[edge]=w0,next[edge]=head[u],head[u]=edge++;
    if (w0>=0)
        to[edge]=u,w[edge]=w0,next[edge]=head[v],head[v]=edge++;
}

void spfa(int x) {
    if (flag)
        return;
    vis[x]=1;
    for (int e=head[x];~e;e=next[e]) {
        if (flag)
            return;
        int &v=to[e],&w0=w[e];
        if (dis[x]+w0<dis[v]) {
            dis[v]=dis[x]+w0;
            if (vis[v]) {
                flag=1;
                return;
            } else 
                spfa(v);			
        }
    }
    vis[x]=0;
}
int main(void) {
    scanf("%d",&t);
    while (t--) {
        edge=0;
        flag=0;
        memset(head,-1,sizeof(head));
        memset(to,0,sizeof(to));
        memset(next,0,sizeof(next));
        memset(w,0,sizeof(w));
        scanf("%d %d",&n,&m);
        while (m--) {
            int u=0,v=0,w0=0;
            scanf("%d %d %d",&u,&v,&w0);
            addEdge(u,v,w0);
        }		
        memset(vis,0,sizeof(vis));
        memset(dis,0,sizeof(dis));
        for (int i=1;i<=n;++i) {
            spfa(i);
            if (flag)
                break;
        }
        printf(flag?"YE5\n":"N0\n");		
    }
    return 0;
} 
