#include<bits/stdc++.h>

const int N = 200010;

std::vector <int> vec[N];
int fa1[N], fa2[N], n, k, l, cnt[N], ans[N];

int find(int fa[], int u){
	return fa[u] == u ? u : fa[u] = find(fa, fa[u]);
}

int unite(int fa[], int u, int v){
	int _u = find(fa, u), _v = find(fa, v);
	fa[_u] = _v;
}

int main(){
	scanf("%d%d%d", &n, &k, &l);
	for (int i = 1; i <= n; ++ i){
		fa1[i] = i;
		fa2[i] = i;
	}
	for (int i = 0, u, v; i < k; ++ i){
		scanf("%d%d", &u, &v);
		if (find(fa1, u) == find(fa1, v)){
			continue;
		}
		unite(fa1, u, v);
	}
	for (int i = 0, u, v; i < l; ++ i){
		scanf("%d%d", &u, &v);
		if (find(fa2, u) == find(fa2, v)){
			continue;
		}
		unite(fa2, u, v);
	}
	for (int i = 1; i <= n; ++ i){
		find(fa1, i);
		find(fa2, i);
	}
	for (int i = 1; i <= n; ++ i){
		vec[fa1[i]].push_back(i);
	}
	for (int i = 0; i <= n; ++ i){
		for (int j = 0; j < vec[i].size(); ++ j){
			++ cnt[fa2[vec[i][j]]];
		}
		for (int j = 0; j < vec[i].size(); ++ j){
			ans[vec[i][j]] = cnt[fa2[vec[i][j]]];
		}
		for (int j = 0; j < vec[i].size(); ++ j){
			cnt[fa2[vec[i][j]]] = 0;
		}
	}
	for (int i = 1; i <= n; ++ i){
		printf("%d ", ans[i]);
	}
	putchar('\n');
	return 0;
}
