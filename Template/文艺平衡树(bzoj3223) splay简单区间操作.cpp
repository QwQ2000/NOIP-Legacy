#include <cstdio>
#include <algorithm>

using namespace std;

const int N=100005;

struct Node {
	int v,sz,flag;
	Node *fa,*ch[2];
	
	void pushDown() {
		if (flag) {
			ch[0]->flag^=1;
			ch[1]->flag^=1;
			flag=0;
			swap(ch[0],ch[1]);
		}
	}	

	void pushUp() {
		sz=1+ch[0]->sz+ch[1]->sz;
	}
	
	int dir() {
		return fa->ch[1]==this;
	}	
}pool[N],*null,*root;

int n=0,m=0;
int cnt=1;
int ans[N];

void build(int l,int r,Node* fa,int son) {
	if (l<=r) {
		int mid=(l+r)>>1;
		Node* cur=pool+cnt++;
		cur->fa=fa;
		if (fa!=null)
			fa->ch[son]=cur;
		cur->flag=0;
		cur->v=mid;
		cur->ch[0]=cur->ch[1]=null;
		cur->sz=1;
		build(l,mid-1,cur,0);
		build(mid+1,r,cur,1);
		cur->pushUp();	
	}	
}

inline void init() {
	root=pool+1;
	null=pool;
	null->v=null->sz=null->flag=0;
	null->fa=null->ch[0]=null->ch[1]=null;
	build(0,n+1,null,0);	
} 

void dfs(Node* p) {
	if (p!=null) {	
		p->pushDown();
		dfs(p->ch[0]);
		if (p->v!=0 && p->v!=n+1)
			ans[cnt++]=p->v;
		dfs(p->ch[1]);
	}
}

inline void print() {
	cnt=1;
	dfs(root);
	for (int i=1;i<=n;++i)
		printf(i==n?"%d\n":"%d ",ans[i]);	
}

inline void rotate(Node* p) {
	Node *fa=p->fa,*gr=fa->fa;
	int d1=p->dir(),d2=fa->dir();
	p->fa=gr;
	if (gr!=null) 
		gr->ch[d2]=p;
	fa->ch[d1]=p->ch[d1^1];
	p->ch[d1^1]->fa=fa;
	p->ch[d1^1]=fa;
	fa->fa=p;
	if (p->fa==null)
		root=p;
	fa->pushUp();
	p->pushUp();
}

void splay(Node* p,Node* fa) {
	p->pushDown();
	while (p->fa!=fa) {
		if (p->fa->fa==fa)
			rotate(p);
		else if (p->fa->dir()==p->dir()) {
			rotate(p->fa);
			rotate(p);
		} else {
			rotate(p);
			rotate(p);
		}
	}
}

Node* find(int x,Node* cur) {
	cur->pushDown();
	if (cur->ch[0]->sz==x)
		return cur;
	else if (cur->ch[0]->sz<x)
		find(x-cur->ch[0]->sz-1,cur->ch[1]);
	else
		find(x,cur->ch[0]);
}

inline void reverse(int l,int r) {
	splay(find(l-1,root),null);
	splay(find(r+1,root),root);
	root->ch[1]->ch[0]->flag^=1;
}

int main(void) {
	scanf("%d %d",&n,&m);
	init();	
	while (m--) {
		int l=0,r=0;
		scanf("%d %d",&l,&r);
		reverse(l,r);
	}
	print();
	return 0;
} 
