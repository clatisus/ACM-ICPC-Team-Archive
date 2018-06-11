#include<bits/stdc++.h>

const int N = 100010;
const int M = 20;

int vis[N][M], col[N], n, m, q, v[N], d[N], c[N];
std::vector <int> e[N];

void paint(int u, int dis, int color){
	if (vis[u][dis]){
		return;
	}
	vis[u][dis] = true;
	if (!dis){
		col[u] = color;
		return;
	}
	paint(u, dis - 1, color);
	for (auto v : e[u]){
		paint(v, dis - 1, color);
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; ++ i){
		scanf("%d%d%d", &v[i], &d[i], &c[i]);
	}
	for (int i = q - 1; ~i; -- i){
		paint(v[i], d[i], c[i]);
	}
	for (int i = 1; i <= n; ++ i){
		printf("%d\n", col[i]);
	}
	return 0;
}
