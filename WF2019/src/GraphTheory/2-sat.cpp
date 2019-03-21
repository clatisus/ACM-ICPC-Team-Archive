struct twoSat{   //for 2-sat MAXN is double large
    int col[MAXN];
    std::vector<int> vec[MAXN << 1];
    int dfn[MAXN << 1], low[MAXN << 1], bel[MAXN << 1], ncnt, scnt;
    bool vis[MAXN << 1];
    std::stack<int> stack;
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
};
