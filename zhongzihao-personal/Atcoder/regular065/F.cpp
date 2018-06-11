#include<bits/stdc++.h>

const int N = 3010;
const int moder = 1e9 + 7;

int dp[N][N], a[N], pre[N], r[N], n, m;
char s[N];

int main(){
	scanf("%d%d%s", &n, &m, s);
	for (int i = 1; i <= n; ++ i){
		r[i] = i;
	}
	for (int i = 0, l, right; i < m; ++ i){
		scanf("%d%d", &l, &right);
		for (int j = l; j <= right; ++ j){
			r[j] = std::max(r[j], right);
		}
	}
	for (int i = 1; i <= n; ++ i){
		a[i] = s[i - 1] - '0';
		pre[i] = pre[i - 1] + (a[i] == 1);
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n + 1; ++ i){
		for (int j = 0; j <= i - 1; ++ j){
			int restone = pre[r[i]] - j;
			if (restone < 0){
				continue;
			}
			if (restone > 0){
				dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % moder;
			}
			if (restone != r[i] - i + 1){
				dp[i][j] = (dp[i][j] + dp[i - 1][j]) % moder;
			}
		}
	}
	printf("%d\n", dp[n][pre[n]]);
	return 0;
}
