#include<bits/stdc++.h>

const int N = 300010;
typedef std::pair <int, int> pii;
typedef long long ll;

int fa[N];
std::vector <pii> rollback;
ll R = 0;

int find(int u){
	if (fa[u] == u) return u;
	int x = find(fa[u]);
	rollback.push_back({u, fa[u]});
	return fa[u] = x;
}

void unite(int u, int v){
	int _u = find(u), _v = find(v);
	if (_u == _v) return;
	rollback.push_back({_u, fa[_u]});
	fa[_u] = _v;
}

int calc(int n, int moder){
	int ret = (n + R) % moder;
	return ret ? ret : moder;
}

bool solve(int moder){
	int n, m;
	scanf("%d%d", &n, &m);
	std::vector <int> vec;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		vec.push_back(calc(x, moder));
	}
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		unite(calc(u, moder), calc(v, moder));
	}
	bool ret = true;
	for (auto u : vec){
		if (find(u) != find(vec[0])){
			ret = false;
			break;
		}
	}
	for (int i = rollback.size() - 1; i >= 0; -- i){
		fa[rollback[i].first] = rollback[i].second;
	}
	rollback.clear();
	return ret;
}

int main(){
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; ++ i){
		fa[i] = i;
	}
	for (int i = 1, u, v; i <= m; ++ i){
		scanf("%d%d", &u, &v);
		unite(u, v);
	}
	for (int i = 1; i <= n; ++ i){
		find(i);
	}
	rollback.clear();
	for (int i = 1; i <= n; ++ i){
		bool ans = solve(n);
		puts(ans ? "YES" : "NO");
		if (ans) R += i;
	}
	return 0;
}
