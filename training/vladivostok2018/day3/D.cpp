#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int sqrt_N = 666;

int n, q, val[max_N];

int cnt[sqrt_N], vis[max_N];

bool in[max_N];

using pair = std::pair<int, int>;
using VP = std::vector<pair>;

VP vec[max_N];

int dfn[max_N], _cnt;

int dep[max_N], p[max_N];

void dfs(int x) {
    dfn[x] = ++_cnt;
    for (auto &e : vec[x]) {
        int y = e.first;
        int w = e.second;
        if (y == p[x]) {
            continue;
        }
        p[y] = x;
        dep[y] = dep[x] + 1;
        val[y] = std::min(w, 100000);
        dfs(y);
    }
}

int Q[max_N], u[max_N], v[max_N], ans[max_N];

void Xor(int x) {
    if (!in[x]) {
        in[x] = true;
        if (++vis[val[x]] > 1) return;
        ++cnt[val[x] / sqrt_N];
    } else {
        in[x] = false;
        if (--vis[val[x]] > 0) return;
        --cnt[val[x] / sqrt_N];
    }
}

int query() {
    int i = 0;
    for (; cnt[i] == sqrt_N; ++i);
    i *= sqrt_N;
    for (; vis[i]; ++i);
    return i;
}

void xor_path(int u, int v) {
    if (dep[u] > dep[v]) {
        std::swap(u, v);
    }
    while (dep[u] != dep[v]) {
        Xor(v);
        v = p[v];
    }
    while (u != v) {
        Xor(u), u = p[u];
        Xor(v), v = p[v];
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        vec[u].push_back({v, w});
        vec[v].push_back({u, w});
    }
    dfs(1);
    for (int i = 1; i <= q; ++i) {
        scanf("%d%d", u + i, v + i);
        if (dfn[u[i]] > dfn[v[i]]) {
            std::swap(u[i], v[i]);
        }
        Q[i] = i;
    }
    std::sort(Q + 1, Q + 1 + q, [&](int x, int y) { return (dfn[u[x]] / sqrt_N) == (dfn[u[y]] / sqrt_N) ? dfn[v[x]] > dfn[v[y]]: dfn[u[x]] < dfn[u[y]]; });
    xor_path(u[Q[1]], v[Q[1]]);
    ans[Q[1]] = query();
    for (int i = 2; i <= q; ++i) {
        xor_path(u[Q[i]], u[Q[i - 1]]);
        xor_path(v[Q[i]], v[Q[i - 1]]);
        ans[Q[i]] = query();
    }
    for (int i = 1; i <= q; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
/*
7 6
2 1 1
3 1 2
1 4 0
4 5 1
5 6 3
5 7 4
1 3
4 1
2 4
2 5
3 5
3 7
*/

