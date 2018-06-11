#include<bits/stdc++.h>

const int N = 100;

char a[N][N], b[N][N];
int n, m;

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i){
		scanf("%s", a[i]);
	}
	for (int i = 0; i < m; ++ i){
		scanf("%s", b[i]);
	}
	for (int i = 0; i <= n - m; ++ i){
		for (int j = 0; j <= n - m; ++ j){
			bool flag = true;
			for (int ii = 0; ii < m; ++ ii){
				for (int jj = 0; jj < m; ++ jj){
					if (b[ii][jj] != a[i + ii][j + jj]){
						flag = false;
					}
				}
			}
			if (flag){
				return printf("Yes\n"), 0;
			}
		}
	}
	return printf("No\n"), 0;
}
