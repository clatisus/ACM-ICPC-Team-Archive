#include<bits/stdc++.h>

const int N = 100010;
typedef std::pair <int, int> pii;

int fa[N], sz[N];
pii e[N];
int left[N], right[N];
int x[N], y[N], z[N];
std::vector <int> vec[N];

int find(int u){
	if (fa[u] == u) return u;
	fa[u] = find(fa[u]);
	sz[u] = sz[fa[u]];
	return fa[u];
}

void unite(int u, int v){
	int _u = find(u), _v = find(v);
	if (_u == _v) return;
	fa[_u] = _v;
	sz[_v] += sz[_u];
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; ++ i){
		scanf("%d%d", &u, &v);
		e[i] = {u, v};
	}
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; ++ i){
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
		left[i] = 1, right[i] = m;
	}
	while (true){
		for (int i = 1; i <= m; ++ i) vec[i].clear();
		for (int i = 1; i <= q; ++ i){
			int mid = left[i] + right[i] >> 1;
			vec[mid].push_back(i);
		}
		for (int i = 1; i <= n; ++ i){
			fa[i] = i;
			sz[i] = 1;
		}
		for (int i = 1; i <= m; ++ i){
			unite(e[i].first, e[i].second);
			for (auto u : vec[i]){
				find(x[u]), find(y[u]);
				int cnt = 0;
				if (fa[x[u]] == fa[y[u]]){
					cnt = sz[x[u]];
				}
				else{
					cnt = sz[x[u]] + sz[y[u]];
				}
				if (cnt >= z[u]){
					right[u] = i;
				}
				else{
					left[u] = i + 1;
				}
			}
		}
		bool flag = true;
		for (int i = 1; i <= q; ++ i){
			if (left[i] != right[i]){
				flag = false;
				break;
			}
		}
		if (flag) break;
	}
	for (int i = 1; i <= q; ++ i){
		printf("%d\n", left[i]);
	}
	return 0;
}
