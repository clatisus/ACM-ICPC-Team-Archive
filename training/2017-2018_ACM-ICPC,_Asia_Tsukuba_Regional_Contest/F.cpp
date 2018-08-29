#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long

int n, m;
struct edge {
    int u, v, w;
}e[MAXN];
std::vector<std::pair<int, int>> vec[2][MAXN];
std::vector<int> mat[MAXN];
int low[MAXN], dfn[MAXN], tot;
ll dis[2][MAXN];
bool canbad[MAXN];

void dijkstra(int type, ll *dis, bool *vis, int s) {
    std::priority_queue<std::pair<ll, int>> pq;
    memset(dis + 1, 0x3f, n * sizeof(ll));
    memset(vis + 1, false, n * sizeof(bool));
    dis[s] = 0;
    pq.push({dis[s], s});
    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &p : vec[type][u]) {
            int v = p.first, w = p.second;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({-dis[v], v});
            }
        }
    }
}

void dfs(int u, int p) {
    dfn[u] = low[u] = ++tot;
    for (auto &v : mat[u]) {
        if (v == p) continue;
        if (!dfn[v]) {
            dfs(v, u);
            low[u] = std::min(low[u], low[v]);
        } else {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        e[i] = {a, b, c};
        vec[0][a].push_back({b, c});
        vec[1][b].push_back({a, c});
    }
    dijkstra(0, dis[0], canbad, 1);
    dijkstra(1, dis[1], canbad, 2);
    ll origin = dis[0][2];

    memset(canbad + 1, false, m * sizeof(bool));
    for (int i = 1; i <= m; ++i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (dis[0][u] + w == dis[0][v] && dis[1][v] + w == dis[1][u]) {
            mat[u].push_back(v);
            mat[v].push_back(u);
            canbad[i] = true;
        }
    }
    dfs(1, 0);
    for (int i = 1; i <= m; ++i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        ll now = dis[0][v] + w + dis[1][u];
        if (!canbad[i] || (canbad[i] && low[v] <= dfn[u])) {
            now = std::min(now, origin);
        }
        if (now < origin) puts("HAPPY");
        else if (now == origin) puts("SOSO");
        else puts("SAD");
    }
    return 0;
}
