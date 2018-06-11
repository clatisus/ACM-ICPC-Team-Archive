#include<bits/stdc++.h>

const int N = 60;

int n, m;
int a[N][2], b[N][2];

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i){
		scanf("%d%d", &a[i][0], &a[i][1]);
	}
	for (int i = 1; i <= m; ++ i){
		scanf("%d%d", &b[i][0], &b[i][1]);
	}
	for (int i = 1; i <= n; ++ i){
		int min = INT_MAX, sit;
		for (int j = 1; j <= m; ++ j){
			int x = std::abs(a[i][0] - b[j][0]) + std::abs(a[i][1] - b[j][1]);
			if (x < min){
				min = x;
				sit = j;
			}
		}
		printf("%d\n", sit);
	}
	return 0;
}
