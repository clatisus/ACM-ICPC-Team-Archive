#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int mod = (int) 1e6 + 3;

int T, n, k, w[max_N], siz[max_N], max[max_N], rt;

bool vis[max_N];

std::vector<int> vec[max_N];

void find_rt(int x, int p, int sum) {
    siz[x] = 1;
    max[x] = 0;
    for (auto &y : vec[x]) {
        if (vis[y] || y == p) continue;
        find_rt(y, x, sum);
        siz[x] += siz[y];
        max[x] = std::max(max[x], siz[y]);
    }
    max[x] = std::max(max[x], sum - siz[x]);
    if (max[x] < max[rt]) {
        rt = x;
    }
}

int path[mod], inv[mod];

std::pair<int, int> ans;

void dfs1(int x, int p, int dis) {
    int need = int(1ll * k * inv[dis] % mod);
    if (path[need]) {
        std::pair<int, int> cur = {path[need], x};
        if (cur.first > cur.second) {
            std::swap(cur.first, cur.second);
        }
        if (ans.first == -1 || ans > cur) {
            ans = cur;
        }
    }
    siz[x] = 1;
    for (auto &y : vec[x]) {
        if (vis[y] || y == p) continue;
        dfs1(y, x, int(1ll * dis * w[y] % mod));
        siz[x] += siz[y];
    }
}

void dfs2(int x, int p, int dis) {
    if (!path[dis] || path[dis] > x) {
        path[dis] = x;
    }
    for (auto &y : vec[x]) {
        if (vis[y] || y == p) continue;
        dfs2(y, x, int(1ll * dis * w[y] % mod));
    }
}

void dfs3(int x, int p, int dis) {
    path[dis] = 0;
    for (auto &y : vec[x]) {
        if (vis[y] || y == p) continue;
        dfs3(y, x, int(1ll * dis * w[y] % mod));
    }
}

void solve(int x) {
    vis[x] = true;
    path[w[x]] = x;
    for (auto &y : vec[x]) {
        if (vis[y]) continue;
        dfs1(y, x, w[y]);
        dfs2(y, x, int(1ll * w[x] * w[y] % mod));
    }
    path[w[x]] = 0;
    for (auto &y : vec[x]) {
        if (vis[y]) continue;
        dfs3(y, x, int(1ll * w[x] * w[y] % mod));
    }
    for (auto &y : vec[x]) {
        if (vis[y]) continue;
        rt = 0;
        find_rt(y, x, siz[y]);
        solve(rt);
    }
}

int main() {
    inv[1] = 1;
    for (int i = 2; i < mod; ++i) {
        inv[i] = int(1ll * (mod / i) * inv[mod % i] % mod);
        if (inv[i]) inv[i] = mod - inv[i];
    }
    while (~scanf("%d%d", &n, &k)) {
        for (int i = 1; i <= n; ++i) {
            vis[i] = false;
            scanf("%d", w + i);
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            vec[u].push_back(v);
            vec[v].push_back(u);
        }
        ans = {-1, -1};
        max[rt = 0] = n + 1;
        find_rt(1, 0, n);
        solve(rt);
        if (ans.first == -1) {
            puts("No solution");
        } else {
            if (ans.first > ans.second) {
                std::swap(ans.first, ans.second);
            }
            printf("%d %d\n", ans.first, ans.second);
        }
        for (int i = 1; i <= n; ++i) {
            std::vector<int>().swap(vec[i]);
        }
    }
    return 0;
}

