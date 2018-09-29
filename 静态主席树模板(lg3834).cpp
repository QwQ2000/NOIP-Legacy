#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N=200005;

struct Node {
    int v,lc,rc;
}pool[20*N];

int n=0,m=0,a[N],b[N],n2=0,c[N],cnt=0,root[N];

int kth(int x1,int x2,int l,int r,int k) {
    if (l==r)
        return l;
    int mid=(l+r)>>1;
    int x=pool[pool[x2].lc].v-pool[pool[x1].lc].v;
    if (x>=k)
        return kth(pool[x1].lc,pool[x2].lc,l,mid,k);
    else
        return kth(pool[x1].rc,pool[x2].rc,mid+1,r,k-x);
}

void insert(int num,int x1,int x2,int l,int r) {
    pool[x2]=pool[x1];
    ++pool[x2].v;
    if (l==r)
        return;
    int mid=(l+r)>>1;
    if (num<=mid) {
        pool[x2].lc=++cnt;
        insert(num,pool[x1].lc,cnt,l,mid);
    } else {
        pool[x2].rc=++cnt;
        insert(num,pool[x1].rc,cnt,mid+1,r);
    }
}

int main(void) {
    scanf("%d %d",&n,&m);	
    for (int i=1;i<=n;++i) {
        scanf("%d",a+i);	
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    n2=unique(b+1,b+1+n)-b-1;
    for (int i=1;i<=n;++i)
        c[i]=lower_bound(b+1,b+1+n2,a[i])-b;
    for (int i=1;i<=n;++i) {
		++cnt;
        root[i]=cnt;
        insert(c[i],root[i-1],cnt,1,n);
    }
    while (m--) {
        int l=0,r=0,k=0;
        scanf("%d %d %d",&l,&r,&k);
        printf("%d\n",b[kth(root[l-1],root[r],1,n,k)]);
    }
    return 0;
} 
