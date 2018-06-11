#include <bits/stdc++.h>

const int max_N = 2000 + 21;

const int mod = 924844033;

int n,k,ans,siz[max_N],fac[max_N];

int f[max_N],g[max_N][max_N][4];

int getG(int i,int j){
	return (g[i][j][0]+g[i][j][2])%mod;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i)++siz[i%k];
	g[1][0][0]=1;
	g[1][1][1]=1;
	for(int i=2;i<=n;++i)
		for(int j=0;j<=i;++j){
			g[i][j][0]=(g[i-1][j][0]+g[i-1][j][2])%mod;
			g[i][j][2]=(g[i-1][j][1]+g[i-1][j][3])%mod;
			if(!j)continue;
			g[i][j][0]=(g[i][j][0]+g[i-1][j-1][0])%mod;
			g[i][j][1]=(g[i-1][j-1][0]+g[i-1][j-1][2])%mod;
			g[i][j][2]=(g[i][j][2]+g[i-1][j-1][1])%mod;
			g[i][j][3]=(g[i-1][j-1][1]+g[i-1][j-1][3])%mod;
		}
	f[0]=1;
	for(int x=0;x<k;++x)
		for(int i=n;i;--i)
			for(int j=1;j<=i&&j<=siz[x];++j){
				f[i] = (f[i] + 1ll*f[i-j]*getG(siz[x],j)) % mod;
			}
	fac[0]=1;
	for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=0;i<=n;++i){
		int tmp=1ll*f[i]*fac[n-i]%mod;
		if(i&1)ans=(ans-tmp+mod)%mod;
		else ans=(ans+tmp)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
