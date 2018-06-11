#include<bits/stdc++.h>

const int N = 100010;

std::vector <int> e[N];
int n;
int dep[N], sz[N], fa[N];

void addedge(int u, int v){
	e[u].push_back(v);
	e[v].push_back(u);
}

void dfs(int u, int fa){
	sz[u] = 1;
	for (auto v : e[u]){
		if (v == fa){
			continue;
		}
		::fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 0, u, v; i < n - 1; ++ i){
		scanf("%d%d", &u, &v);
		addedge(u, v);
	}
	dfs(1, 0);
	int v = n;
	for (int i = 0, sz = dep[n] - 1 >> 1; i < sz; ++ i){
		v = fa[v];
	}
	return printf(n - sz[v] > sz[v] ? "Fennec\n" : "Snuke\n"), 0;
}
