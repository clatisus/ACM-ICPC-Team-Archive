#include<bits/stdc++.h>

typedef std::pair <int, int> pii;

const int N = 100010;

pii x[N], y[N];
int fa[N];
std::vector <std::pair <int, pii>> e;

int find(int u){
	return fa[u] == u ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v){
	int _u = find(u), _v = find(v);
	fa[_u] = _v;
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0, u, v; i < n; ++ i){
		scanf("%d%d", &u, &v);
		x[i] = {u, i};
		y[i] = {v, i};
	}
	std::sort(x, x + n);
	std::sort(y, y + n);
	for (int i = 0; i < n - 1; ++ i){
		e.push_back({x[i + 1].first - x[i].first, {x[i].second, x[i + 1].second}});
		e.push_back({y[i + 1].first - y[i].first, {y[i].second, y[i + 1].second}});
	}
	std::sort(e.begin(), e.end());
	for (int i = 0; i < N; ++ i){
		fa[i] = i;
	}
	long long ans = 0;
	for (auto u : e){
		int v = u.second.first, w = u.second.second;
		if (find(v) != find(w)){
			unite(v, w);
			ans += u.first;
		}
	}
	return printf("%lld\n", ans), 0;
}
