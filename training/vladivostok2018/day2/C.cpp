#include <bits/stdc++.h>

#define MAXN (2000010)

int n;
std::vector<int> vec[MAXN];

int siz[MAXN], max[MAXN], rt;
bool vis[MAXN];
int ans[MAXN];

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

void dfs(int x, int fa) {
    siz[x] = 1;
    for (auto v : vec[x]) {
        if (vis[v] || v == fa) continue;
        dfs(v, x);
        siz[x] += siz[v];
    }
}

void solve(int x, int fa) {
    ans[x] = fa;
    vis[x] = true;
    dfs(x, 0);
    for (auto &y : vec[x]) {
        if (vis[y]) continue;
        rt = 0;
        find_rt(y, x, siz[y]);
        solve(rt, x);
    }
}

int main() {
    while(~scanf("%d", &n)) {
        for (int i = 1; i < n; ++ i) {
            int u, v;
            scanf("%d%d", &u, &v);
            vec[u].push_back(v);
            vec[v].push_back(u);
        }
        max[rt = 0] = n + 1;
        find_rt(1, 0, n);
        solve(rt, 0);
        for (int i = 1; i <= n; ++ i) {
            printf("%d%c", ans[i], " \n"[i == n]);
        }
        for (int i = 1; i <= n; ++ i) {
            vis[i] = false;
            std::vector<int>().swap(vec[i]);
        }
    }
    return 0;
}

