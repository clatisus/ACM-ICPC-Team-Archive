#include<bits/stdc++.h>

const int N = 210;

int n, m, r;
int v[N], a[N], mat[N][N], dis[N][N];

int main(){
	scanf("%d%d%d", &n, &m, &r);
	for (int i = 0; i < r; ++ i){
		scanf("%d", &v[i]);
	}
	for (int i = 0, u, v, w; i < m; ++ i){
		scanf("%d%d%d", &u, &v, &w);
		mat[u][v] = mat[v][u] = w;
	}
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j <= n; ++ j){
			if (mat[i][j]){
				dis[i][j] = dis[j][i] = mat[i][j];
			}
		}
	}
	for (int k = 1; k <= n; ++ k){
		for (int i = 1; i <= n; ++ i){
			for (int j = 1; j <= n; ++ j){
				if (k == i || k == j){
					continue;
				}
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	for (int i = 0; i < r; ++ i){
		a[i] = i;
	}
	int ans = INT_MAX;
	do{
		int sum = 0;
		for (int i = 0; i < r - 1; ++ i){
			sum += dis[v[a[i]]][v[a[i + 1]]];
		}
		ans = std::min(sum, ans);
	}
	while (std::next_permutation(a, a + r));
	return printf("%d\n", ans), 0;
}
