#include<bits/stdc++.h>

const int N = 410;
const int M = 100010;

std::bitset <N> set[N];
bool flag[N];
int n, m;
int x[M], y[M];

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++ i){
		scanf("%d%d", &x[i], &y[i]);
	}
	for (int i = 1; i <= n; ++ i){
		set[i][i] = 1;
		for (int j = m; j; -- j){
			if (set[i][x[j]] && set[i][y[j]]){
				flag[i] = true;
				break;
			}
			if (!set[i][x[j]] && !set[i][y[j]]){
				continue;
			}
			set[i][x[j]] = set[i][y[j]] = 1;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i){
		for (int j = i + 1; j <= n; ++ j){
			if (flag[i] || flag[j]){
				continue;
			}
			ans += (set[i] & set[j]).none();
		}
	}
	return printf("%d\n", ans), 0;
}
