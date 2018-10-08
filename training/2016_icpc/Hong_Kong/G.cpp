#include <bits/stdc++.h>

inline int read(int &x) {
    scanf("%d", &x);
}

using LL = long long;

const int max_N = (int) 1e5 + 21;

int n, m, a[max_N], siz[max_N], ch[max_N][2], st[max_N], top;

LL f[max_N], g[max_N], sum[max_N];

void solve(int u, int p) {
    if (!u) return;
    solve(ch[u][0], u);
    solve(ch[u][1], u);

    siz[u] = siz[ch[u][0]] + 1 + siz[ch[u][1]];
    sum[u] = sum[ch[u][0]] + a[u] + sum[ch[u][1]];

    LL rem = 1ll * (a[u] - a[p]) * siz[u] - g[ch[u][0]] - g[ch[u][1]];
    f[u] = f[ch[u][0]] + f[ch[u][1]] + std::max(0ll, (LL) std::ceil(1. * rem / m));
    g[u] = f[u] * m - (sum[u] - 1ll * a[p] * siz[u]);
}

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        while (top && a[st[top]] >= a[i]) {
            ch[i][0] = st[top--];
        }
        if (top) ch[st[top]][1] = i;
        st[++top] = i;
    }
    solve(st[1], 0);
    printf("%lld\n", f[st[1]]);
    return 0;
}

