#include <bits/stdc++.h>

int main(){
	int n, m; scanf("%d%d", &n, &m);

	int f[n+1], *c[n+1], *s[n+1];
	
	for(int i=0;i<=n;++i){
		s[i] = new int[n+1](), c[i] = new int[n+1]();
		memset(s[i], 0, sizeof(int)*(n+1)), memset(c[i], 0, sizeof(int)*(n+1));
		s[i][0] = c[i][0] = 1;
		for(int j=1;j<=i;++j){
			s[i][j] = (s[i-1][j-1] + 1ll*(j+1)*s[i-1][j])%m;
			c[i][j] = (c[i-1][j-1] + c[i-1][j])%m;
		}
	}
	
	auto qpow = [](int x, int k, int m){
		int res = 1;
		while(k){
			if(k&1) res = 1ll*res*x%m;
			x = 1ll*x*x%m;
			k >>= 1;
		}
		return res;
	};
	
	int ans = 0;
	
	for(int i=0;i<=n;++i){
		f[i] = 0;
		int pw22 = qpow(2, qpow(2, n-i, m-1), m);
		int pw2 = qpow(2, n-i, m), pw2j = 1;
		for(int j=0;j<=i;++j){
			f[i] = (f[i] + 1ll*s[i][j]*pw2j%m*pw22)%m;
			pw2j = 1ll* pw2j*pw2%m;
		}
		int tmp = 1ll*c[n][i]*f[i]%m;
		if(i&1) tmp = m - tmp;
		ans = (ans + tmp)%m;
	}
	
	printf("%d\n", ans);
	
	return 0;
}
