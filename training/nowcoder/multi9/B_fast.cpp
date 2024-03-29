#include <bits/stdc++.h>
 
const int max_N = 12;
const int max_S = (1 << max_N);
const int max_M = 5000 + 21;
 
const int mod = (int) 1e9 + 7;
 
int n, m, f[max_N][max_S], g[max_N][max_S], _f[max_N][max_S], _g[max_N][max_S], bit[max_S];
 
int u[max_M], v[max_M], w[max_M], e[max_N][max_N], ans;
 
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", u + i, v + i, w + i);
        --u[i], --v[i];
        ++e[u[i]][v[i]], ++e[v[i]][u[i]];
    }
    for (int i = 0; i < n; ++i) _g[i][0] = 1;
    int maxs = (1 << n);
    for (int s = 0; s < maxs; ++s) {
        if (s) bit[s] = bit[s - (s & -s)] + 1;
        for (int u = 0; u < n; ++u) {
            if ((s >> u) & 1) continue;
            f[u][s] = _f[u][s], g[u][s] = _g[u][s];
            int lbt = s & -s, ss = s ^ lbt;
            if (ss) {
                for (int ns = (ss - 1) & ss; ; (--ns) &= ss) {
                    g[u][s] = (g[u][s] + 1ll * _g[u][ns | lbt] * g[u][ss ^ ns]) % mod;
                    f[u][s] = (f[u][s] + 1ll * _f[u][ns | lbt] * g[u][ss ^ ns]) % mod;
                    f[u][s] = (f[u][s] + 1ll * _g[u][ns | lbt] * f[u][ss ^ ns]) % mod;
                    if (!ns) break;
                }
            }
            for (int v = 0, sz; v < n; ++v) {
                if (u == v || ((s >> v) & 1)) continue;
                if (!(sz = e[u][v])) continue;
                _g[v][s | (1 << u)] = (_g[v][s | (1 << u)] + 1ll * sz * g[u][s]) % mod;
                int tmp = (f[u][s] + 1ll * (bit[s] + 1) * g[u][s]) % mod;
                _f[v][s | (1 << u)] = (_f[v][s | (1 << u)] + 1ll * sz * tmp) % mod;
            }
        }
    }
    for (int i = 1, tmp; i <= m; ++i) {
        if (u[i] == v[i]) continue;
        int s = (maxs - 1) ^ (1 << u[i]) ^ (1 << v[i]);
        for (int ns = s; ; (--ns) &= s) {
            tmp = (1ll * (bit[ns] + 1) * g[u[i]][ns] + f[u[i]][ns]) % mod;
            tmp = 1ll * tmp * g[v[i]][s ^ ns] % mod;
            ans = (ans + 1ll * w[i] * tmp) % mod;
 
            tmp = (1ll * (bit[s ^ ns] + 1) * g[v[i]][s ^ ns] + f[v[i]][s ^ ns]) % mod;
            tmp = 1ll * tmp * g[u[i]][ns] % mod;
            ans = (ans + 1ll * w[i] * tmp) % mod;
            if (!ns) break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
