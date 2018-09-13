#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct edge {
    int u,v,c,f;
    edge() { }
    edge(int a,int b,int cc,int d):u(a),v(b),c(cc),f(d) { };
};

const int N=1001,INF=int(1e9),s=0,t=1000;

int n=0,p=0,q=0,room[N][N],dish[N][N],f[N],prev[N],d[N],vis[N],cur[N];
vector<edge> e;
vector<int> g[N];
int exist[N][N];

inline void addEdge(int u,int v,int c=1) {
    if (exist[u][v])
        return;
    e.push_back(edge(u,v,c,0));
    e.push_back(edge(v,u,0,0));
    g[u].push_back(e.size()-2);
    g[v].push_back(e.size()-1);
    exist[u][v]=1;
}

inline void build() {
    //S:0 T:1000
    //Room 1~p Customer p+1~p+n p+n+1~p+2n Dish p+2n+1~p+2n+q
    for (int i=1; i<=p; ++i)
        addEdge(0,i);
    for (int i=1; i<=p; ++i)
        for (int j=1; j<=n; ++j)
            if (room[j][i])
                addEdge(i,p+j);
    for (int i=1; i<=n; ++i)
        addEdge(p+i,p+n+i);
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=q; ++j)
            if (dish[i][j]) {
                addEdge(p+n+i,p+2*n+j);
                addEdge(p+2*n+j,1000);
            }
}

int bfs() {
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    queue<int> q;
    d[s]=1;
    vis[s]=1;
    q.push(s);
    while (!q.empty()) {
        int x=q.front();
        q.pop();
        for (int i=0;i<g[x].size();++i) {
            edge e0=e[g[x][i]];
            if (!vis[e0.v] && e0.c>e0.f) {
                vis[e0.v]=1;
                q.push(e0.v);
                d[e0.v]=d[x]+1;
            }
        }
    }
    return vis[t];
}

int dfs(int x,int a) {
    if (x==t || a==0)
        return a;
    int flow=0,f=0;
    for (int& i=cur[x];i<g[x].size();++i) {
        edge& e0=e[g[x][i]];
        if (d[x]+1==d[e0.v] && (f=dfs(e0.v,min(a,e0.c-e0.f)))>0) {
            e0.f+=f;
            e[g[x][i]^1].f-=f;
            flow+=f;
            a-=f;
            if (a==0)
                break;
        }
    }
    return flow;
}

int maxFlow() {
    int flow=0;
    while (bfs()) {
        memset(cur,0,sizeof(cur));
        flow+=dfs(s,INF);
    }
    return flow;
}

int main(void) {
    scanf("%d %d %d",&n,&p,&q);
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=p; ++j)
            scanf("%d",&room[i][j]);
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=q; ++j)
            scanf("%d",&dish[i][j]);
    build();
    printf("%d\n",maxFlow());
    return 0;
}

