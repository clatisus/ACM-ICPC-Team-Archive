#include<bits/stdc++.h>

const int N = 100010;

std::vector <int> e[N];
bool vis[N];
std::vector <int> ans[2];

int dfs(int u, int type){
	ans[type].push_back(u);
	vis[u] = true;
	for (auto v : e[u]){
		if (!vis[v]){
			dfs(v, type);
			break;
		}
	}
}

int n, m;

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	dfs(1, 1);
	printf("%d\n", (int) ans[0].size() + (int) ans[1].size() - 1);
	for (int i = (int) ans[1].size() - 1; i; -- i){
		printf("%d ", ans[1][i]);
	}
	for (auto u : ans[0]){
		printf("%d ", u);
	}
	return printf("\n"), 0;
}
