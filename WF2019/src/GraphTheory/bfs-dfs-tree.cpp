int dfn_l[MAXN], dfn_r[MAXN], f[MAXN][21], dep[MAXN], sz[MAXN];
int nxt[MAXN];
std::vector<int> vec[MAXN];
void bfs(int u){
	std::vector<int> que;
	que.push_back(u);
	int tot = 1;
	for(int i = 0; i < tot; ++ i){
		u = que[i];
		sz[u] = 1;
		for(auto v : vec[u]){
			if(v == f[u][0]) continue;
			dep[v] = dep[u] + 1;
			f[v][0] = u;
			for(int j = 0; f[v][j + 1] = f[f[v][j]][j]; ++ j);
			que.push_back(v);
			++ tot;
		}
	}
	for(int i = tot - 1; ~i; -- i) sz[f[que[i]][0]] += sz[que[i]];
	dfn_l[1] = 1;
	nxt[1] = 2;
	int last;
	for(int i = 1; i < tot; ++ i){
		if(f[que[i]][0] != f[que[i - 1]][0]) last = nxt[f[que[i]][0]];
		else last += sz[que[i - 1]];
		dfn_l[que[i]] = last;
		nxt[que[i]] = last + 1;
	}
	for(int i = 1; i <= n; ++ i) dfn_r[i] = dfn_l[i] + sz[i] - 1;
}
