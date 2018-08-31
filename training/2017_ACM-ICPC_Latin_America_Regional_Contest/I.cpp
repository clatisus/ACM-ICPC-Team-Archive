#include <bits/stdc++.h>

const int max_N = (int) 2e5 + 21;

int n, m, q, f[max_N], u[max_N], v[max_N], w[max_N], Q[max_N], ret[max_N], ans;

bool mst[max_N];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

std::unordered_map<int, int> edgeID[max_N];

std::vector<int> qy[max_N];

std::vector<std::pair<int, int>> vec[max_N];

int sz[max_N], mx[max_N], p[max_N], part[max_N], val[max_N], Time[max_N], T;

bool vis[max_N];

inline int getRT(int u) {
    static int Q[max_N], tot;
    Q[tot = 1] = u, p[u] = 0;
    for (int i = 1; i <= tot; ++i) {
        u = Q[i];
        sz[u] = 1, mx[u] = 0;
        for (auto pr : vec[u]) {
            int v = pr.first;
            if (vis[v] || v == p[u]) continue;
            p[Q[++tot] = v] = u;
        }
    }
    for (int i = tot; i; --i) {
        u = Q[i];
        mx[u] = std::max(mx[u], tot - sz[u]);
        if (mx[u] * 2 <= tot) return u;
        sz[p[u]] += sz[u];
        mx[p[u]] = std::max(mx[p[u]], sz[u]);
    }
    return 0;
}

int vp[max_N], cnt;

void dfs(int u, int rt) {
    part[u] = rt;
    vp[++cnt] = u;
    Time[u] = T;
    for (auto pr : vec[u]) {
        int v = pr.first;
        if (vis[v] || v == p[u]) continue;
        p[v] = u;
        val[v] = std::max(val[u], pr.second);
        dfs(v, rt);
    }
}

void solve(int u) {
    u = getRT(u);
    val[u] = 0;
    part[u] = u;
    vp[cnt = 1] = u;
    ++T;
    Time[u] = T;
    for (auto pr : vec[u]) {
        int v = pr.first;
        if (vis[v]) continue;
        p[v] = u;
        val[v] = pr.second;
        dfs(v, v);
    }
    for (int i = 1; i <= cnt; ++i) {
        int x = vp[i];
        for (auto y : qy[x]) {
            if (Time[y] != T || part[x] == part[y]) continue;
            int a = x, b = y;
            if (a > b) std::swap(a, b);
            ret[edgeID[a][b]] = std::max(val[x], val[y]);
        }
    }
    vis[u] = true;
    for (auto pr : vec[u]) {
        int v = pr.first;
        if (!vis[v]) solve(v);
    }
}

void testCase() {
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", u + i, v + i, w + i);
        if (u[i] > v[i]) std::swap(u[i], v[i]);
        edgeID[u[i]][v[i]] = i;
        mst[i] = false;
        Q[i] = i;
    }
    std::sort(Q + 1, Q + 1 + m, [&](int x, int y) { return w[x] < w[y]; });
    ans = 0;
    for (int i = 1; i <= m; ++i) {
        int x = find(u[Q[i]]), y = find(v[Q[i]]);
        if (x == y) {
            qy[u[Q[i]]].push_back(v[Q[i]]);
            qy[v[Q[i]]].push_back(u[Q[i]]);
        } else {
            f[x] = y;
            ans += w[Q[i]];
            mst[Q[i]] = true;
            vec[u[Q[i]]].push_back({v[Q[i]], w[Q[i]]});
            vec[v[Q[i]]].push_back({u[Q[i]], w[Q[i]]});
        }
    }
    solve(1);
    scanf("%d", &q);
    for (int i = 1, a, b; i <= q; ++i) {
        scanf("%d%d", &a, &b);
        if (a > b) std::swap(a, b);
        int id = edgeID[a][b];
        int res = ans;
        if (!mst[id]) res += w[id] - ret[id];
        printf("%d\n", res);
    }
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        std::vector<int>().swap(qy[i]);
        std::unordered_map<int, int>().swap(edgeID[i]);
        std::vector<std::pair<int, int>>().swap(vec[i]);
    }
}

int main() {
    while (~scanf("%d%d", &n, &m)) testCase();
    return 0;
}

