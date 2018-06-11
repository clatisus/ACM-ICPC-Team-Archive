#include<bits/stdc++.h>

const int N = 2010;

int a[N][N];
int n, m, test;
int pre[N][N], preleft[N][N], preup[N][N];

int query(int (*pre)[N], int x1, int y1, int x2, int y2){
	if (x1 > x2 || y1 > y2) return 0;
	return pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
}

int main(){
	scanf("%d%d%d", &n, &m, &test);
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j <= m; ++ j){
			scanf("%1d", &a[i][j]);
			pre[i][j] = a[i][j];
		}
	}
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j <= m; ++ j){
			if (a[i][j]){
				if (a[i - 1][j]){
					preup[i][j] = 1;
				}
				if (a[i][j - 1]){
					preleft[i][j] = 1;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++ i){
		for (int j = 0; j <= m; ++ j){
			pre[i][j] += pre[i - 1][j];
			preup[i][j] += preup[i - 1][j];
			preleft[i][j] += preleft[i - 1][j];
		}
	}
	for (int i = 0; i <= n; ++ i){
		for (int j = 1; j <= m; ++ j){
			pre[i][j] += pre[i][j - 1];
			preup[i][j] += preup[i][j - 1];
			preleft[i][j] += preleft[i][j - 1];
		}
	}
	while (test --){
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		printf("%d\n", query(pre, x1, y1, x2, y2) - query(preup, x1 + 1, y1, x2, y2) - query(preleft, x1, y1 + 1, x2, y2));
	}
	return 0;
}
