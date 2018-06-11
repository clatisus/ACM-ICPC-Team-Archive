#include<bits/stdc++.h>

const int N = 100010;

std::vector <int> e[N];
int ans[N], sz[N], sum, min, minsit;
bool vis[N];

void precalc(int u, int fa){
	sz[u] = 1;
	for (auto v : e[u]){
		if (vis[v] || v == fa) continue;
		precalc(v, u);
		sz[u] += sz[v];
	}
}

void dfs1(int u, int fa, int sum){
	int max = 0, ssum = sum;
	for (auto v : e[u]){
		if (vis[v] || v == fa) continue;
		dfs1(v, u, sum);
		ssum -= sz[v];
		max = std::max(max, sz[v]);
	}
	max = std::max(max, ssum - 1);
	if (max < min){
		min = max;
		minsit = u;
	}
}

void dfs2(int u, int fa){
	++ ans[u];
	for (auto v : e[u]){
		if (v == fa || vis[v]) continue;
		dfs2(v, u);
	}
}

void dfs(int u){
	precalc(u, 0);
	if (sz[u] == 1) return;
	min = INT_MAX;
	dfs1(u, 0, sz[u]);
	dfs2(u, 0);
	-- ans[minsit]; 
	vis[minsit] = true;
	for (auto v : e[minsit]){
		if (vis[v]) continue;
		dfs(v);
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0, u, v; i < n - 1; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1);
	int max = 0;
	for (int i = 1; i <= n; ++ i){
		max = std::max(max, ans[i]);
	}
	printf("%d\n", max);
	return 0;
}
