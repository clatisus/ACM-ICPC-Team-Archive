#include<bits/stdc++.h>

const int N = 410;
const int M = 100010;

bool set[N][N], flag[N];
int n, m;
int x[M], y[M];

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++ i){
		scanf("%d%d", &x[i], &y[i]);
	}
	for (int i = 1; i <= n; ++ i){
		set[i][i] = true;
		for (int j = m; j; -- j){
			if (set[i][x[j]] && set[i][y[j]]){
				flag[i] = true;
				break;
			}
			if (!set[i][x[j]] && !set[i][y[j]]){
				continue;
			}
			set[i][x[j]] = set[i][y[j]] = true;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i){
		for (int j = i + 1; j <= n; ++ j){
			if (flag[i] || flag[j]){
				continue;
			}
			bool _flag = true;
			for (int k = 1; k <= n; ++ k){
				if (set[i][k] && set[j][k]){
					_flag = false;
					break;
				}
			}
			ans += _flag;
		}
	}
	return printf("%d\n", ans), 0;
}
