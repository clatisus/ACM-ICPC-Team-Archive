#include<bits/stdc++.h>

const int N = 100010;
typedef std::pair <int, int> pii;
typedef std::pair <int, pii> piii;
typedef long long ll;

int fa[N], edge[N];
bool flag[N];
ll sz[N];
std::vector <int> e[N];
int x[N];
piii p[N];

int find(int u){
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

void dfs(int u, int fa){
    for (auto v : e[u]){
        if (v == -1 || v == fa) continue;
        if (flag[u]){
            flag[v] = true;
        }
        dfs(v, u);
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &x[i]);
    }
    for (int i = 0; i < m; ++ i){
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        p[i] = {w, {a, b}};
    }
    std::sort(p, p + m);
    for (int i = 1; i <= n; ++ i){
        fa[i] = i;
        sz[i] = x[i];
        edge[i] = -1;
    }
    for (int i = 0; i < m; ++ i){
        int u = p[i].second.first, v = p[i].second.second;
        u = find(u), v = find(v);
        if (u == v){
            e[i].push_back(edge[u]);
            edge[u] = i;
            if (sz[u] >= p[i].first){
                flag[i] = true;
            }
        }
        else{
            sz[u] += sz[v];
            fa[v] = u;
            e[i].push_back(edge[u]);
            e[i].push_back(edge[v]);
            edge[u] = i;
            if (sz[u] >= p[i].first){
                flag[i] = true;
            }
        }
    }
    dfs(m - 1, -1);
    int cnt = 0;
    for (int i = 0; i < m; ++ i){
        cnt += flag[i];
    }
    printf("%d\n", m - cnt);
    return 0;
}
