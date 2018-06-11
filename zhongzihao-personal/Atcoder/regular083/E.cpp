#include<bits/stdc++.h>

const int N = 1010;
const int M = 5010;

bool dp[N][M], aux[M];
bool vis[N];
std::vector <int> e[N];

void dfs(int u){
	vis[u] = true;
	memset(aux, 0, sizeof(aux));
	for (auto v : e[u]){
		dfs(v);
		if (!vis[v]){
			vis[u] = false;
			break;
		}
		
	}
}

int main(){
	int n;
	for (int i = 2, x; i <= n; ++ i){
		scanf("%d", &x);
		e[x].push_back(i);
	}
	dfs(1);
	
}
