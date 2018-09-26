#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;

int n, m;
std::vector <int> e[N], _e[N], ring[N];
int col[N];
double ans[N];
int vis[N];
int fa[N];
ll cnt[N];
std::vector <int> stack;

void dfs(int u, int id){
    stack.push_back(u);
    vis[u] = id;
    for (auto v : _e[u]){
        if (vis[v] == id){
            ring[v] = stack;
            continue;
        }
        dfs(v, id);
    }
    stack.pop_back();
}

int find(int u){
    return fa[u] == u ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v){
    u = find(u), v = find(v);
    if (u == v) return;
    fa[u] = v;
}

void solve(){
    for (int i = 0; i < N; ++ i){
        e[i].clear();
        _e[i].clear();
        ring[i].clear();
    }
    for (int i = 0, u, v; i < m; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; ++ i){
        col[i] = i;
        fa[i] = i;
    }
    for (int i = 1; i <= n; ++ i){
        for (auto v : e[i]){
            col[v] = col[i];
        }
    }
    for (int i = 1; i <= n; ++ i){
        _e[col[i]].push_back(i);
        unite(col[i], i);
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++ i){
        if (!vis[i]){
            dfs(i, i);
        }
    }
    for (int i = 1; i <= n; ++ i){
        col[i] = i;
        cnt[i] = n;
    }
    for (int i = 1; i <= n; ++ i){
        for (auto v : e[i]){
            cnt[col[v]] -= n - i;
            cnt[col[i]] += n - i;
            col[v] = col[i];
        }
    }
    for (int i = 1; i <= n; ++ i){
        if (find(i) != i){
            cnt[fa[i]] += cnt[i];
        }
    }
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= n; ++ i){
        if (ring[i].empty()) continue;
        for (auto u : ring[i]){
            ans[u] = 1.0 * cnt[find(u)] / n / ring[i].size();
        }
    }
    std::sort(ans + 1, ans + n + 1, std::greater <double>());
    for (int i = 1; i <= n; ++ i){
        if (ans[i] > 1e-9){
            printf("%.6f\n", ans[i]);
        }
    }
}

int main(){
    while (scanf("%d%d", &n, &m) != EOF){
        solve();
    }
    return 0;
}
