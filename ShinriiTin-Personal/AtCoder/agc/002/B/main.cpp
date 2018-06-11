#include <bits/stdc++.h>

const int max_N = 1e5 + 21;

int n,m,ans,siz[max_N];

bool f[max_N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)siz[i]=1;
	f[1]=1;
	while(m--){
		int x,y; scanf("%d%d",&x,&y);
		++siz[y],f[y]|=f[x];
		if(!--siz[x])f[x]=0;
	}
	for(int i=1;i<=n;++i)if(f[i])++ans;
	printf("%d\n",ans);
	return 0;
}
