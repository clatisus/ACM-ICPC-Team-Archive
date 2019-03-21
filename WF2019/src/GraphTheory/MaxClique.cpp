struct MaxClique{
	bool g[MAXN][MAXN];
	int n, nmax[MAXN], alt[MAXN][MAXN], ans;
	void init(int n){
		this -> n = n;
		memset(g, 0, sizeof(g));
	}
	bool dfs(int cur, int tot){
		if(!cur){
			if(ans < tot){ ans = tot; return 1; }
			return false;
		}
		for(int i = 0; i < cur; ++ i){
			if(tot + (cur - i) <= ans) return 0;
			int u = alt[tot][i];
			if(tot + nmax[u] <= ans) return 0;
			int nxt = 0;
			for(int j = i + 1; j < cur; ++ j)
				if(g[u][alt[tot][j]])
					alt[tot + 1][nxt ++] = alt[tot][j];
			if(dfs(nxt, tot + 1)) return 1;
		}
		return 0;
	}
	int solve(){
		ans = 0;
		memset(nmax, 0, sizeof(nmax));
		for(int i = n; i; -- i){
			int cur = 0;
			for(int j = i + 1; j <= n; ++ j)
				if(g[i][j]) alt[1][cur ++] = j;
			dfs(cur, 1);
			nmax[i] = ans;
		}
		return ans;
	}
};
