#include <cstdio>

using namespace std;

typedef long long LL;

const int N=100001;

int n=0,m=0;
LL a[N],tree[N*8],plus[N*8];

inline void pushUp(int rt) {
    tree[rt]=tree[rt<<1]+tree[rt<<1|1];	
}

inline void pushDown(int l,int r,int rt) {
    tree[rt]+=LL(r-l+1)*plus[rt];
    plus[rt<<1]+=plus[rt];
    plus[rt<<1|1]+=plus[rt];
    plus[rt]=0;
}

void build(int l,int r,int rt) {
    if (l==r) 
        tree[rt]=a[l];
    else {
        int mid=(l+r)>>1;
        build(l,mid,rt<<1);
        build(mid+1,r,rt<<1|1);
        pushUp(rt);
    }
}

LL query(int rt,int l,int r,int l0,int r0) {
    pushDown(l,r,rt);
    if (l0<=l && r<=r0) 
        return tree[rt];
    LL ret=0;
    int mid=(l+r)>>1;
    if (l0<=mid)
        ret+=query(rt<<1,l,mid,l0,r0);
    if (r0>mid)
        ret+=query(rt<<1|1,mid+1,r,l0,r0);
    return ret;
}

void change(int rt,int l,int r,int l0,int r0,LL k) {
    if (l0<=l && r<=r0) {
        plus[rt]+=k;
        pushDown(l,r,rt);
    }
    else {
        int mid=(l+r)>>1;
        if (l0<=mid)
            change(rt<<1,l,mid,l0,r0,k);
        if (r0>mid)
            change(rt<<1|1,mid+1,r,l0,r0,k);
        pushDown(l,mid,rt<<1);
        pushDown(mid+1,r,rt<<1|1);
        pushUp(rt);
    }
}

int main(void) {
    scanf("%d %d",&n,&m);
    for (int i=1;i<=n;++i)
        scanf("%lld",a+i);
    build(1,n,1);
    while (m--) {
        int type=0,x=0,y=0;
        scanf("%d %d %d",&type,&x,&y);
        if (type==1) {
            LL k=0;
            scanf("%lld",&k);
            change(1,1,n,x,y,k);
        } else 
            printf("%lld\n",query(1,1,n,x,y));
    }
    return 0;
}
