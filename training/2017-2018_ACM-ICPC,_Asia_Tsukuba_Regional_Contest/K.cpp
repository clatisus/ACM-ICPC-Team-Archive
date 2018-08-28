#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

int n, m, rt, f[max_N], ans;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

std::vector<int> vec[max_N], vt[max_N], kp;

bool key[max_N], vis[max_N];

int build(int u, int p) {
    std::vector<int> ch;
    for (auto v : vec[u]) {
        if (v == p) continue;
        int w = build(v, u);
        if (w) ch.push_back(w);
    }
    if (ch.size() >= 2) key[u] = true;
    if (key[u]) {
        kp.push_back(u);
        for (auto v : ch) {
            vt[u].push_back(v);
            vt[v].push_back(u);
        }
        return u;
    }
    return ch.empty() ? 0 : ch[0];
}

void dfs(int u, int s, int L) {
    int cnt = 0;
    for (auto v : vt[u]) {
        if (v == s ) ++cnt;
        if (v > s) continue;
        if (!vis[v]) {
            vis[v] = true;
            dfs(v, s, L + 1);
            vis[v] = false;
        }
    }
    if (cnt > 1 || (cnt == 1 && L > 2)) ++ans;
}

int main() {
    scanf("%d%d", &n, &m);
    if (n - 1 == m) return puts("0"), 0;
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        int x = find(u), y = find(v);
        if (x == y) {
            key[u] = key[v] = true;
            vt[u].push_back(v);
            vt[v].push_back(u);
        } else {
            vec[u].push_back(v);
            vec[v].push_back(u);
            f[x] = y;
        }
    }
    rt = build(1, 0);
    for (auto s : kp) {
        for (auto u : kp) vis[u] = false;
        vis[s] = true;
        dfs(s, s, 1);
    }
    printf("%d\n", ans / 2);
    return 0;
}
