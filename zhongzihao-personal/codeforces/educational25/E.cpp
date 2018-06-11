#include<bits/stdc++.h>

const int N = 100010;

int n, m;
int deg[N], ans[N];
std::vector <int> e[N], _e[N];
bool vis[N];
std::vector <int> now;

void dfs(int u){
	now.push_back(u);
	vis[u] = true;
	for (auto v : _e[u]){
		if (!vis[v]){
			dfs(v);
		}
	}
}

void addedge(int u, int v){
	e[v].push_back(u);
	_e[u].push_back(v);
	_e[v].push_back(u);
}

void solve(int s, int &num){
	::now.clear();
	dfs(s);
	std::vector <int> zero;
	for (auto u : ::now){
		if (!deg[u]){
			zero.push_back(u);
		}
	}
	int now = num + ::now.size();
	while ((int) zero.size()){
		std::sort(zero.begin(), zero.end(), std::greater <int>());
		std::vector <int> _zero;
		for (auto u : zero){
			ans[u] = now --;
			for (auto v : e[u]){
				-- deg[v];
				if (!deg[v]){
					_zero.push_back(v);
				}
			}
		}
		zero = _zero;
	}
	num += ::now.size();
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		++ deg[u];
		addedge(u, v);
	}
	int num = 0;
	for (int i = 1; i <= n; ++ i){
		if (!vis[i]){
			solve(i, num);
		}
	}
	for (int i = 1; i <= n; ++ i){
		printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
