#include <bits/stdc++.h>

// virtual tree twice nodes
#define MAXN (1010)
#define ll long long

int n;
ll a[MAXN][MAXN];
ll b[MAXN][MAXN];
std::vector<std::pair<int, ll> > vec[MAXN];
ll sz[MAXN];
ll m;
double ans;
bool vis[MAXN];

void addedge(int u, int v, ll w) {
    vec[u].push_back({v, w});
    vec[v].push_back({u, w});
}

void build_tree() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            b[i][j] = a[1][i] + a[1][j] - a[i][j];
        }
    }
    int tot = n;
    for (int _ = 1; _ <= n - 2; ++_) {
        ll d = INT_MIN;
        int u, v;
        for (int i = 2; i <= tot; ++i) {
            if (vis[i]) continue;
            for (int j = i + 1; j <= tot; ++j) {
                if (vis[j]) continue;
                if (d < b[i][j]) {
                    d = b[u = i][v = j];
                }
            }
        }
        d /= 2;
        ++ tot;
        addedge(u, tot, a[1][u] - d);
        addedge(v, tot, a[1][v] - d);
        for (int i = 1; i < tot; ++i) {
            a[i][tot] = a[tot][i] = a[i][u] - (a[1][u] - d);
            b[i][tot] = b[tot][i] = a[1][i] + a[1][tot] - a[i][tot];
        }
        vis[u] = vis[v] = true;
    }
    addedge(1, tot, a[1][tot]);
}

void dfs1(int u, int fa) {
    for (auto p : vec[u]) {
        int v = p.first;
        if (v == fa) continue;
        ll w = p.second;
        dfs1(v, u);
        sz[u] += sz[v] + w;
    }
}

void dfs2(int u, int fa) {
    for (auto p : vec[u]) {
        int v = p.first;
        if (v == fa) continue;
        ll w = p.second;
        dfs2(v, u);
        ans += 1.0 * sz[v] * w * (m - sz[v]);
        ans += 1.0 * (m - 2 * sz[v]) * w * (w + 1) / 2;
        ans -= 1.0 * w * (w + 1) * (2 * w + 1) / 6;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            scanf("%lld", &a[i][j]);
            a[j][i] = a[i][j];
        }
    }
    build_tree();
    dfs1(1, 0);
    m = sz[1] + 1;
    dfs2(1, 0);
    printf("%.15f\n", ans * 2 / (m * (m - 1)));
    return 0;
}
