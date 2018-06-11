#include<bits/stdc++.h>

const int N = 10;

std::queue <std::pair <int, int>> q;
int dp[1 << N][N], n, m, mat[N][N], vis[1 << N][N];

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		mat[u][v] = mat[v][u] = 1;
	}
	dp[1][1] = 1;
	q.push({1, 1});
	while (!q.empty()){
		int u = q.front().first, v = q.front().second;
		q.pop();
		vis[u][v] = false;
		for (int i = 1; i <= n; ++ i){
			if (!mat[v][i] || (u & 1 << (i - 1))){
				continue;
			}
			std::pair <int, int> p = {u | 1 << (i - 1), i};
			if (!vis[p.first][p.second]){
				q.push(p);
			}
			dp[p.first][p.second] += dp[u][v];
			vis[p.first][p.second] = true;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i){
		ans += dp[(1 << n) - 1][i];
	}
	return printf("%d\n", ans), 0;
}
