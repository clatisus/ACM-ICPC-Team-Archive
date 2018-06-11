#include<bits/stdc++.h>

const int N = 10010;
const int M = 1010;

bool dp[N][M];
int pre[N][M], a[N];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	dp[0][1] = true;
	for (int i = 1; i <= n; ++ i){
		for (int j = 0; j < m; ++ j){
			if (!dp[i - 1][j]) continue;
			dp[i][j] = true;
			pre[i][j] = j;
			int x = j * a[i] % m;
			dp[i][x] = true;
			pre[i][x] = j;
		}
	}
	for (int i = m - 1; i >= 0; -- i){
		if (dp[n][i]){
			printf("%d\n", i);
			std::vector <int> ans;
			int now = i;
			for (int j = n; j; -- j){
				if (pre[j][now] != now){
					now = pre[j][now];
					ans.push_back(j);
				}
			}
			std::reverse(ans.begin(), ans.end());
			for (int i = 0, sz = ans.size(); i < sz; ++ i){
				printf("%d%c", ans[i], " \n"[i == sz - 1]);
			}
			return 0;
		}
	}
}
