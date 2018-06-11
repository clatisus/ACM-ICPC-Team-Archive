#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;

std::vector <int> e[N];
ll a[N], b[N], k[N], sz[N];
int n;

void dfs(int u){
	for (auto v : e[u]){
		dfs(v);
		if (a[v] >= b[v]){
			a[u] += a[v] - b[v];
		}
	}
	for (auto v : e[u]){
		if (a[v] < b[v]){
			double x = 1.0 * (b[v] - a[v]) * k[v];
			if (x > 1e18){
				printf("NO\n");
				exit(0);
			}
			a[u] -= (b[v] - a[v]) * k[v];
		}
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%I64d", &a[i]);
	}
	for (int i = 1; i <= n; ++ i){
		scanf("%I64d", &b[i]);
	}
	for (int i = 2, x; i <= n; ++ i){
		scanf("%d%I64d", &x, &k[i]);
		e[x].push_back(i);
	}
	dfs(1);
	return printf(a[1] >= b[1] ? "YES\n" : "NO\n"), 0;
}
