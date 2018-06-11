#include<bits/stdc++.h>

const int N = 200010;
const int M = 2010;
const int moder = 1e9 + 7;
const int inv2 = 5e8 + 4;

int fac[M << 2], inv[M << 2];
int a[N], b[N];
int dp[M << 1][M << 1];

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

int comb(int n, int m){
	if (n < m || m < 0) return 0;
	return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

int main(){
	fac[0] = 1;
	for (int i = 1; i < M << 2; ++ i){
		fac[i] = 1ll * fac[i - 1] * i % moder;
	}
	inv[(M << 2) - 1] = powermod(fac[(M << 2) - 1], moder - 2);
	for (int i = (M << 2) - 1; i; -- i){
		inv[i - 1] = 1ll * inv[i] * i % moder;
	}
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d%d", &a[i], &b[i]);
		++ dp[M - a[i]][M - b[i]];
	}
	for (int i = 1; i < M << 1; ++ i){
		dp[0][i] = (dp[0][i - 1] + dp[0][i]) % moder;
	}
	for (int i = 1; i < M << 1; ++ i){
		dp[i][0] = (dp[i - 1][0] + dp[i][0]) % moder;
		for (int j = 1; j < M << 1; ++ j){
			dp[i][j] = (dp[i][j] + dp[i - 1][j] + dp[i][j - 1]) % moder;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		ans = (ans + dp[a[i] + M][b[i] + M]) % moder;
		ans = (ans - comb(a[i] + b[i] << 1, a[i] << 1) + moder) % moder;
	}
	ans = 1ll * ans * inv2 % moder;
	printf("%d\n", ans);
	return 0;
}
