#include<bits/stdc++.h>

const int N = 100010;

typedef std::pair <int, bool> pib;
std::vector <pib> e[N];

int col[N], fa[N], cnt[10][N];

void dfs(int u){
	for (auto v : e[u]){
		int pre = col[v.first];
		if (col[u] == 4){
			col[v.first] = 4;
		}
		else{
			int x = v.second ? col[u] - 1 : (col[u] + 1) % 3;
			x += !x ? 3 : 0;
			if (col[v.first]){
				col[v.first] = col[v.first] == x ? x : 4;
			}
			else{
				col[v.first] = x;
			}
		}
		if (!pre) dfs(v.first);
	}
}

int find(int u){
	if (fa[u] == u) return u;
	fa[u] = find(fa[u]);
	for (int i = 0; i <= 4; ++ i){
		cnt[i][u] = cnt[i][fa[u]];
	}
	return fa[u];
}

void unite(int u, int v){
	int _u = find(u), _v = find(v);
	if (_u == _v) return;
	for (int i = 0; i <= 4; ++ i){
		cnt[i][_v] += cnt[i][_u];
	}
	fa[_u] = _v;
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back({v, false});
		e[v].push_back({u, true});
	}
	for (int i = 1; i <= n; ++ i){
		if (!col[i]){
			col[i] = 1;
			dfs(i);
		}
	}
	for (int i = 1; i <= n; ++ i){
		fa[i] = i;
		cnt[col[i]][i] = 1;
		cnt[0][i] = e[i].size();
	}
	for (int i = 1; i <= n; ++ i){
		for (auto v : e[i]){
			unite(i, v.first);
		}
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++ i){
		if (find(i) != i) continue;
		if (cnt[4][i]){
			int x = cnt[1][i] + cnt[2][i] + cnt[3][i] + cnt[4][i];
			ans += 1ll * x * x;
		}
		else{
			if (!cnt[1][i] || !cnt[2][i] || !cnt[3][i]){
				ans += cnt[0][i] >> 1;
			}
			else{
				for (int j = 1; j <= 3; ++ j){
					ans += 1ll * cnt[j][i] * cnt[j % 3 + 1][i];
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
