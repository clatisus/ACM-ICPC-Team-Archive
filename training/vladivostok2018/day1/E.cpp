#include <bits/stdc++.h>

using ll = long long;

const int max_N = 1000 + 21;
const int mod = 1234567891;

int T, n, m, f[max_N], siz[max_N];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    f[a] = b;
    siz[b] += siz[a];
}

int C[max_N][max_N], fac[max_N];

void init() {
    fac[0] = 1;
    for (int i = 1; i < max_N; ++i) {
        fac[i] = int(1ll * fac[i - 1] * i % mod);
    }
    C[0][0] = 1;
    for (int n = 1; n < max_N; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int m = 1; m < n; ++m) {
            C[n][m] = (1ll * C[n - 1][m] + C[n - 1][m - 1]) % mod;
        }
    }
}

int dp[2][max_N], *pre, *cur;

void trans(int s) {
    std::swap(pre, cur);
    memset(cur, 0, sizeof(int) * (n + 1));
    for (int k = 0; k <= s; ++k) {
        ll tmp = 1ll * C[s][k] * C[s][k] % mod;
        tmp = tmp * fac[k] % mod;
        for (int i = 0; i + k <= n; ++i) {
            cur[i + k] = (cur[i + k] + tmp * pre[i]) % mod;
        }
    }
}

void testCase() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        siz[i] = 1;
    }
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        merge(u, v);
    }
    cur = dp[0];
    pre = dp[1];
    memset(dp[0] + 1, 0, sizeof(int) * n);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (f[i] == i) {
            trans(siz[i]);
        }
    }
    int ans = 0;
    for (int k = 0; k <= n; ++k) {
        ll tmp = 1ll * cur[k] * fac[n - k] % mod;
        if (k & 1) {
            ans = (ans - tmp + mod) % mod;
        } else {
            ans = (ans + tmp) % mod;
        }
    }
    assert(ans >= 0);
    printf("%d\n", ans);
}

int main() {
    init();
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}

