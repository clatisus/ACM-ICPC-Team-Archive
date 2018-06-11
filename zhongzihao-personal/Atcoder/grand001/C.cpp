#include<bits/stdc++.h>

const int N = 2010;

std::vector <int> e[N];
int dis[N];

void dfs(int u, int fa){
	for (auto v : e[u]){
		if (v == fa) continue;
		dis[v] = dis[u] + 1;
		dfs(v, u);
	}
}

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0, u, v; i < n - 1; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int min = INT_MAX;
	if (k & 1){
		for (int i = 1; i <= n; ++ i){
			for (auto u : e[i]){
				memset(dis, 0, sizeof(dis));
				dfs(u, i);
				dfs(i, u);
				int cnt = 0;
				for (int j = 1; j <= n; ++ j){
					cnt += dis[j] > k - 1 >> 1;
				}
				min = std::min(min, cnt);
			}
		}
	}
	else{
		for (int i = 1; i <= n; ++ i){
			memset(dis, 0, sizeof(dis));
			dfs(i, 0);
			int cnt = 0;
			for (int j = 1; j <= n; ++ j){
				cnt += dis[j] > k >> 1;
			}
			min = std::min(min, cnt);
		}
	}
	printf("%d\n", min);
	return 0;
}
