#include<bits/stdc++.h>

const int N = 210;

std::vector <int> e[N];
int col[N];
bool vis[N];

void dfs(int u){
	for (auto v : e[u]){
		if (vis[v]){
			if (col[v] == col[u]){
				puts("no");
				exit(0);
			}
		}
		else{
			vis[v] = true;
			col[v] = col[u] ^ 1;
			dfs(v);
		}
	}
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++ i){
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; ++ i){
		if (!vis[i]){
			dfs(i);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++ i){
		cnt += col[i];
	}
	puts("yes");
	printf("%d\n", cnt);
	for (int i = 1; i <= n; ++ i){
		if (col[i]){
			printf("%d%c", i, " \n"[cnt == 1]);
			-- cnt;
		}
	}
	return 0;
}
