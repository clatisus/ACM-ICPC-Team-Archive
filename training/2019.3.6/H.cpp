//
// Created by zzh on 2019/3/6.
//

#include <bits/stdc++.h>

using LL = long long;

const int max_N = 121;

int n, a[max_N], b[max_N], p[max_N], vis[max_N], tmp[max_N];

namespace ChuLiu {
    const int max_M = max_N * max_N;

    LL val[max_M], tag[max_M];

    int n, m, root, u[max_M], v[max_M], ls[max_M], rs[max_M];

    int st[max_N], top, rt[max_N];

    inline void down(int x) {
        if (tag[x]) {
            val[x] += tag[x];
            tag[ls[x]] += tag[x];
            tag[rs[x]] += tag[x];
            tag[x] = 0;
        }
    }

    int merge(int x, int y) {
        down(x), down(y);
        if (!x || !y) {
            return x + y;
        }
        if (val[x] > val[y]) {
            std::swap(x, y);
        }
        rs[x] = merge(rs[x], y);
        std::swap(ls[x], rs[x]);
        return x;
    }

    struct dsu {
        int f[max_N];

        int find(int x) {
            return x == f[x] ? x : f[x] = find(f[x]);
        }

        void init(int n) {
            for (int i = 1; i <= n; ++i) {
                f[i] = i;
            }
        }

        inline void merge(int x, int y) {
            f[find(x)] = find(y);
        }

        inline bool check(int x, int y) {
            return find(x) == find(y);
        }
    } F[2];

    inline void addEdge(int x, int y, int w) {
        ++m;
        u[m] = x, v[m] = y, val[m] = w;
    }

    LL solve() {
        F[0].init(n);
        F[1].init(n);
        for (int i = 1; i <= n; ++i) {
            rt[i] = 0;
        }
        for (int i = 1; i <= m; ++i) {
            tag[i] = ls[i] = rs[i] = 0;
            rt[v[i]] = merge(rt[v[i]], i);
        }
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (F[1].f[i] != i) continue;
            st[top = 1] = i;
            while (!F[0].check(st[top], root)) {
                int x = st[top], y;
                LL w;
                do {
                    y = F[1].find(u[rt[x]]);
                    w = val[rt[x]];
                    rt[x] = merge(ls[rt[x]], rs[rt[x]]);
                } while (x == y);
                ans += w;
                tag[rt[x]] -= w;
                if (F[0].check(x, y)) {
                    while (st[top] != y) {
                        x = st[top--];
                        rt[y] = merge(rt[x], rt[y]);
                        F[1].merge(x, y);
                    }
                } else {
                    F[0].merge(x, y);
                    st[++top] = y;
                }
            }
        }
        return ans;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", b + i);
    }
    ChuLiu::root = ChuLiu::n = n + 1;
    ChuLiu::m = 0;
    for (int i = 1; i <= n; ++i) {
        ChuLiu::addEdge(ChuLiu::root, i, a[i] ^ b[i]);
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            ChuLiu::addEdge(j, i, a[i] ^ b[j]);
        }
    }
    LL ans = ChuLiu::solve();
    printf("%lld\n", ans);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (vis[j]) continue;
            vis[j] = 1;
            p[i] = j;
            tmp[j] = INT_MAX;
            for (int k = 1; k <= i; ++k) {
                tmp[j] = std::min(tmp[j], a[j] ^ b[p[k]]);
            }
            ChuLiu::m = 0;
            for (int k = 1; k <= n; ++k) {
                if (vis[k]) {
                    ChuLiu::addEdge(ChuLiu::root, k, tmp[k]);
                    continue;
                }
                ChuLiu::addEdge(ChuLiu::root, k, a[k] ^ b[k]);
                for (int l = 1; l <= n; ++l) {
                    if (l == k) continue;
                    ChuLiu::addEdge(l, k, a[k] ^ b[l]);
                }
            }
            LL cur = ChuLiu::solve();
            if (ans == cur) {
                break;
            }
            vis[j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", p[i], " \n"[i == n]);
    }
}
