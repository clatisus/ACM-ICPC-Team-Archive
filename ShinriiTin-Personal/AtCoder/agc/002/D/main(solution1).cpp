#include <bits/stdc++.h>

//#define debug

const int max_N = 1e5 + 21;

int n,m,q,cur,u[max_N],v[max_N];

int x[max_N],y[max_N],z[max_N],ans[max_N];

int f[max_N],siz[max_N];

void dfu_init(){
	for(int i=1;i<=n;++i)f[i]=i,siz[i]=1;
}

int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}

void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(siz[x]>siz[y])std::swap(x,y);
	siz[y]+=siz[x],f[x]=y;
}

using star = struct node*;

struct node{
	int l,r;
	std::vector<int>vec;
}pool[max_N*20];

star tail=pool;

std::queue<star>Q;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)scanf("%d%d",u+i,v+i);
	scanf("%d",&q);
	star rt=tail++;
	rt->l=1,rt->r=m,Q.push(rt);
	for(int i=1;i<=q;++i){
		scanf("%d%d%d",x+i,y+i,z+i);
		rt->vec.push_back(i);
	}
	dfu_init();
	while(!Q.empty()){
		star it=Q.front(); Q.pop();
		if(it->vec.empty())continue;
		if(it->l==it->r){
			for(auto&i:it->vec)ans[i]=it->l;
			continue;
		}
		int mid=(it->l+it->r)>>1;
		if(cur>mid)dfu_init(),cur=0;
		while(cur<mid)++cur,merge(u[cur],v[cur]);
		star lch=tail++,rch=tail++;
		lch->l=it->l,lch->r=mid,rch->l=mid+1,rch->r=it->r;
		for(auto&i:it->vec){
			int fx=find(x[i]),fy=find(y[i]);
			int sz=(fx==fy)?siz[fx]:siz[fx]+siz[fy];
			if(sz>=z[i])lch->vec.push_back(i);
			else rch->vec.push_back(i);
		}
		Q.push(lch),Q.push(rch);
	}
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
