#include<bits/stdc++.h>

const int N = 100010;

int n;
int a[N], dp[N][2];

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	dp[0][0] = dp[0][1] = 1;
	for (int i = 1; i < n; ++ i){
		dp[i][0] = dp[i][1] = 1 + std::min(dp[i - 1][0], dp[i - 1][1]);
		if (a[i] >= a[i - 1]){
			dp[i][0] = std::min(dp[i][0], dp[i - 1][0]);
		}
		if (a[i] <= a[i - 1]){
			dp[i][1] = std::min(dp[i][1], dp[i - 1][1]);
		}
	}
	return printf("%d\n", std::min(dp[n - 1][0], dp[n - 1][1])), 0;
}
