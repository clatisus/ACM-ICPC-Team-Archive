#include <bits/stdc++.h>

#define MAXN (510)
#define ll long long

int n, m;
ll dis[MAXN * MAXN];
bool vis[MAXN * MAXN];
int id[MAXN][MAXN], tot;
std::vector<std::pair<int, int> > vec[MAXN * MAXN];

bool dfs(int u, ll d) {
    vis[u] = true;
    dis[u] = d;
    for (auto p : vec[u]) {
        int v = p.first, w = p.second;
        if (vis[v]) {
            if (dis[v] != d + w) {
                return false;
            }
            continue;
        }
        if (!dfs(v, d + w)) return false;
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            id[i][j] = ++tot;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int k = id[i][j];
            int x, y;
            scanf("%d%d", &x, &y);
            int up = id[(i - 1 + n) % n][j];
            int le = id[i][(j - 1 + m) % m];
            vec[k].push_back({up, x});
            vec[up].push_back({k, -x});
            vec[k].push_back({le, -y});
            vec[le].push_back({k, y});
        }
    }
    for (int i = 1; i <= tot; ++i) {
        if (!vis[i]) {
            if (!dfs(i, 0)) {
                printf("No\n");
                return 0;
            }
        }
    }
    printf("Yes\n");
    return 0;
}

