#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=300005;

int n=0;
int a[N];
int head[N*2],next[N*2],to[N*2],edge=0;
int depth[N],sz[N],id[N],son[N],num[N],fa[N],top[N],rank[N],yts=1;
int sum[N*8],flag[N*8];

inline void addEdge(int u,int v) {
    to[edge]=v,next[edge]=head[u],head[u]=edge++;
    to[edge]=u,next[edge]=head[v],head[v]=edge++;
}

void dfs1(int x,int f,int d) {
    depth[x]=d;
    sz[x]=1;
    fa[x]=f;
    for (int e=head[x];~e;e=next[e]) {
        int& v=to[e];
        if (v!=f) {
            dfs1(v,x,d+1);
            sz[x]+=sz[v];
            if (son[x]==-1 || sz[son[x]]<sz[v])
                son[x]=v; 
        }
    }
}

void dfs2(int x,int t) {
    top[x]=t;
    id[x]=yts++;
    rank[id[x]]=x;
    if (son[x]==-1) 
         return;  
    dfs2(son[x],t);
    for (int e=head[x];~e;e=next[e]) {
        int& v=to[e];
        if (v!=fa[x] && v!=son[x])
            dfs2(v,v);
    }
}

inline void pushUp(int rt) {
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

inline void pushDown(int rt,int l,int r) {
    sum[rt]+=(r-l+1)*flag[rt];
    flag[rt<<1]+=flag[rt];
    flag[rt<<1|1]+=flag[rt];
    flag[rt]=0;
}

void update(int rt,int l,int r,int d,int l0,int r0) {
    if (l0>r0)
        swap(l0,r0);
    if (l0<=l && r<=r0) {
        flag[rt]+=d;
        pushDown(rt,l,r);
    } else {
        int mid=(l+r)>>1;
        if (l0<=mid)
            update(rt<<1,l,mid,d,l0,r0);
        if (r0>mid)
            update(rt<<1|1,mid+1,r,d,l0,r0);
        pushDown(rt<<1,l,mid);
        pushDown(rt<<1|1,mid+1,r);
        pushUp(rt);
    }
}

int query(int rt,int l,int r,int x) {
    pushDown(rt,l,r);
    if (l==r) {
        return sum[rt];
    }        
    int mid=(l+r)>>1;
    if (x<=mid)
        return query(rt<<1,l,mid,x);
    if (x>mid)
        return query(rt<<1|1,mid+1,r,x);
}

inline void change(int x,int y,int d) {
    while (top[x]!=top[y]) {
        if (depth[top[x]]<depth[top[y]])
            swap(x,y);
        update(1,1,n,d,id[x],id[top[x]]);
        x=fa[top[x]];
    }
    if(depth[x]>depth[y]) 
        swap(x,y);  
    update(1,1,n,d,id[x],id[y]);  
}

int main(void) {
    memset(head,-1,sizeof(head));
    memset(son,-1,sizeof(son));
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        scanf("%d",a+i);
    for (int i=1;i<=n-1;++i) {
        int u=0,v=0;
        scanf("%d %d",&u,&v);
        addEdge(u,v);
    }        
    dfs1(1,-1,1);
    dfs2(1,-1);
    for (int i=1;i<=n-1;++i) { 
        change(a[i],a[i+1],1);
    } 
    for (int i=1;i<=n;++i) {
        int ret=query(1,1,n,id[i]);
        if (!ret)
            printf("0\n");
        else
            printf("%d\n",i!=a[1]?(ret-1):ret);
    }
    return 0;
}

