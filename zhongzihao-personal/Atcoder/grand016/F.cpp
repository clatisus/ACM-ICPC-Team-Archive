#include<bits/stdc++.h>

inline int lowbit(int n){return n & (-n);}

const int moder = 1e9 + 7;
const int N = 300;

int n, m;
int power[N], fac[N], inv[N], mat[N][N], digit[N], dp[1 << 16];

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
	if (n < m || m < 0){
		return 0;
	}
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
	power[0] = 1;
	for (int i = 1; i < N; ++ i){
		power[i] = 2 * power[i - 1] % moder;
	}
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		-- u, -- v;
		mat[u][v] = 1;
	}
	dp[0] = 1; 
	for (int i = 0; i < 1 << n; ++ i){
		if ((i >> 0 & 1) != (i >> 1 & 1)){
		//	continue;
		}
		int cnt = 0, x = i, y;
		for ( ; x; x -= lowbit(x)){
			digit[cnt ++] = lowbit(x);
		}
		for (int j = 0; j < 1 << cnt; ++ j){
			x = 0;
			for (int k = 0; k < cnt; ++ k){
				if (j >> k & 1){
					x ^= digit[k];
				}
			}
			y = i ^ x;
			if ((x >> 0 & 1) != (x >> 1 & 1) || !x){
				continue;
			}
			int ans = 1, cccnt = 0;
			for (int k = 0; k < n; ++ k){
				if (y >> k & 1){
					int ccnt = 0;
					for (int kk = 0; kk < n; ++ kk){
						if (x >> kk & 1){
							if (mat[k][kk]){
								++ ccnt;
							}
							if (mat[kk][k]){
								++ cccnt;
							}
						}
					}
					ans = 1ll * ans * (power[ccnt] - 1 + moder) % moder;
				}
			}
			dp[i] = (dp[i] + 1ll * ans * power[cccnt] % moder * dp[y]) % moder;
		}
	}
	return printf("%d\n", (power[m] - dp[(1 << n) - 1] + moder) % moder), 0;
}
