#include <bits/stdc++.h>

const int max_N = 1e5 + 21;

int n,pos,tot,ans[max_N],a[max_N],L;

int main(){
	scanf("%d%d",&n,&L);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=1;i<n;++i)
		if(a[i]+a[i+1]>=L){pos=i; break;}
	if(!pos)return puts("Impossible"),0;
	puts("Possible");
	for(int i=1;i<pos;++i)ans[++tot]=i;
	for(int i=n-1;i>=pos;--i)ans[++tot]=i;
	for(int i=1;i<=tot;++i)printf("%d\n",ans[i]);
	return 0;
}
