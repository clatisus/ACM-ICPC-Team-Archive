#include <bits/stdc++.h>

using ll = long long;

const int max_N = (int) 1e5 + 21;

int T, n, m, F[max_N], last[max_N];

int dep[max_N], p[max_N], siz[max_N], max[max_N];

int head[max_N], dfn[max_N], cnt;

ll bit[max_N];

std::vector<int> vec[max_N];

void dfs1(int x) {
    siz[x] = 1, max[x] = 0;
    for (auto &y : vec[x]) {
        if (y == p[x]) continue;
        p[y] = x;
        dep[y] = dep[x] + 1;
        dfs1(y);
        if (siz[y] > siz[max[x]]) {
            max[x] = y;
        }
        siz[x] += siz[x];
    }
}

void dfs2(int x, int c) {
    head[x] = c;
    dfn[x] = ++cnt;
    if (max[x]) {
        dfs2(max[x], c);
    }
    for (auto & y : vec[x]) {
        if (dfn[y]) continue;
        dfs2(y, y);
    }
}

void add(int x, int y) {
    for (; x && x <= n; x += x&-x) bit[x] += y;
}

ll sum(int x) {
    ll res = 0;
    for (; x; x -= x&-x) res += bit[x];
    return res;
}

void testCase() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", F + i);
        last[i] = dfn[i] = bit[i] = 0;
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    cnt = 0;
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; ++i) {
        add(dfn[i], F[i]);
    }
    for (int i = 1; i <= m; ++i) {
        char opt[5];
        scanf("%s", opt);
        if (*opt == 'P') {
            int x;
            scanf("%d", &x);
            int delta = F[x] + i - last[x];
            add(dfn[x], -delta);
            F[x] = 0, last[x] = i;
        } else {
            int u, v;
            scanf("%d%d", &u, &v);
            ll Sum = 0, Siz = 0;
            while (head[u] != head[v]) {
                if (dep[head[u]] > dep[head[v]]) {
                    std::swap(u, v);
                }
                Sum += sum(dfn[v]) - sum(dfn[head[v]] - 1);
                Siz += dfn[v] - dfn[head[v]] + 1;
                v = p[head[v]];
            }
            if (dep[u] > dep[v]) {
                std::swap(u, v);
            }
            Sum += sum(dfn[v]) - sum(dfn[u] - 1);
            Siz += dfn[v] - dfn[u] + 1;
            ll ans = Sum + Siz * i;
            printf("%lld\n", ans);
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::vector<int>().swap(vec[i]);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}

