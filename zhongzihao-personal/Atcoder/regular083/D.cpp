#include<bits/stdc++.h>

const int N = 310;

int mat[N][N], dis[N][N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		for (int j = 0; j < n; ++ j){
			scanf("%d", &mat[i][j]);
			dis[i][j] = mat[i][j];
		}
	}
	for (int k = 0; k < n; ++ k){
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < n; ++ j){
				if (i == j || i == k || j == k) continue;
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	long long ans = 0;
	for (int i = 0; i < n; ++ i){
		for (int j = 0; j < n; ++ j){
			if (dis[i][j] != mat[i][j]){
				return printf("-1\n"), 0;
			}
			bool flag = true;
			for (int k = 0; k < n; ++ k){
				if (i == k || i == j || k == j) continue;
				if (dis[i][k] + dis[k][j] == dis[i][j]){
					flag = false;
					break;
				}
			}
			if (flag) ans += mat[i][j];
		}
	}
	return printf("%lld\n", ans >> 1), 0;
}
