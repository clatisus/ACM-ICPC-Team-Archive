#include<bits/stdc++.h>

const int N = 100010;

std::vector <int> e[N];
int sg[N], cnt[N];
int n;

void dfs(int u, int fa){
	for (auto v : e[u]){
		if (v == fa){
			continue;
		}
		dfs(v, u);
		sg[u] ^= 1 + sg[v];
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 0, u, v; i < n - 1; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	return printf(sg[1] ? "Alice\n" : "Bob\n"), 0;
}
