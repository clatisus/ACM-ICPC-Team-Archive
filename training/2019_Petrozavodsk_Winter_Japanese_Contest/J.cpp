//
// Created by zzh on 2019/3/1.
//

#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

int n, m, c[max_N], dfn[max_N], vp[max_N], cnt;

int anc[20][max_N], dep[max_N];

std::vector<int> vec[max_N];

void dfs(int u) {
    dfn[u] = ++cnt;
    vp[cnt] = u;
    for (int i =1; i < 20; ++i) {
        anc[i][u] = anc[i - 1][anc[i - 1][u]];
    }
    for (auto &v : vec[u]) {
        if (dfn[v]) continue;
        dep[v] = dep[u] + 1;
        anc[0][v] = u;
        dfs(v);
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) {
        std::swap(u, v);
    }
    int k = dep[v] - dep[u];
    for (int i = 0; k; ++i, k >>= 1) {
        if (k & 1) {
            v = anc[i][v];
        }
    }
    if (u == v) return u;
    for (int i = 19; ~i; --i) {
        if (anc[i][u] == anc[i][v]) continue;
        u = anc[i][u], v = anc[i][v];
    }
    return anc[0][u];
}

inline int dis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

std::set<int> set[max_N];

long long ret[max_N];

void modify(int c, int x, int tp) {
    if (tp == 1) set[c].insert(x);
    auto it = set[c].find(x);
    int prev = -1, next = -1;
    if (it != set[c].begin()) {
        --it;
        prev = *it;
        ++it;
    }
    ++it;
    if (it != set[c].end()) {
        next = *it;
    }
    --it;
    if (prev != -1) {
        ret[c] += dis(vp[prev], vp[x]) * tp;
    }
    if (next != -1) {
        ret[c] += dis(vp[x], vp[next]) * tp;
    }
    if (prev != -1 && next != -1) {
        ret[c] -= dis(vp[prev], vp[next]) * tp;
    }
    if (tp == -1) set[c].erase(x);
}

inline long long query(int c) {
    if (set[c].empty())
        return -1;
    /*for (auto &x : set[c]) {
        printf("%d ", x);
    }
    puts("");*/
    long long ans = ret[c];
    if (set[c].size() >= 2) {
        auto fir = set[c].begin();
        auto las = --set[c].end();
        ans += dis(vp[*fir], vp[*las]);
    }
    return ans >> 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
        modify(c[i], dfn[i], 1);
    }
    scanf("%d", &m);
    for (int i = 1, u, v; i <= m; ++i) {
        char tmp[5];
        scanf("%s%d", tmp, &u);
        if (*tmp == 'U') {
            scanf("%d", &v);
            if (c[u] != v) {
                modify(c[u], dfn[u], -1);
                modify(c[u] = v, dfn[u], 1);
            }
        } else {
            printf("%lld\n", query(u));
        }
    }
}