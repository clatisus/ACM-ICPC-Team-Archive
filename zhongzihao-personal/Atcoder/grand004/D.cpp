#include<bits/stdc++.h>

const int N = 100010;
typedef std::pair <int, int> pii;

int a[N];
std::vector <int> e[N];
int dep[N];
std::set <pii, std::greater <pii>> set;

void dfs(int u){
	for (auto v : e[u]){
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

void dfs1(int u){
	set.erase({dep[u], u});
	for (auto v : e[u]){
		if (set.count({dep[v], v})){
			dfs1(v);
		}
	}
}

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	int ans = a[1] != 1;
	a[1] = 1;
	for (int i = 2; i <= n; ++ i){
		e[a[i]].push_back(i);
	}
	dfs(1);
	for (int i = 1; i <= n; ++ i){
		set.insert({dep[i], i});
	}
	while (!set.empty()){
		pii p = *(set.begin());
		if (p.first <= k){
			break;
		}
		int u = p.second;
		for (int i = 0; i < k - 1; ++ i){
			u = a[u];
		}
		dfs1(u);
		++ ans;
	}
	printf("%d\n", ans);
	return 0;
}
