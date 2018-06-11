#include<bits/stdc++.h>

const int N = 3010;

struct edge{
	int next, to;
};

edge e[N << 1];
int n, first[N], e_cnt = 0, a[N];
bool state[N];

void addedge(int u, int v){
	e[++ e_cnt] = {first[u], v};
	first[u] = e_cnt;
	e[++ e_cnt] = {first[v], u};
	first[v] = e_cnt;
}

void dfs(int i, int fa){
	for (int j = first[i]; j; j = e[j].next){
		int x = e[j].to;
		if (x == fa){
			continue;
		}
		dfs(x, i);
		if (!state[x] && a[x] < a[i]){
			state[i] = true;
		}
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	for (int i = 0, u, v; i < n - 1; ++ i){
		scanf("%d%d", &u, &v);
		addedge(u, v);
	}
	for (int i = 1; i <= n; ++ i){
		memset(state, 0, sizeof(state));
		dfs(i, 0);
		if (state[i]){
			printf("%d ", i);
		}
	}
	return 0;
}
