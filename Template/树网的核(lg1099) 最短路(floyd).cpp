#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N=305,INF=1e9;

int n=0,s=0;
int head[N],next[N*2],to[N*2],w[N*2],edge=0;
int dis[N][N];
int vis[N],yts=0;
int path[N],len=0,pathLen=0;
int flag[N];
int dis2[N];

inline void init() {
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            dis[i][j]=INF;
    for (int i=1;i<=n;++i)
        dis[i][i]=0;
    memset(head,-1,sizeof(head));
}

inline void addEdge(int u,int v,int argw) {
    w[edge]=argw,to[edge]=v,next[edge]=head[u],head[u]=edge++;
    w[edge]=argw,to[edge]=u,next[edge]=head[v],head[v]=edge++;
    dis[u][v]=dis[v][u]=argw;
}

inline void floyd() {
    for (int k=1;k<=n;++k)
        for (int i=1;i<=n;++i)
            for (int j=1;j<=n;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}

void dfs(int x,int t,int depth) {
    if (yts)
        return;
    path[depth]=x;
    if (x==t) {
        len=depth;
        yts=1;
        return;
    }
    for (int e=head[x];~e;e=next[e]) {
        int& v=to[e];
        if (!vis[v]) {
            vis[v]=1;
            dfs(v,t,depth+1);
            vis[v]=0;
        }
    }
}
    
int main(void) {
    scanf("%d %d",&n,&s);
    init();
    for (int i=1;i<=n-1;++i) {
        int u=0,v=0,w=0;
        scanf("%d %d %d",&u,&v,&w);
        addEdge(u,v,w);
    }
    floyd();
    int maxd=0,s2=0,t=0;
    for (int i=1;i<=n-1;++i)
        for (int j=i+1;j<=n;++j)
            if (dis[i][j]>maxd) {
                maxd=dis[i][j];
                s2=i;
                t=j;
            }
    vis[s2]=1;
    dfs(s2,t,1);
    for (int i=1;i<=len;++i) 
        flag[path[i]]=1;
    int ans=INF;
    for (int i=1;i<=len;++i)
        for (int j=i;j<=len;++j) {
            int sum=0;
            for (int k=i;k<=j-1;++k)
                sum+=dis[path[k]][path[k+1]];
            if (sum>s)
                break;
            int ecc=0,ecc0=0;
            for (int k=1;k<=n;++k) {                                                  
                ecc0=INF;
                for (int l=i;l<=j;++l)
                    ecc0=min(ecc0,dis[k][path[l]]);
                ecc=max(ecc,ecc0);	
            }	
            if (ecc)
                ans=min(ans,ecc);
        }
    printf("%d\n",ans);
    return 0;
}

