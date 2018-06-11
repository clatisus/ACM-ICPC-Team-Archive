#include<bits/stdc++.h>

const int N = 1010;
const int moder = 1e9 + 7;

int fac[N], inv[N], dp[N][N], n, a, b, c, d;

int power_mod(int a, int index){
	int ret = 1;
	while (index){
		if (index & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
		index >>= 1;
	}
	return ret;
}

int main(){
	fac[0] = inv[0] = 1;
	for (int i = 1; i < N; ++ i){
		fac[i] = 1ll * fac[i - 1] * i % moder;
		inv[i] = power_mod(fac[i], moder - 2);
	}
	scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
	dp[a][0] = 1;
	for (int i = a; i <= b; ++ i){
		for (int j = 0; j <= n; ++ j){
			dp[i + 1][j] = dp[i][j];
		}
		for (int j = c; j <= d; ++ j){
			for (int k = 0; k <= n; ++ k){
				int x = i * j + k;
				if (x > n){
					break;
				}
				dp[i + 1][x] = (dp[i + 1][x] + 1ll * fac[x] * inv[k] % moder * power_mod(inv[i], j) % moder * inv[j] % moder * dp[i][k]) % moder;
			}
		}
	}
	printf("%d\n", dp[b + 1][n]);
	return 0;
}
