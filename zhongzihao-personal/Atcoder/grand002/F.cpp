#include<bits/stdc++.h>

const int M = 2010;
const int N = M * M;
const int moder = 1e9 + 7;

int powermod(int a, int exp){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

int fac[N], inv[N];
int dp[M][M];

int comb(int n, int m){
	if (n < m || m < 0) return 0;
	return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

int main(){
	fac[0] = 1;
	for (int i = 1; i < N; ++ i){
		fac[i] = 1ll * fac[i - 1] * i % moder;
	}
	inv[N - 1] = powermod(fac[N - 1], moder - 2);
	for (int i = N - 1; i; -- i){
		inv[i - 1] = 1ll * inv[i] * i % moder;
	}
	int n, k;
	scanf("%d%d", &n, &k);
	if (k == 1){
		puts("1");
		return 0;
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++ i){
		dp[i][0] = 1ll * dp[i - 1][0] * comb(i * (k - 1) - 1, k - 2) % moder;
		for (int j = 1; j <= i; ++ j){
			if (j < i){
				dp[i][j] = 1ll * dp[i - 1][j] * comb(j + i * (k - 1) - 1, k - 2) % moder;
			}
			dp[i][j] += dp[i][j - 1];
			dp[i][j] -= dp[i][j] >= moder ? moder : 0;
		}
	}
	printf("%lld\n", 1ll * fac[n] * dp[n][n] % moder);
	return 0;
}
