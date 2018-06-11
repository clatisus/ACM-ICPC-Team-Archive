#include<bits/stdc++.h>

const int N = 400010;
const int M = 21;

int a[N], v[N], dppre[1 << M], dpsuf[1 << M], pre[M][N], suf[M][N], ans[N];
int n, V, m;

int main(){
	scanf("%d%d", &n, &V);
	v[0] = V;
	for (int i = 1; ; ++ i){
		v[i] = v[i - 1] >> 1;
		if (!v[i]){
			m = i + 1;
			break;
		}
	}
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < m; ++ i){
		pre[i][n - 1] = n - 1;
		for (int j = n - 2; j >= 0; -- j){
			if (a[j + 1] - a[j] <= v[i]){
				pre[i][j] = pre[i][j + 1];
			}
			else{
				pre[i][j] = j;
			}
		}
	}
	for (int i = 0; i < M; ++ i){
		suf[i][0] = 0;
		for (int j = 0; j < n - 1; ++ j){
			if (a[j + 1] - a[j] <= v[i]){
				suf[i][j + 1] = suf[i][j];
			}
			else{
				suf[i][j + 1] = j + 1;
			}
		}
	}
	memset(dppre, -1, sizeof(dppre));
	for (int i = 0; i < 1 << m; ++ i){
		dpsuf[i] = n;
	}
	for (int i = 0; i < 1 << m - 1; ++ i){
		int x = dppre[i];
		for (int j = 0; j < m - 1; ++ j){
			if (i >> j & 1){
				continue;
			}
			int &y = dppre[i | 1 << j];
			if (x == n - 1){
				y = n - 1;
			}
			y = std::max(y, pre[j + 1][x + 1]);
		}
		x = dpsuf[i];
		for (int j = 0; j < m - 1; ++ j){
			if (i >> j & 1){
				continue;
			}
			int &y = dpsuf[i | 1 << j];
			if (!x){
				y = 0;
			}
			y = std::min(y, suf[j + 1][x - 1]);
		}
	}
	for (int i = 0; i < 1 << m - 1; ++ i){
		int j = (1 << m - 1) - i - 1;
		int x = dppre[i] + 1, y = dpsuf[j] - 1;
		if (x >= y){
			++ ans[0];
			-- ans[n];
		}
		if (pre[0][x] >= y){
			++ ans[suf[0][x]];
			-- ans[pre[0][y] + 1];
		}
	}
	for (int i = 0; i < n; ++ i){
		ans[i + 1] += ans[i];
		printf(ans[i] ? "Possible\n" : "Impossible\n");
	}
	return 0;
}
