#include <bits/stdc++.h>

const int max_N = 2e5 + 21;

const int max_M = 2e3 + 21;

const int mod = 1e9 + 7;

int n,A[max_N],B[max_N],dp[max_M<<1][max_M<<1],ans;

int fac[max_M<<2],_fac[max_M<<1],inv[max_M<<1];

int main(){
	inv[1]=1;
	for(int i=2;i<=4000;++i){
		inv[i]=1ll*(mod/i)*inv[mod%i]%mod;
		if(inv[i])inv[i]=mod-inv[i];
		assert(1ll*i*inv[i]%mod==1);
	}
	fac[0]=_fac[0]=1;
	for(int i=1;i<=8000;++i){
		fac[i]=1ll*fac[i-1]*i%mod;
	}
	for(int i=1;i<=4000;++i){
		_fac[i]=1ll*_fac[i-1]*inv[i]%mod;
	}
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",A+i,B+i);
		++dp[2000-A[i]][2000-B[i]];
	}
	for(int i=0;i<=4000;++i)
		for(int j=0;j<=4000;++j){
			dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
			dp[i][j+1]=(dp[i][j+1]+dp[i][j])%mod;
		}
	for(int i=1;i<=n;++i){
		ans=(ans+dp[2000+A[i]][2000+B[i]])%mod;
		int tmp=1ll*fac[A[i]*2+B[i]*2]*_fac[A[i]*2]%mod*_fac[B[i]*2]%mod;
		ans=(ans-tmp+mod)%mod;
	}
	ans=1ll*ans*inv[2]%mod;
	printf("%d\n",ans);
	return 0;
}

