#include<bits/stdc++.h>

const int N = 410;

int n, ma, mb, a[N], b[N], c[N], dp[50][N][N];

int main(){
	scanf("%d%d%d", &n, &ma, &mb);
	for (int i = 1; i <= n; ++ i){
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
	}
	memset(dp, -1, sizeof(dp));
	dp[0][0][0] = 0;
	for (int i = 1; i <= n; ++ i){
		for (int j = 0; j < N; ++ j){
			for (int k = 0; k < N; ++ k){
				dp[i][j][k] = dp[i - 1][j][k];
			}
		}
		for (int j = 0; j < N; ++ j){
			for (int k = 0; k < N; ++ k){
				if (dp[i - 1][j][k] == -1 || j + a[i] >= N || k + b[i] >= N){
					continue;
				}
				int x = dp[i - 1][j][k] + c[i], &u = dp[i][j + a[i]][k + b[i]];
				if (u == -1 || u > x){
					u = x;
				}
			}
		}
	}
	int ans = INT_MAX;
	for (int i = ma, j = mb; i < N && j < N; i += ma, j += mb){
		if (dp[n][i][j] >= 0){
			ans = std::min(ans, dp[n][i][j]);
		}
	}
	if (ans == INT_MAX){
		ans = -1;
	}
	return printf("%d\n", ans), 0;
}
