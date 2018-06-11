#include<bits/stdc++.h>

const int N = 100010;

struct edge{
	int next, to;
};

edge e[N];
int first[N], vis[N], a[N], e_cnt = 0;
std::vector <int> ans;

void addedge(int u, int v){
	e[++ e_cnt] = {first[u], v};
	first[u] = e_cnt;
}

void dfs(int u){
	if (vis[u]){
		printf("-1\n");
		exit(0);
	}
	vis[u] = true;
	ans.push_back(u);
	for (int i = first[u]; i; i = e[i].next){
		dfs(e[i].to);
	}
}

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; ++ i){
		scanf("%d", &a[i]);
	}
	for (int i = 1, t; i <= n; ++ i){
		scanf("%d", &t);
		for (int j = 0, x; j < t; ++ j){
			scanf("%d", &x);
			addedge(i, x);
		}
	}
	for (int i = 0; i < k; ++ i){
		if (!vis[a[i]]){
			dfs(a[i]);
		}
	}
	printf("%d\n", (int) ans.size());
	reverse(ans.begin(), ans.end());
	for (auto u : ans){
		printf("%d ", u);
	}
	return printf("\n"), 0;
}
