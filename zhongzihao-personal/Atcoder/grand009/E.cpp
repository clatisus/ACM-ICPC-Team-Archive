#include<bits/stdc++.h>
#define ll long long

const int N = 4010;
const int moder = 1e9 + 7;

ll dp[2][N][2], n, m, kk;

int main(){
	scanf("%d%d%d", &n, &m, &kk);
	dp[0][0][0] = 1;
	int pre = 0, now = 1;
	ll ans = 0;
	for (int i = 1; i <= (n + m - 1) / (kk - 1); ++ i){
		for (int k = 0; k <= n; ++ k){
			if (k < i * (kk - 1) - m + 1){
				continue;
			}
			dp[now][k][0] = (dp[now][k][0] + dp[pre][k][0] + dp[pre][k][1]) % moder;
		}
		for (int j = 1; j < kk; ++ j){
			for (int k = 0; k <= n; ++ k){
				int x = j + k;
				if (x < i * (kk - 1) - m + 1 || x > n){
					continue;
				}
				dp[now][x][1] = (dp[now][x][1] + dp[pre][k][0] + dp[pre][k][1]) % moder;
			}
		}
		for (int j = 0; j <= n; ++ j){
			if (j % (kk - 1) == n % (kk - 1)){
				ans = (ans + dp[now][j][1]) % moder;
			}
		}
		pre ^= 1;
		now ^= 1;
		memset(dp + now, 0, sizeof(int) * N * 2);
	}
	return printf("%d\n", ans), 0;
}
