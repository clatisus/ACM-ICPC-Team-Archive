#include<bits/stdc++.h>

typedef long long ll;
const int N = 100;

ll dp[N][2];
int n, p;

int main(){
	scanf("%d%d", &n, &p);
	dp[0][0] = 1;
	for (int i = 1, x; i <= n; ++ i){
		scanf("%d", &x);
		dp[i][0] = dp[i - 1][0] + dp[i - 1][x & 1];
		dp[i][1] = dp[i - 1][1] + dp[i - 1][x & 1 ^ 1];
	}
	return printf("%lld\n", dp[n][p]), 0;
}
