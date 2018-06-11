#include<bits/stdc++.h>

const int N = 300010;
const int M = 30;

int dp[N];
bool vis[N];
char a[N];
int top[N];
int cnt = 0;
std::vector <int> e[N];

void dfs(int u, char ch){
	if (vis[u]) return;
	vis[u] = true;
	dp[u] = 0;
	for (auto v : e[u]){
		dfs(v, ch);
		dp[u] = std::max(dp[u], dp[v]);
	}
	dp[u] += a[u] == ch;
	top[u] = ++ cnt;
}

int main(){
	int n, m;
	scanf("%d%d%s", &n, &m, a + 1);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
	}
	int ans = 0;
	for (char ch = 'a'; ch <= 'z'; ++ ch){
		cnt = 0;
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; ++ i){
			dfs(i, ch);
		}
		for (int i = 1; i <= n; ++ i){
			ans = std::max(ans, dp[i]);
		}
	}
	for (int i = 1; i <= n; ++ i){
		for (auto u : e[i]){
			if (top[i] <= top[u]){
				puts("-1");
				return 0;
			}
		}
	}
	return printf("%d\n", ans), 0;
}
