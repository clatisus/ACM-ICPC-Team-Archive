#include <bits/stdc++.h>

#define MAXN (100010)

int n, m, k;
std::vector<int> vec[2][MAXN];
std::vector<int> ore, coal;
int dis[3][MAXN];

void bfs(int t, std::vector<int> s, int *d) {
    memset(d, -1, (n + 1) * sizeof(int));
    std::queue<int> q;
    for (auto u : s) {
        d[u] = 0;
        q.push(u);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : vec[t][u]) {
            if (d[v] != -1) continue;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        ore.push_back(x);
    }
    for (int i = 0; i < k; ++i) {
        int x;
        scanf("%d", &x);
        coal.push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        int a;
        scanf("%d", &a);
        for (int j = 1; j <= a; ++j) {
            int b;
            scanf("%d", &b);
            vec[0][i].push_back(b);
            vec[1][b].push_back(i);
        }
    }
    bfs(0, std::vector<int>{1}, dis[0]);
    bfs(1, ore, dis[1]);
    bfs(1, coal, dis[2]);
    int ans = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        if (dis[0][i] == -1 || dis[1][i] == -1 || dis[2][i] == -1) continue;
        ans = std::min(ans, dis[0][i] + dis[1][i] + dis[2][i]);
    }
    if (ans == INT_MAX) {
        puts("impossible");
        return 0;
    }
    printf("%d\n", ans);
    return 0;
}

