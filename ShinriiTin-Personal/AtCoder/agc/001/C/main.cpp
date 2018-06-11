#include <bits/stdc++.h>

const int max_N = 2000 + 21;

int n,k,t,dis[max_N],q[max_N],ans=-1;

std::vector<int>vec[max_N];

int bfs(){
	int tmp=0;
	for(int i=1;i<=t;++i){
		int u=q[i];
		for(auto&v:vec[u])
			if(dis[v]==-1){
				dis[v]=dis[u]+1;
				q[++t]=v;
			}
		if(dis[u]>k/2)++tmp;
	}
	return tmp;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1,a,b;i<n;++i){
		scanf("%d%d",&a,&b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	if(k&1){
		for(int x=1;x<=n;++x)
			for(auto&y:vec[x])if(x<y){
				memset(dis+1,-1,sizeof(int)*n);
				t=2,q[1]=x,q[2]=y,dis[x]=dis[y]=0;
				int tmp=bfs();
				if(ans==-1||ans>tmp)ans=tmp;
			}
	}
	else{
		for(int x=1;x<=n;++x){
			memset(dis+1,-1,sizeof(int)*n);
			t=1,q[1]=x,dis[x]=0;
			int tmp=bfs();
			if(ans==-1||ans>tmp)ans=tmp;
		}
	}
	printf("%d\n",ans);
	return 0;
}

