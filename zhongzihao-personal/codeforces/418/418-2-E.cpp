#include<bits/stdc++.h>

const int N = 60;
const int moder = 1e9 + 7;

int d[N], dp[N][N][N * 3];
int n;
int fac[N], inv[N * N], pre[N * N];

int powermod(int a, int exp){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

int comb(int n, int m){
	if (n < 0 || n < m || m < 0){
		return 0;
	}
	return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

int main(){
	fac[0] = 1;
	for (int i = 1; i < N * N; ++ i){
		fac[i] = 1ll * fac[i - 1] * i % moder;
	}
	inv[N * N - 1] = powermod(fac[N * N - 1], moder - 2);
	for (int i = N * N - 1; i; -- i){
		inv[i - 1] = 1ll * inv[i] * i % moder;
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &d[i]);
		pre[i] = pre[i - 1] + d[i];
	}
	dp[1][1][0] = 1;
	for (int i = 1; i <= n; ++ i){
		for (int j = 0; j <= i; ++ j){
			for (int k = 0; k <= i * 3; ++ k){
				if (!dp[i][j][k]){
					continue;
				}
				for (int ii = 0; ii <= k && ii <= j * (j - 1); ii += 2){
					int x = i + pre[i] - pre[i - j - 1] + k - (ii >> 1);
					if (i + x <= n){
						int &u = dp[x][x - i][k - (ii >> 1)];
						u = (u + 1ll * comb(j * (j - 1) >> 1, ii) * dp[i][j][k]) % moder;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++ i){
		for (int j = 0; j < N; ++ j){
			ans = (ans + dp[n][i][j]) % moder;
		}
	}
	return printf("%d\n", ans), 0;
}
