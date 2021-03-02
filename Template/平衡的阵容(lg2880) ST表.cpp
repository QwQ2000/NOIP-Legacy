#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=50001;

int n=0,q=0;
int mx[N][20],mn[N][20];

void init() {
    int m=log(n)/log(2);
    for (int i=1;i<=m;++i)
        for (int j=n;j>0;--j) {
            mx[j][i]=mx[j][i-1];
            mn[j][i]=mn[j][i-1];
            if (j+(1<<(i-1))<=n) {
                mx[j][i]=max(mx[j][i],mx[j+(1<<(i-1))][i-1]);
                mn[j][i]=min(mn[j][i],mn[j+(1<<(i-1))][i-1]);
            }
        }
}

int query(int b,int e) {
    int m=log(e-b+1)/log(2);
    int x1=max(mx[b][m],mx[e-(1<<m)+1][m]),x2=min(mn[b][m],mn[e-(1<<m)+1][m]);
    return x1-x2;
}

int main(void) {
    scanf("%d %d",&n,&q);
    for (int i=1;i<=n;++i) {
        scanf("%d",&mx[i][0]);
        mn[i][0]=mx[i][0];
    }
    init();
    while (q--) {
        int b=0,e=0;
        scanf("%d %d",&b,&e);
        printf("%d\n",query(b,e));
    }
    return 0;
}

