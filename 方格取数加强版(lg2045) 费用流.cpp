#include <cstdio>
#include <algorithm>

using namespace std;

const int N=51,E=1000000,S=0,T=30000,INF=1e9;

int n=0,a[N][N],k=0;
int edge=0,next[E],to[E],head[E],cap[E],cost[E],flow[E];
int dis[E],prev[E],inq[E],q[E],pos[E],front=0,tail=0;

void addEdge(int u,int v,int c,int w) {
    cap[edge]=c,cost[edge]=w,to[edge]=v,next[edge]=head[u],head[u]=edge++;
    cap[edge]=0,cost[edge]=-w,to[edge]=u,next[edge]=head[v],head[v]=edge++;
    flow[edge-1]=flow[edge-2]=0;
}

//Split a point Link 2 edges cap=1 cost=a[i][j] & cap=k cost=0
//The first point 1~n^2 The second n^2+1~2n^2 
//S=0 T=30000
void build() {
    addEdge(S,1,k,0);
    addEdge(2*n*n,T,k,0);
    for (int i=1;i<=n;++i)
        for (int j=i;j<=n;++j) {
            addEdge(i+(j-1)*n,i+(j-1)*n+n*n,1,a[j][i]);
            addEdge(i+(j-1)*n,i+(j-1)*n+n*n,k,0);
            if (j!=n)
                addEdge(i+(j-1)*n+n*n,i+j*n,k,0);
            if (i!=n)
                addEdge(i+(j-1)*n+n*n,i+1+(j-1)*n,k,0);
            if (i!=j) {
                addEdge(j+(i-1)*n,j+(i-1)*n+n*n,1,a[i][j]);
                addEdge(j+(i-1)*n,j+(i-1)*n+n*n,k,0);
                if (i!=n)
                    addEdge(j+(i-1)*n+n*n,j+i*n,k,0);
                if (j!=n)
                    addEdge(j+(i-1)*n+n*n,j+1+(i-1)*n,k,0);
            }
        }
}

int spfa() {
    for (int i=S;i<=2*n*n;++i)
        dis[i]=-INF;
    dis[T]=-INF;
    prev[T]=-1;
    q[tail++]=S;
    inq[S]=1;
    dis[S]=0;
    while (front<tail) {
        int x=q[front++];
        inq[x]=0;
        for (int i=head[x];i!=-1;i=next[i]) {
            int v=to[i];
            if (cost[i]+dis[x]>dis[v] && flow[i]<cap[i]) {
                dis[v]=cost[i]+dis[x];
                prev[v]=x;
                pos[v]=i;
                if (!inq[v]) {
                    q[tail++]=v;
                    inq[v]=1;
                }
            }

        }
    }
    return prev[T]==-1?0:1;
}

long long mcmf() {
    long long cst=0;
    int f=0;
    while (spfa()) {
        f=INF;
        for (int i=T;i!=S;i=prev[i])
            f=min(f,cap[pos[i]]-flow[pos[i]]);
        cst+=f*dis[T];
        for (int i=T;i!=S;i=prev[i]) {
            flow[pos[i]]+=f;
            flow[pos[i]^1]-=f;
        }
    }
    return cst;
}

int main(void) {
    for (int i=0;i<=E;++i)
        head[i]=-1;
    scanf("%d %d",&n,&k);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            scanf("%d",&a[i][j]);
    build();
    printf("%lld\n",mcmf());
    return 0;
}
