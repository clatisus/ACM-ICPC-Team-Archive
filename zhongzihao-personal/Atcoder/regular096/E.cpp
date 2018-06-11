#include<bits/stdc++.h>

const int N = 3010;
int moder;

int powermod(int a, int exp, int moder){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

int s[N][N];
int comb[N][N];

int main(){
	int n;
	scanf("%d%d", &n, &moder);
	for (int i = 0; i < N; ++ i){
		comb[i][0] = 1;
		for (int j = 1; j <= i; ++ j){
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % moder;
		}
	}
	for (int i = 0; i < N; ++ i){
		s[i][0] = 1;
		for (int j = 1; j <= i; ++ j){
			s[i][j] = (1ll * s[i - 1][j] * (j + 1) + s[i - 1][j - 1]) % moder;
		}
	}
	int ans = powermod(2, powermod(2, n, moder - 1), moder);
	for (int i = 1; i <= n; ++ i){
		int sum = 0;
		for (int j = 0; j <= i; ++ j){
			sum = (sum + 1ll * s[i][j] * powermod(2, (n - i) * j, moder) % moder) % moder;
		}
		sum = 1ll * sum * powermod(2, powermod(2, n - i, moder - 1), moder) % moder;
		ans = (ans + (i & 1 ? -1ll : 1ll) * comb[n][i] * sum) % moder;
		ans += ans < 0 ? moder : 0;
	}
	printf("%d\n", ans);
	return 0;
}
