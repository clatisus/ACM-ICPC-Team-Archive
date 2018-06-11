#include<bits/stdc++.h>
#define ll long long

const int N = 1000010;

struct edge{
	int next, to;
	ll w;
};

edge e[N << 1];
int n, deg[N], first[N], e_cnt = 1;
ll a[N];
ll orz[N];

void addedge(int u, int v){
	e[++ e_cnt] = {first[u], v};
	first[u] = e_cnt;
	e[++ e_cnt] = {first[v], u};
	first[v] = e_cnt;
}

void dfs(int i, int fa){
	for (int j = first[i]; j; j = e[j].next){
		int x = e[j].to;
		++ deg[i];
		if (x != fa){
			dfs(x, i);
		}
	}
}

void solve(int i, int fa){
	for (int j = first[i]; j; j = e[j].next){
		int x = e[j].to;
		if (x == fa){
			continue;
		}
		solve(x, i);
		if (deg[x] > 1){
			e[j].w = e[j ^ 1].w = 2 * a[x] - orz[x];
		}
		else{
			e[j].w = e[j ^ 1].w = a[x] - orz[x];
		}
		if (e[j].w < 0 || e[j].w > a[i] || e[j].w > a[x]){
			printf("NO\n");
			exit(0);
		}
		orz[i] += e[j].w;
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%lld", &a[i]);
	}
	for (int i = 0, u, v; i < n - 1; ++ i){
		scanf("%d%d", &u, &v);
		addedge(u, v);
	}
	if (n == 2){
		return printf(a[1] == a[2] ? "YES\n" : "NO\n"), 0;
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++ i){
		if (deg[i] > 1){
			solve(i, 0);
			ll sum = 0;
			for (int j = first[i]; j; j = e[j].next){
				sum += e[j].w;
			}
			if (sum != 2 * a[i]){
				return printf("NO\n"), 0;
			}
			break;
		}
	}
	return printf("YES\n"), 0;
}
