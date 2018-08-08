#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long

int n, m;
std::vector<std::pair<int, int> > vec[MAXN];
std::vector<int> ans;
ll dis[MAXN];
int vis[MAXN];
bool flag;

void dijkstra(int s) {
    std::priority_queue<std::pair<ll, int> > pq;
    memset(dis + 1, 0x3f, n * sizeof(ll));
    memset(vis + 1, 0, n * sizeof(int));
    dis[s] = 0, pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto p : vec[u]) {
            int v = p.first, w = p.second;
            auto tmp = dis[u] + w;
            if (dis[v] > tmp) {
                dis[v] = tmp;
                pq.push({-dis[v], v});
            }
        }
    }
}

void dfs(int u) {
    vis[u] = 1;
    if (u == 2) {
        flag = true;
        ans.push_back(u);
        return;
    }
    for (auto p : vec[u]) {
        int v = p.first, w = p.second;
        if (dis[u] == dis[v] + w) continue;
        if (vis[v]) continue;
        dfs(v);
        if (flag) {
            ans.push_back(u);
            return;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        ++ a; ++ b;
        vec[a].push_back({b, d});
        vec[b].push_back({a, d});
    }
    dijkstra(2);
    if (!vis[1]) {
        puts("impossible");
        return 0;
    }
    memset(vis, 0, sizeof(vis));
    dfs(1);
    if (!flag) {
        puts("impossible");
        return 0;
    }
    int sz = ans.size();
    printf("%d ", sz);
    std::reverse(ans.begin(), ans.end());
    for (int i = 0; i < sz; ++i) {
        printf("%d%c", ans[i] - 1, " \n"[i == sz - 1]);
    }
    return 0;
}
