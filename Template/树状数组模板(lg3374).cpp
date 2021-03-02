#include <cstdio>

using namespace std;

const int N=500005;

int n=0,m=0;
int a[N];

inline int lowBit(int x) {
    return x&-x;
}

inline void plus(int x,int k) {
    while (x<=n) {
        a[x]+=k;
        x+=lowBit(x);
    }	
}

inline int query(int x) {
    int ret=0;
    while (x) {
        ret+=a[x];
        x-=lowBit(x);
    }	
    return ret;
}

int main(void) {
    scanf("%d %d",&n,&m);
    for (int i=1;i<=n;++i) {
        int k=0;
        scanf("%d",&k);
        plus(i,k);
    }
    while (m--) {
        int type=0,x=0,y=0;
        scanf("%d %d %d",&type,&x,&y);
        if (type==1) 
            plus(x,y);
        else
            printf("%d\n",query(y)-query(x-1));
    }
    return 0;
}
