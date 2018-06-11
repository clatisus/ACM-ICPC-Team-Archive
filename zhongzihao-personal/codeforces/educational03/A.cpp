#include<bits/stdc++.h>

const int N = 110;
const int M = 100010;
const int INF = 0x7f7f7f7f;

int dp[M];

int main(){
	memset(dp, 0x7f, sizeof(dp));
	dp[0] = 0;
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		for (int j = M - 1; j >= 0; -- j){
			if (dp[j] != INF){
				dp[j + x] = std::min(dp[j + x], dp[j] + 1);
			}
		}
	}
	int min = INT_MAX;
	for (int j = m; j < M; ++ j){
		min = std::min(min, dp[j]);
	}
	return printf("%d\n", min), 0;
}
