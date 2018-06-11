#include <bits/stdc++.h>

const int max_N = 5e5 + 21;

#define ls(x) ((x)<<1)
#define rs(x) (ls(x)|1)
#define mid ((l+r)>>1)
#define lch ls(x),l,mid
#define rch rs(x),mid+1,r

int n,K,p[max_N],q[max_N],seg[max_N<<2],pos[max_N],ans[max_N];

bool vis[max_N];

std::priority_queue<int>pq;

inline void update(int x){
	seg[x]=std::max(seg[ls(x)],seg[rs(x)]);
}

void build(int x,int l,int r){
	if(l==r){seg[x]=p[l],pos[l]=x; return;}
	build(lch),build(rch),update(x);
}

void modify(int x,int v){
	x=pos[x],seg[x]=v;
	for(x>>=1;x;x>>=1)update(x);
}

int ql,qr,qa;

void query(int x,int l,int r){
	if(ql<=l&&r<=qr){qa=std::max(qa,seg[x]); return;}
	if(ql<=mid)query(lch); if(qr>mid)query(rch);
}

void check(int id){
	if(id<0||id>(n-1)/K)return;
	ql=id*K+1,qr=ql+K-1,qa=0,query(1,1,n);
	if(!qa||vis[qa])return;
	int tmp=qa;
	ql=q[qa]-K+1,qr=q[qa]+K-1,qa=0,query(1,1,n);
	if(tmp!=qa)return;
	vis[qa]=1,pq.push(q[qa]);
}

int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;++i){
		scanf("%d",p+i);
		q[p[i]]=i;
	}
	build(1,1,n);
	for(int i=0;i<=(n-1)/K;++i)check(i);
	for(int i=n;i;--i){
		int x=pq.top();
		pq.pop(),ans[x]=i,modify(x,0);
		int id=(x-1)/K;
		check(id-1),check(id),check(id+1);
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
