#include <bits/stdc++.h>

const int max_N = 2e3 + 21;

const int mod = 1e9 + 7;

int n,k,f[max_N][max_N];

int fac[max_N*max_N],_fac[max_N*max_N],inv[max_N*max_N];

inline void init(int n){
	inv[1]=1;
	for(int i=2;i<=n;++i){
		inv[i]=1ll*(mod/i)*inv[mod%i]%mod;
		if(inv[i])inv[i]=mod-inv[i];
	}
	fac[0]=_fac[0]=1;
	for(int i=1;i<=n;++i){
		fac[i]=1ll*fac[i-1]*i%mod;
		_fac[i]=1ll*_fac[i-1]*inv[i]%mod;
	}
}

inline int C(int n,int m){
	return 1ll*fac[n]*_fac[m]%mod*_fac[n-m]%mod;
}

int calc(int i,int j){
	if(~f[i][j])return f[i][j];
	int&res=f[i][j];
	res=0;
	if(i)res=calc(i-1,j);
	if(j>i)
		res=(res+1ll*C(i+j*(k-1)-1,k-2)*calc(i,j-1))%mod;
	return res;
}

int main(){
	scanf("%d%d",&n,&k);
	if(k==1)return puts("1"),0;
	init(n*k);
	for(int i=0;i<=n;++i)
		for(int j=0;j<=n;++j)
			f[i][j]=-1;
	f[0][0]=1;
	int ans=1ll*calc(n,n)*fac[n]%mod;
	printf("%d\n",ans);
	return 0;
}
