#include <bits/stdc++.h>

const int N = 100010;
std::multiset <int> a, b;
std::map <int, int> Hash;
int fa[N], numa[N], numb[N];
int n;

int find(int u){
	return u == fa[u] ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v){
	int _u = find(u), _v = find(v);
	if (_u == _v){
		return;
	}
	fa[_u] = _v;
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &numa[i]);
		a.insert(numa[i]);
		numa[0] ^= numa[i];
	}
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &numb[i]);
		b.insert(numb[i]);
		numb[0] ^= numb[i];
	}
	a.insert(numa[0]);
	b.insert(numb[0]);
	if (a != b){
		return printf("-1\n"), 0;
	}
	Hash[numa[0]] = Hash[numb[0]] = 0;
	for (int i = 1; i <= n; ++ i){
		if (numa[i] != numb[i]){
			Hash[numa[i]] = Hash[numb[i]] = 0;
		}
	}
	int cnt = 0;
	for (auto &u : Hash){
		u.second = cnt ++;
	}
	for (int i = 0; i < N; ++ i){
		fa[i] = i;
	}
	int ans = -1;
	for (int i = 1; i <= n; ++ i){
		if (numa[i] != numb[i]){
			unite(Hash[numa[i]], Hash[numb[i]]);
			++ ans;
		}
	}
	for (int i = 0; i < cnt; ++ i){
		find(i);
		if (fa[i] == i){
			++ ans;
		}
	}
	return printf("%d\n", ans), 0;
}
