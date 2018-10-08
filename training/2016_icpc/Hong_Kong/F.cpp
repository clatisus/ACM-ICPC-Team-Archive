#include <bits/stdc++.h>

const int max_N = (int) 2e5 +21;
const int log_N = 20;
const int mod = (int) 1e9 + 7;

#define ext(x) ((x) > n)

int n, K, tot, ret;

int dp[max_N][log_N], pre[max_N][log_N][7], suf[log_N][7];

std::vector<int> vec[max_N];

int p[max_N], sz[max_N], mx[max_N];

bool vis[max_N];

inline int find(int u) {
    static int Q[max_N], tot;
    p[Q[tot = 1] = u] = 0;
    for (int i = 1; i <= tot; ++i) {
        u = Q[i];
        sz[u] = 1, mx[u] = 0;
        for (auto v : vec[u]) {
            if (ext(v)) continue;
            if (vis[v] || p[u] == v) continue;
            p[Q[++tot] = v] = u;
        }
    }
    for (int i = tot; i; --i) {
        u = Q[i];
        mx[u] = std::max(mx[u], tot - sz[u]);
        if (mx[u] * 2 <= tot) return u;
        sz[p[u]] += sz[u];
        mx[p[u]] = std::max(mx[p[u]], sz[u]);
    }
    return 0;
}

int tmp[max_N][log_N][7];

void dfs(int u, int p) {
    memset(tmp[u], 0, sizeof(tmp[u]));
    for (int j = 0; j < log_N; ++j) tmp[u][j][0] = 1;
    for (auto v : vec[u]) {
        if (v == p || vis[v]) continue;
        if (!ext(v)) dfs(v, u);
        for (int j = 0; j < log_N; ++j) {
            for (int k = K; k; --k) {
                tmp[u][j][k] = (tmp[u][j][k] + 1ll * tmp[u][j][k - 1] * dp[v][j]) % mod;
            }
        }
    }
    dp[u][0] = 1;
    for (int j = 1; j < log_N; ++j) {
        dp[u][j] = tmp[u][j - 1][K];
    }
}

void solve(int u) {
    u = find(u);

    memset(pre[0], 0, sizeof(pre[0]));
    for (int j = 0; j < log_N; ++j) pre[0][j][0] = 1;
    int i = 0;
    for (auto v : vec[u]) {
        if (vis[v]) continue;
        ++i;
        if (!ext(v)) dfs(v, u);
        for (int j = 0; j < log_N; ++j) {
            for (int k = K; k; --k) {
                pre[i][j][k] = (pre[i - 1][j][k] + 1ll * pre[i - 1][j][k - 1] * dp[v][j]) % mod;
            }
            pre[i][j][0] = 1;
        }
    }
    dp[u][0] = 1;
    for (int j = 1; j < log_N; ++j) {
        dp[u][j] = pre[i][j - 1][K];
    }

    std::reverse(vec[u].begin(), vec[u].end());

    memset(suf, 0, sizeof(suf));
    for (int j = 0; j < log_N; ++j) suf[j][0] = 1;
    for (auto v : vec[u]) {
        if (vis[v]) continue;
        --i;
        if (!ext(v)) {
            int w = ++tot;
            vec[v].push_back(w);
            dp[w][0] = 1;
            for (int j = 1; j < log_N; ++j) {
                dp[w][j] = 0;
                for (int k = 0; k <= K; ++k) {
                    dp[w][j] = (dp[w][j] + 1ll * pre[i][j - 1][k] * suf[j - 1][K - k]) % mod;
                }
            }
        }
        for (int j = 0; j < log_N; ++j) {
            for (int k = K; k; --k) {
                suf[j][k] = (suf[j][k] + 1ll * suf[j][k - 1] * dp[v][j]) % mod;
            }
        }
    }

    vis[u] = true;
    for (auto v : vec[u]) {
        if (ext(v) || vis[v]) continue;
        solve(v);
    }
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    tot = n;

    solve(1);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < log_N; ++j) {
            ret = (ret + dp[i][j]) % mod;
        }
    printf("%d\n", ret);

    return 0;
}
