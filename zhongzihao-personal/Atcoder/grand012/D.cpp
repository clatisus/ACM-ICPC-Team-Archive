#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 400010;

int n, x, y;
int fa[N], _cnt[N], fac[N], inv[N];
std::pair <int, int> p[N];
std::vector <int> cnt[N];
std::set <int> rollback;

int power_mod(int a, int exp){
	int ret = 1;
	while (exp){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
		exp >>= 1;
	}
	return ret;
}

int comb(int n, int m){
	return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

int find(int u){
	return u == fa[u] ? u : fa[u] = find(fa[u]);
}

void unite(int u, int v){
	int _u = find(u), _v = find(v);
	if (_u == _v){
		return;
	}
	fa[_u] = _v;
	find(v);
}

int main(){
	for (int i = 0; i < N; ++ i){
		fa[i] = i;
	}
	fac[0] = 1;
	for (int i = 1; i < N; ++ i){
		fac[i] = 1ll * fac[i - 1] * i % moder;
	}
	inv[N - 1] = power_mod(fac[N - 1], moder - 2);
	for (int i = N - 1; i; -- i){
		inv[i - 1] = 1ll * inv[i] * i % moder;
	}
	scanf("%d%d%d", &n, &x, &y);
	for (int i = 0; i < n; ++ i){
		scanf("%d%d", &p[i].first, &p[i].second);
	}
	std::sort(p, p + n);
	if (p[0].first == p[n - 1].first){
		return printf("1\n"), 0;
	}
	int sit, sit1 = 0, sit2 = 0, min1 = INT_MAX, min2 = INT_MAX;
	for (int i = 0; i < n; ++ i){
		if (!i || p[i].first != p[i - 1].first){
			sit = i;
			if (p[i].second <= min1){
				min2 = min1;
				sit2 = sit1;
				min1 = p[i].second;
				sit1 = i;
			}
			else if (p[i].second <= min2){
				min2 = p[i].second;
				sit2 = i;
			}
		}
		if (p[i].second + p[sit].second <= x){
			unite(i, sit);
		}
	}
	for (int i = 0; i < n; ++ i){
		if (p[sit1].second + p[i].second <= y && p[i].first != p[sit1].first){
			unite(sit1, i);
		}
		if (p[sit2].second + p[i].second <= y && p[i].first != p[sit2].first){
			unite(sit2, i);
		}
	}
	for (int i = 0; i < n; ++ i){
		find(i);
		cnt[fa[i]].push_back(p[i].first);
	}
	int ans = 1;
	for (int i = 0; i < n; ++ i){
		if (!cnt[i].size()){
			continue;
		}
		rollback.clear();
		int sum = cnt[i].size();
		for (auto u : cnt[i]){
			++ _cnt[u];
			rollback.insert(u);
		}
		for (auto u : rollback){
			ans = 1ll * ans * comb(sum, _cnt[u]) % moder;
			sum -= _cnt[u];
		}
		for (auto u : rollback){
			_cnt[u] = 0;
		}
	}
	return printf("%d\n", ans), 0;
}
