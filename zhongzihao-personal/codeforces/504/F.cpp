#include<bits/stdc++.h>

const int N = 500010;
typedef std::pair <int, int> pii;
typedef std::pair <pii, int> piii;
typedef long long ll;
const int M = 20;

std::vector <int> e[N];
std::set <pii> set[N];
bool vis[N];
int root[N], dep[N];
std::vector <pii> event[N];
int fa[N][M];

ll ans;
bool flag;

void dfs(int u, int fa, int root){
    ::root[u] = root;
    vis[u] = true;
    ::fa[u][0] = fa;
    for (int i = 1; i < M; ++ i){
        ::fa[u][i] = ::fa[::fa[u][i - 1]][i - 1];
    }
    for (auto v : e[u]){
        if (!vis[v]){
            dep[v] = dep[u] + 1;
            dfs(v, u, root);
        }
    }
}

void solve(int u, int fa, int root){
    vis[u] = true;
    int sit = 0;
    for (auto v : e[u]){
        if (fa != v){
            solve(v, u, root);
            if (set[v].size() > set[sit].size()){
                sit = v;
            }
        }
    }
    for (auto v : e[u]){
        if (v == sit || v == fa) continue;
        for (auto w : set[v]){
            set[u].insert(w);
        }
    }
    for (auto v : event[u]){
        set[u].erase(v);
    }
    if (u == root) return;
    if (set[u].empty()){
        flag = true;
    }
    else{
        ans += set[u].begin() -> first;
    }
}

int lca(int u, int v){
    if (dep[u] < dep[v]){
        std::swap(u, v);
    }
    while (dep[u] > dep[v]){
        u = fa[u][0];
    }
    for (int i = M - 1; i >= 0; -- i){
        if (fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main(){
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 0, u, v; i < k; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; ++ i){
        if (!vis[i]){
            dfs(i, 0, i);
        }
    }
    for (int i = 1, u, v, w; i <= m; ++ i){
        scanf("%d%d%d", &u, &v, &w);
        if (root[u] == root[v]){
            int l = lca(u, v);
            set[u].insert({w, u});
            set[v].insert({w, v});
            event[l].push_back({w, u});
            event[l].push_back({w, v});
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++ i){
        if (!vis[i]){
            solve(i, 0, i);
        }
    }
    if (flag){
        ans = -1;
    }
    printf("%lld\n", ans);
    return 0;
}
