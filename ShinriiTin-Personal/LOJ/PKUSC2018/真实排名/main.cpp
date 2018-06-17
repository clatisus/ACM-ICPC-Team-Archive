#include <bits/stdc++.h>

const int max_N = (int)1e5 + 21;
const int mod = 998244353;

int n, m, k, a[max_N], a2[max_N], s[max_N << 1], s2[max_N << 1], h[max_N << 1];

int fac[max_N], _fac[max_N], inv[max_N];

inline void init(){
	inv[1] = 1;
	for(int i=2;i<max_N;++i){
		inv[i] = 1ll*(mod/i)*inv[mod%i]%mod;
		if(inv[i]) inv[i] = mod - inv[i];
	}
	fac[0] = _fac[0] = 1;
	for(int i=1;i<max_N;++i){
		fac[i] = 1ll*fac[i-1] * i % mod;
		_fac[i] = 1ll*_fac[i-1] * inv[i] % mod;	
	}
}

int main(){
	init();
	scanf("%d %d", &n, &k);
	for(int i=1;i<=n;++i){
		scanf("%d", a+i);
		h[++ m] = a[i];
		h[++ m] = a[i] << 1;
	}
	std::sort(h+1, h+1+m);
	m = std::unique(h+1, h+1+m) - (h+1);
	auto rk = [&](int x){
		return m - (std::lower_bound(h+1, h+1+m, x) - h) + 1;	
	};
	for(int i=1;i<=n;++i){
		a2[i] = rk(a[i] << 1); ++ s2[a2[i]];
		a[i] = rk(a[i]); ++ s[a[i]];
	}
	for(int i=1;i<=m;++i) s[i] += s[i-1], s2[i] += s2[i-1];
	auto binom = [&](int n, int m) -> int{
		if(n < m) return 0;
		return 1ll*fac[n] * _fac[m] % mod * _fac[n-m] % mod;
	};
	for(int i=1;i<=n;++i){
		if(a[i] == m && h[1] == 0){
			printf("%d\n", binom(n, k));
			continue;
		}
		int ans1 = binom(n - (s2[a[i]]-s[a[i]]) - 1, k);
		int delta = s[a[i]] - s[a2[i]] - 1;
		int ans2 = 0;
		if(delta < k){
			ans2 = 1ll*binom(s2[a2[i]]-s[a2[i]]-1, delta) * binom(n - (s2[a2[i]]-s[a2[i]]), k-1-delta) % mod;	
		}
		printf("%d\n", (ans1+ans2)%mod);
	}
	return 0;
}
