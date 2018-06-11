#include<bits/stdc++.h>
#define ll long long

const int N = 1000010;

struct edge{
	int next, to;
};

edge e[N << 2];
bool vis[N];
int first[N], n, m, e_cnt = 0, col[N], gl;

void addedge(int u, int v){
	e[++ e_cnt] = {first[u], v};
	first[u] = e_cnt;
	e[++ e_cnt] = {first[v], u};
	first[v] = e_cnt;
}

void dfs(int u){
	vis[u] = true;
	for (int i = first[u]; i; i = e[i].next){
		int v = e[i].to;
		if (vis[v]){
			if (col[v] == col[u]){
				gl = 1;
			}
			continue;
		}
		col[v] = !col[u];
		dfs(v);
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		addedge(u, v);
	}
	int a = 0, n1 = 0, n2 = 0;
	for (int i = 1; i <= n; ++ i){
		if (!first[i]){
			++ a;
			continue;
		}
		if (vis[i]){
			continue;
		}
		gl = 0;
		dfs(i);
		gl ? ++ n2 : ++ n1;
	}
	ll ans = 2ll * a * n - 1ll * a * a;
	ans += 2ll * n1 * n1 + 1ll * n2 * n2 + 2ll * n1 * n2;
	return printf("%lld\n", ans), 0;
}
