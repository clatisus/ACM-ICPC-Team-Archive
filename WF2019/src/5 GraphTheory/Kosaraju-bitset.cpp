struct BIT{
	ui v[8];
	void clear(){ for(int i = 0; i < 8; ++ i) v[i] = 0; }
	void set(int x){       v[x >> 5] |= 1U << (x & 31); }
	void flip(int x){      v[x >> 5] ^= 1U << (x & 31); }
	int get(int x){ return v[x >> 5] >> (x & 31) & 1; }
}vis, gra[MAXN], arg[MAXN];
int n, m, k, now;
char str[MAXN];
std::stack<int> stack;
void sfd(int u){
	vis.flip(u);
	for(int i = 0; i < 8; ++ i) while(1){
		ui o = vis.v[i] & arg[u].v[i]; if(!o) break;
		sfd(i << 5 | __builtin_ctz(o));
	}
	stack.push(u);
}
void dfs(int u){
	vis.flip(u); ++ now;
	for(int i = 0; i < 8; ++ i) while(1){
		ui o = vis.v[i] & gra[u].v[i]; if(!o) break;
		dfs(i << 5 | __builtin_ctz(o));
	}
}
int main(){
	int test;scanf("%d", &test);
	while(test --){
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i) gra[i].clear(), arg[i].clear();
		for(int i = 0; i < n; ++i){
			scanf("%s", str);
			for(int j = 0; j < n; ++ j)
				if(str[j] == '1'){
					gra[i].set(j); arg[j].set(i);
				}
		}
		while(m --){
			scanf("%d", &k);
			while(k --){
				int u, v;
				scanf("%d%d", &u, &v); --u; --v;
				gra[u].flip(v); arg[v].flip(u);
			}
			for(int i = 0; i < n; ++i) vis.set(i);
			for(int i = 0; i < n; ++i) if(vis.get(i)) sfd(i);
			int ans = 0;
			for(int i = 0; i < n; ++i) vis.set(i);
			while(!stack.empty()){
				int i = stack.top(); stack.pop();
				if(vis.get(i)){
					now = 0; dfs(i);
					ans += now * (now - 1) / 2;
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
