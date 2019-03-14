//
// Created by zzh on 2019/3/12.
//

#include <bits/stdc++.h>

using LL = long long;

const int max_N = 100 + 21;

int n, a[max_N][max_N << 1], map[max_N][max_N];

struct hash {
    bool eql[max_N][max_N];

    LL pw[max_N << 1], _pw[max_N << 1], f[max_N][max_N][max_N], tmp[max_N << 1];

    LL qpow(LL x, LL k, LL mod) {
        LL ret = 1;
        while (k) {
            if (k & 1) {
                ret = ret * x % mod;
            }
            x = x * x % mod;
            k >>= 1;
        }
        return ret;
    }

    void solve(LL mod, LL base) {
        LL _base = qpow(base, mod - 2, mod);
        pw[0] = _pw[0] = 1;
        for (int i = 1; i < (max_N << 1); ++i) {
            pw[i] = pw[i - 1] * base % mod;
            _pw[i] = _pw[i - 1] * _base % mod;
        }
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (!map[u][v]) continue;
                f[0][u][v] = *a[v];
            }
        }
        for (int k = 1; k <= n; ++k) {
            for (int v = 1; v <= n; ++v) {
                tmp[0] = 0;
                for (int i = 1; i <= *a[v] * 2; ++i) {
                    int u = a[v][i];
                    tmp[i] = (tmp[i - 1] + f[k - 1][v][u] * pw[i]);
                }
                for (int i = 1; i <= *a[v]; ++i) {
                    int u = a[v][i];
                    LL ret = (tmp[i + *a[v]] - tmp[i] + mod) % mod;
                    ret = (ret * _pw[i] + *a[v]) % mod;
                    f[k][u][v] = ret;
                }
            }
        }
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                eql[u][v] = false;
                if (*a[u] != *a[v]) continue;
                for (int i = 0; i < n; ++i) {
                    bool flag = true;
                    for (int j = 1; j <= *a[u]; ++j) {
                        if (f[n][u][a[u][j]] != f[n][v][a[v][j + i]]) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        eql[u][v] = true;
                        break;
                    }
                }
                if (eql[u][v]) continue;
                for (int i = 0; i < n; ++i) {
                    bool flag = true;
                    for (int j = 1; j <= *a[u]; ++j) {
                        if (f[n][u][a[u][i + j]] != f[n][v][a[v][j]]) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        eql[u][v] = true;
                        break;
                    }
                }
            }
        }
    }
} h[2];

int f[max_N], Q[max_N], tot;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

std::set<int> set[max_N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a[i]);
        for (int j = 1; j <= *a[i]; ++j) {
            scanf("%d", a[i] + j);
            a[i][*a[i] + j] = a[i][j];
            map[i][a[i][j]] = 1;
        }
    }
    h[0].solve(1000000007, 998244353);
    h[1].solve(1000000009, 1000000007);
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
    }
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (h[0].eql[u][v] && h[1].eql[u][v]) {
                f[find(u)] = find(v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        set[find(i)].insert(i);
    }
    for (int i = 1; i <= n; ++i) {
        if (find(i) == i && set[i].size() > 1) {
            Q[++tot] = i;
        }
    }
    if (!tot) {
        puts("none");
        return 0;
    }
    std::sort(Q + 1, Q + 1 + tot, [&] (int x, int y) {
        return *set[x].begin() < *set[y].begin();
    });
    for (int i = 1; i <= tot; ++i) {
        for (auto &x : set[Q[i]]) {
            printf("%d ", x);
        }
        puts("");
    }
}