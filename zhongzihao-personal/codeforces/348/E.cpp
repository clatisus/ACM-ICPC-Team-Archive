#include<bits/stdc++.h>

int n, m1, m2;

const int MAXN = 2010;

struct twoSat{   //for 2-sat MAXN is two times large
	
	int col[MAXN];
	std::vector<int> vec[MAXN << 1], e[MAXN << 1];
	int dfn[MAXN << 1], low[MAXN << 1], bel[MAXN << 1], ncnt, scnt;
	bool vis[MAXN << 1];
	std::stack<int> stack;
	std::bitset <MAXN << 1> arr[MAXN << 1];
	
	void tarjan(int u){
		dfn[u] = low[u] = ++ ncnt;
		stack.push(u);
		vis[u] = true;
		for(auto v : vec[u]){
			if(!dfn[v]){
				tarjan(v);
				low[u] = std::min(low[u], low[v]);
			}
			else if(vis[v]){
				low[u] = std::min(low[u], dfn[v]);
			}
		}
		if(low[u] == dfn[u]){
			int v; ++ scnt;
			do{
				v = stack.top(); stack.pop();
				vis[v] = false;
				bel[v] = scnt;
			}while(v != u);
		}
	}
	
	void addedge(int u, int v){
		vec[u].push_back(v);
	}
	
	bool solve(){ //tarjan + topsort
	    memset(dfn, 0, sizeof(dfn));
	    memset(vis, 0, sizeof(vis));
	    ncnt = scnt = 0;
	    for(int i = 1; i <= n + n; ++ i){
		    if(!dfn[i]){
			    tarjan(i);
			}
		}
		for(int i = 1; i <= n; ++ i){
			if(bel[i] == bel[i + n]){
				return false;
			}
		}
		for(int i = 1; i <= n; ++ i){
			col[i] = (bel[i] < bel[i + n]);
		}
		
		return true;
	}
	
	void top(int u){
		for (int i = 1; i <= n << 1; ++ i){
			if (bel[i] == u){
				arr[u].set(i);
			}
		}
		for (auto v : e[u]){
			if (!vis[v]){
				top(v);
			}
			arr[u] |= arr[v];
		}
	}
	
	void solveTop(){
		static std::bitset <MAXN << 1> set[MAXN << 1];
		for (int i = 1; i <= n << 1; ++ i){
			for (auto u : vec[i]){
				e[bel[i]].push_back(bel[u]);
			}
		}
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= scnt; ++ i){
			if (!vis[i]){
				top(i);
			}
		}
		for (int i = 1; i <= n << 1; ++ i){
			set[i] = arr[bel[i]];
		}
		for (int i = 1; i <= n << 1; ++ i){
			arr[i] = set[i];
		}
	}
};

twoSat sat1, sat2;

const int N = 1000010;
typedef std::pair <int, int> pii;
inline int inv(int x){return x <= n ? x + n : x - n;}

pii query[2][N];

int main(){
	scanf("%d%d%d", &n, &m1, &m2);
	for (int i = 0, u, v; i < m1; ++ i){
		scanf("%d%d", &u, &v);
		if (u < 0){
			u = inv(-u);
		}
		if (v < 0){
			v = inv(-v);
		}
		query[0][i] = {u, v};
		sat1.addedge(inv(u), v);
		sat1.addedge(inv(v), u);
	}
	for (int i = 0, u, v; i < m2; ++ i){
		scanf("%d%d", &u, &v);
		if (u < 0){
			u = inv(-u);
		}
		if (v < 0){
			v = inv(-v);
		}
		query[1][i] = {u, v};
		sat2.addedge(inv(u), v);
		sat2.addedge(inv(v), u);
	}
	bool flag1 = sat1.solve(), flag2 = sat2.solve();
	if (!flag1 && !flag2){
		puts("SIMILAR");
		return 0;
	}
	if (flag1 && !flag2){
		for (int i = 1; i <= n; ++ i){
			printf("%d%c", sat1.col[i] ? 1 : 0, " \n"[i == n]);
		}
		return 0;
	}
	if (!flag1 && flag2){
		for (int i = 1; i <= n; ++ i){
			printf("%d%c", sat2.col[i] ? 1 : 0, " \n"[i == n]);
		}
		return 0;
	}
	sat1.solveTop(), sat2.solveTop();
	for (int i = 0; i < m1; ++ i){
		
	}
}
