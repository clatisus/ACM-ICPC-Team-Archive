#include<bits/stdc++.h>

const int N = 100010;

std::set <int> set[N];
std::queue <std::pair <int, int>> q;
int n;
int fa[N], sz[N];

int find(int u){
	return fa[u] == u ? u : fa[u] = find(fa[u]);
}

void unite(int u, int v){
	int _u = find(u), _v = find(v);
	if (_u == _v){
		return;
	}
	fa[_u] = fa[_v];
	sz[_v] += sz[_u];
	find(u);
}

int main(){
	for (int i = 0; i < N; ++ i){
		fa[i] = i;
		sz[i] = 1;
	}
	scanf("%d", &n);
	for (int i = 0, u, v; i < n - 1 << 1; ++ i){
		scanf("%d%d", &u, &v);
		if (set[u].count(v)){
			q.push({u, v});
		}
		else{
			set[u].insert(v);
			set[v].insert(u);
		}
	}
	while (!q.empty()){
		std::pair <int, int> p = q.front();
		q.pop();
		int u = find(p.first), v = find(p.second);
		if (sz[u] > sz[v]){
			std::swap(u, v);
		}
		unite(u, v);
		set[u].erase(v);
		set[v].erase(u);
		for (auto w : set[u]){
			set[w].erase(u);
			if (set[w].count(v)){
				q.push({w, v});
			}
			else{
				set[w].insert(v);
				set[v].insert(w);
			}
		}
		set[u].clear();
	}
	return printf(sz[find(1)] == n ? "YES\n" : "NO\n"), 0;
}
