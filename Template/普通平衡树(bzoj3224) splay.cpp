#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;

const int N=100001,INF=LONG_MAX-10;

struct SplayNode {
    long val;
    int size,cnt;
    SplayNode *fa,*ch[2];
    void setChild(int,SplayNode*);
    void pushUp() {
        size=ch[0]->size+ch[1]->size+cnt;
    }
    int getPos() {
        return this==fa->ch[0]?0:1;
    }
}pool[N],*root,*null;

int n=0,top=1;

void SplayNode::setChild(int son,SplayNode* child) {
    ch[son]=child;
    if (child!=null)
        child->fa=this;
    pushUp();
}

void init() {
    null=pool;
    pool[0].size=pool[0].cnt=0;
    pool[0].fa=pool[0].ch[0]=pool[0].ch[1]=null;
    root=null;
}

void rotate(SplayNode*& cur) {
    SplayNode *fa=cur->fa,*grand=cur->fa->fa;
    int son=cur->getPos();
    fa->setChild(son,cur->ch[son^1]);
    cur->setChild(son^1,fa);
    cur->fa=grand;
    if (grand!=null)
        grand->ch[grand->ch[0]==fa?0:1]=cur;
}

void splay(SplayNode* cur,SplayNode* tar) {
    for (;cur->fa!=tar;rotate(cur))
        if (cur->fa->fa!=tar)
            cur->getPos()==cur->fa->getPos()?rotate(cur->fa):rotate(cur);
    if (tar==null)
        root=cur;
}

SplayNode* getNode(long val) {
    SplayNode* node=&pool[top++];
    node->val=val;
    node->size=node->cnt=1;
    node->fa=node->ch[0]=node->ch[1]=null;
    return node;
}

void insert(long val) {
    SplayNode *fa=null,*cur=root,*node=getNode(val);
    while (cur!=null) {
        fa=cur;
        if (cur->val==val) {
            cur->size+=1;
            cur->cnt+=1;
            splay(cur,null);
            return;
        }
        if (cur->val<val)
            cur=cur->ch[1];
        else
            cur=cur->ch[0];
    }
    if (fa==null)
        root=node;
    else {
        if (fa->val<val)
            fa->setChild(1,node);
        else
            fa->setChild(0,node);
        splay(node,null);
    }
}

SplayNode* find(long val) {
    SplayNode* cur=root;
    while (cur!=null) {
        if (cur->val==val)
            break;
        if (cur->val<val)
            cur=cur->ch[1];
        else
            cur=cur->ch[0];
    }
    if (cur!=null)
        splay(cur,null);
    return cur;
}

void erase(long val) {
    SplayNode* node=find(val);
    if (node==null)
        return;
    if (node->cnt>1) {
        node->cnt-=1;
        node->size-=1;
        return;
    }
    if (node->ch[0]!=null && node->ch[1]!=null) {
        SplayNode* maxNode=node->ch[0];
        while (maxNode->ch[1]!=null)
            maxNode=maxNode->ch[1];
        splay(maxNode,node);
        maxNode->setChild(1,node->ch[1]);
        maxNode->fa=null;
        root=maxNode;
    }
    else if (node->ch[0]==null && node->ch[1]==null)
        root=null;
    else {
        int son=node->ch[0]!=null?0:1;
        root=node->ch[son];
        node->ch[son]->fa=null;
    }
}

int getRank(long val) {
    SplayNode* cur=root;
    int lsize=0;
    while (cur!=null) {
        if (cur->val==val) {
            int ans=lsize+cur->ch[0]->size+1;
            splay(cur,null);
            return ans;
        }
        else if (cur->val>val)
            cur=cur->ch[0];
        else {
            lsize+=cur->ch[0]->size+cur->cnt;
            cur=cur->ch[1];
        }
    }
    return -1;
}

long getKth(int k) {
    SplayNode* cur=root;
    int lsize=0;
    while (cur!=null) {
        int x=lsize+cur->ch[0]->size;
        if (x+1<=k && k<=x+cur->cnt) {
            splay(cur,null);
            return cur->val;
        }
        if (k<=x)
            cur=cur->ch[0];
        else {
            lsize=x+cur->cnt;
            cur=cur->ch[1];
        }
    }
    return -1;
}

long prev(long val) {
    SplayNode* cur=root;
    long ans=-INF;
    while (cur!=null) {
        if (cur->val>=val)
            cur=cur->ch[0];
        else {
            ans=max(ans,cur->val);
            cur=cur->ch[1];
        }
    }
    return ans;
}

long next(long val) {
    SplayNode* cur=root;
    long ans=INF;
    while (cur!=null) {
        if (cur->val<=val)
            cur=cur->ch[1];
        else {
            ans=min(ans,cur->val);
            cur=cur->ch[0];
        }
    }
    return ans;
}

int main(void) {
    init();
    scanf("%d",&n);
    int opt=0;
    long x=0;
    for (int i=0;i<n;++i) {
        scanf("%d %ld",&opt,&x);
        switch (opt) {
            case 1:{
                insert(x);
                break;
            }
            case 2:{
                erase(x);
                break;
            }
            case 3:{
                printf("%d\n",getRank(x));
                break;
            }
            case 4:{
                printf("%ld\n",getKth(x));
                break;
            }
            case 5:{
                printf("%ld\n",prev(x));
                break;
            }
            case 6:{
                printf("%ld\n",next(x));
                break;
            }
        }
    }
    return 0;
}

