#include <bits/stdc++.h>

const int max_N = (int)1e6 + 21;

const int mod = (int)1e9 + 7;

int n, fac[max_N], _fac[max_N], inv[max_N], f[max_N];

int main(){
	scanf("%d", &n);
	
	if(n==1) return puts("1"), 0;
	
	inv[1] = 1;
	for(int i=2;i<=n;++i){
		inv[i] = 1ll*(mod/i)*inv[mod%i]%mod;
		if(inv[i]) inv[i] = mod-inv[i];
	}
	
	fac[0] = _fac[0] = 1;
	for(int i=1;i<=n;++i){
		fac[i] = 1ll*fac[i-1]*i%mod;
		_fac[i] = 1ll*_fac[i-1]*inv[i]%mod;
	}
	
	auto binom = [](int n, int m){
		if(n < m) return 0;
		return int(1ll*fac[n]*_fac[m]%mod*_fac[n-m]%mod);	
	};
	
	for(int i=1;i<n;++i) f[i] = 1ll*binom(i-1, n-i-1)*fac[i]%mod*fac[n-i-1]%mod;
	
	int ans = 0;
	
	for(int i=1;i<n;++i){
		int g = (f[i]-f[i-1]+mod)%mod;
		ans = (ans+1ll*g*i)%mod;
	}
	
	printf("%d\n", ans);
	
	return 0;
}
