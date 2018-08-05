#include <bits/stdc++.h>

const int max_N = 15;
const int max_S = 1 << max_N;

using ll = long long;

int n, maxs, a[max_N][max_N];

ll f[max_N][max_S];

std::vector<int> bit[max_S];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 1; j < n - i; ++j) {
            scanf("%d", a[i] + i + j);
            a[i + j][i] = a[i][i + j];
        }
    }
    maxs = (1 << n);
    for (int i = 0; i < n; ++i) bit[1 << i] = {i};
    for (int s = 1; s < maxs; ++s) {
        int lbt = s & -s;
        if (lbt == s) continue;
        bit[s] = bit[s ^ lbt];
        bit[s].push_back(bit[lbt][0]);
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i < n; ++i) f[i][1 << i] = 0;
    for (int s = 1; s < maxs; ++s) {
        if (bit[s].size() == 1) continue;
        for (auto u : bit[s]) {
            int rs = s ^ (1 << u);
            int ss = rs;
            do {
                for (auto v : bit[ss]) {
                    int sz = bit[ss].size();
                    ll tmp = 1ll * a[u][v] * sz * (n - sz);
                    tmp += f[u][s ^ ss] + f[v][ss];
                    f[u][s] = std::min(f[u][s], tmp);
                }
            } while ((--ss) &= rs);
        }
    }
    ll ans = 0x3f3f3f3f3f3f3f3fll;
    for (int i = 0; i < n; ++i) {
        ans = std::min(ans, f[i][maxs - 1]);
    }
    printf("%lld\n", ans);
    return 0;
}
