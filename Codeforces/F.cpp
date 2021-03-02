#include <bits/stdc++.h>

using namespace std;

const int N=1005,L=6*N+3;
const int WX[]={2,-2,1,1,-1,-1},WY[]={0,0,3,-3,3,-3},D=6;//下，上，右下，左下，右上，左上 

struct Point {
	int x,y,d;
	Point() { }
	Point(int x0,int y0,int d0):x(x0),y(y0),d(d0) { }
};

int r,c,sx,sy,tx,ty;
char a[L][L],line[L];
int vis[N][N];
queue<Point> q;
 
inline void centre(int x,int y,int& outx,int& outy) {
	if (y&1)
		outx=4*x-1;
	else 
		outx=4*x+1;
	outy=6*y-1;
}
	
inline int nextCell(int x,int y,int wall,int& outx,int& outy) {
	switch (wall) {
		case 0:
			if (x==r)
				return 1;
			++x;	
			break;
		case 1:
			if (x==1)
				return 1;
			--x;
			break;
		case 2:
			if (y==c)
				return 1;
			if (y&1) {
				if (x==r)
					return 1;
				++y;	
			} else {
				++y;
				++x;
			}
			break;
		case 3:
			if (y==1)
				return 1;
			if (y&1) {
				if (x==r)
					return 1;
				--y;	
			} else {
				--y;
				++x;
			}
			break;
		case 4:
			if (y==c)
				return 1;
			if (y&1) {
				if (x==1)
					return 1;
				--x;
				++y;
			} else
				++y;
			break;
		case 5:
			if (y==1)
				return 1;
			if (y&1) {
				if (x==1)
					return 1;
				--x;
				--y;
			} else
				--y;
	}
	outx=x;
	outy=y;
	return 0;
}

inline int isAccessible(int x,int y,int wall) {
	int cx,cy;
	centre(x,y,cx,cy);
	if (a[cx+WX[wall]][cy+WY[wall]]==' ')
		return 1;
	return 0;
}

void bfs() {
	q=queue<Point>();
	for (int i=1;i<=r;++i)
		for (int j=1;j<=c;++j)
			vis[i][j]=0;
	vis[sx][sy]=1;
	q.push(Point(sx,sy,1));
	while (!q.empty()) {
		Point& p=q.front();
		int x=p.x,y=p.y,d=p.d,x2,y2;
		q.pop();
		if (x==tx && y==ty) {
			printf("%d\n",d);
			return;
		}
		for (int i=0;i<D;++i)
			if (!nextCell(x,y,i,x2,y2)) {
				if (isAccessible(x,y,i) && !vis[x2][y2]) {
					q.push(Point(x2,y2,d+1));
					vis[x2][y2]=1;
				}
			}
	}
	printf("-1\n");
}

int main(void) {
	int t=0;
	scanf("%d",&t);
	while (t--) {
		scanf("%d%d",&r,&c);
		for (int i=0;i<=r*4+3;++i)
			cin.getline(&a[i][1],L);	
		for (int i=1;i<=r;++i)
			for (int j=1;j<=c;++j) {
				int x,y;
				centre(i,j,x,y);
				if (a[x][y]=='S') {
					sx=i;
					sy=j;
				}
				else if (a[x][y]=='T') {
					tx=i;
					ty=j;
				}
			}
		bfs();
	}	
	return 0;
} 
