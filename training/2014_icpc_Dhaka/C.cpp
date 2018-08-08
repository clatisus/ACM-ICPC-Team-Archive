#include <bits/stdc++.h>

const int max_N = 10000 + 21;
const int mod = 21092013;

int T, n, L[max_N], R[max_N], val[max_N], ans[55];

std::vector<int> vec[max_N], Div[55];

int f[max_N], g[max_N];

void treeDP(int u, int p) {
    f[u] = g[u] = val[u];
    for (auto v : vec[u]) {
        if (v == p) continue;
        treeDP(v, u);
        f[u] = (f[u] + f[v]) % mod;
        f[u] = (f[u] + 1ll * g[u] * g[v]) % mod;
        g[u] = (g[u] + 1ll * val[u] * g[v]) % mod;
    }
}

void testCase() {
    static int caseID = 0;
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", L + i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", R + i);
    }
    for (int g = 1; g <= 50; ++g) {
        for (int i = 1; i <= n; ++i) {
            val[i] = (R[i] / g) - ((L[i] - 1) / g);
        }
        treeDP(1, 0);
        ans[g] = f[1];
    }
    for (int g = 50; g; --g) {
        for (auto v : Div[g]) {
            ans[v] = (ans[v] - ans[g] + mod) % mod;
        }
    }
    printf("Case %d:\n", ++caseID);
    for (int g = 1; g <= 50; ++g) {
        printf("%d: %d\n", g, ans[g]);
    }
    for (int i = 1; i <= n; ++i) {
        std::vector<int>().swap(vec[i]);
    }
}

int main() {
    for (int g = 1; g <= 50; ++g) {
        for (int i = g + g; i <= 50; i += g) {
            Div[i].push_back(g);
        }
    }
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
