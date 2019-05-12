#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int inf = 0x3f3f3f3f;

int n, m, c[max_N], p[max_N], up[max_N], down[max_N];

std::pair<int, int> dp[max_N];

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)

void updt(int u) {
    dp[u] = {c[u] ? 0 : inf, u};
    std::vector<int> ch =  {ls(u), rs(u)};
    for (auto v : ch) {
        if (v > n) break;
        auto tmp = dp[v];
        tmp.first += down[v] ? -1 : 1;
        dp[u] = std::min(dp[u], tmp);
    }
}

void modify(int u, int v, int p) {
    while (u != p) {
        if (up[u]) --up[u];
        else ++down[u];
        updt(u);
        u >>= 1;
    }
    assert(c[v]);
    --c[v];
    while (v != p) {
        if (down[v]) --down[v];
        else ++up[v];
        updt(v);
        v >>= 1;
    }
    while (p) {
        updt(p);
        p >>= 1;
    }
}

int query(int u) {
    int ans = inf, p = 0, tmp = 0;
    for (int v = u; v; v >>= 1) {
        int ttmp = tmp + dp[v].first;
        if (ttmp < ans) {
            ans = ttmp;
            p = v;
        }
        tmp += up[v] ? -1 : 1;
    }
    modify(u, dp[p].second, p);
    return ans;
}

int main() {
    freopen("mole.in", "r", stdin);
    freopen("mole.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", p + i);
    }
    for (int i = n; i; --i) updt(i);
    int ans = 0;
    for (int i = 1; i <= m; ++i) {
        ans += query(p[i]);
        printf("%d%c", ans, " \n"[i == m]);
    }
}