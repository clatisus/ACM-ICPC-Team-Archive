#include<bits/stdc++.h>

const int N = 5010;

int dp[N][N], a[N], pre[N][N];
int n, k;

int main(){
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	dp[0][0] = 1;
	for (int i = 1; i <= k; ++ i){
		pre[0][i] = 1;
	}
	for (int i = 1; i <= n; ++ i){
		for (int j = 0; j < k; ++ j){
			dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
			if (!dp[i - 1][j] || j + a[i] >= k){
				continue;
			}
			dp[i][j + a[i]] = 1;
		}
		for (int j = 0; j < k; ++ j){
			pre[i][j + 1] = pre[i][j] + dp[i][j];
		}
	}
	memset(dp, 0, sizeof(dp));
	dp[n + 1][0] = 1;
	for (int i = n; i >= 1; -- i){
		for (int j = 0; j < k; ++ j){
			dp[i][j] = std::max(dp[i][j], dp[i + 1][j]);
			if (!dp[i + 1][j] || j + a[i] >= k){
				continue;
			}
			dp[i][j + a[i]] = 1;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i){
		if (a[i] >= k){
			++ ans;
			continue;
		}
		for (int j = 0; j < k; ++ j){
			if (!dp[i + 1][j]){
				continue;
			}
			int left = std::max(0, k - a[i] - j), right = k - j;
			if (pre[i - 1][right] - pre[i - 1][left]){
				++ ans;
				break;
			}
		}
	}
	return printf("%d\n", n - ans), 0;
}
