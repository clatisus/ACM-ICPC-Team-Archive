#include<bits/stdc++.h>

const int N = 200010;
typedef std::pair <int, int> pii;
typedef std::pair <pii, pii> piiii;
typedef long long ll;

int n, m;
ll ans[N];
int fa[N];
piiii p[N];
std::vector <int> e[N];

int find(int u){
	return fa[u] == u ? u : (fa[u] = find(fa[u]));
}

ll sum = 0;

void unite(int u, int v, int w){
	int _u = find(u), _v = find(v);
	if (_u == _v) return;
	e[u].push_back({v, w});
	e[v].push_back({u, w});
	sum += w;
	fa[_u] = _v;
}

const int M = 18;

int ance[N][M], ancem[N][M], dep[N];

void dfs(int u, int fa){
	for (auto v : e[u]){
		if (v.first == fa){
			continue;
		}
		ance[v.first][0] = u;
		ancem[v.first][0] = v.second;
		dep[v.first] = dep[u] + 1;
		for (int i = 1; i < M; ++ i){
			ance[v.first][i] = ance[ance[v.first][i - 1]][i - 1];
			ancem[v.first][i] = std::max(ancem[v.first][i - 1], ancem[ance[v.first][i - 1]][i - 1]);
		}
		dfs(v.first, u);
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v, w; i < m; ++ i){
		scanf("%d%d%d%d", &u, &v, &w);
		p[i] = {{w, i}, {u, v}};
	}
	std::sort(p, p + m);
	for (int i = 1; i <= n; ++ i){
		fa[i] = i;
	}
	for (int i = 0; i < m; ++ i){
		unite(p[i].second.first, p[i].second.second, p[i].first.first);
	}
	dep[1] = 1;
	dfs(1, 0);
	for (int i = 0; i < m; ++ i){
		int u = p[i].second.first, v = p[i].second.second, max = 0;
		if (dep[u] > dep[v]){
			std::swap(u, v);
		}
		while (dep[] < ){
		}
	}
	return 0;
}
