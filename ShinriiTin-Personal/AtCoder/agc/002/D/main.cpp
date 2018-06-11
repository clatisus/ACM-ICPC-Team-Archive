#include <bits/stdc++.h>

//#define debug

const int max_N = 1e5 + 21;

#ifdef debug
const int K = 4;
#else
const int K = 400;
#endif

int n,m,q,u[max_N],v[max_N];

int x[max_N],y[max_N],z[max_N],ans[max_N];

struct dfu{
	int f[max_N],siz[max_N];
	int find(int x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return;
		if(siz[x]>siz[y])std::swap(x,y);
		siz[y]+=siz[x],f[x]=y;
	}
}F[2];

std::vector<int>Q[2],Q2;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)scanf("%d%d",u+i,v+i);
	for(int i=1;i<=n;++i){
		F[0].f[i]=i,F[0].siz[i]=1;
		F[1].f[i]=i,F[1].siz[i]=1;
	}
	scanf("%d",&q);
	for(int i=1;i<=q;++i){
		scanf("%d%d%d",x+i,y+i,z+i);
		Q[0].push_back(i);
	}
	int cur=0,B=(m-1)/K;
	for(int i=0;i<=B;++i){
		for(int j=i*K+1;j<=m&&j<=(i+1)*K;++j)
			F[0].merge(u[j],v[j]);
		Q[cur^1].clear(),Q2.clear();
		for(auto&j:Q[cur]){
			int fx=F[0].find(x[j]),fy=F[0].find(y[j]);
			int siz=(fx==fy)?F[0].siz[fx]:F[0].siz[fx]+F[0].siz[fy];
			if(siz>=z[j])Q2.push_back(j);
			else Q[cur^1].push_back(j);
		}
		for(int j=i*K+1;j<=m&&j<=(i+1)*K;++j){
			F[1].merge(u[j],v[j]);
			for(auto&k:Q2){
				if(ans[k])continue;
				int fx=F[1].find(x[k]),fy=F[1].find(y[k]);
				int siz=(fx==fy)?F[1].siz[fx]:F[1].siz[fx]+F[1].siz[fy];
				if(siz>=z[k])ans[k]=j;
			}
		}
		cur^=1;
	}
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}

