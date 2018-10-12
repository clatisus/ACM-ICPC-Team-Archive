#include <bits/stdc++.h>

#define MAXN (100010)

int n;
std::vector<int> vec[MAXN];
int sz[MAXN], son[MAXN];
std::pair<int, int> ans[MAXN];
int now[30];

void dfs(int u, int fa) {
    sz[u] = 1;
    for (auto v : vec[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

void getans(int u, int fa, int level) {
    ans[u] = {++ now[level], level};
    for (auto v : vec[u]) {
        if (v == fa || v == son[u]) continue;
        getans(v, u, level + 1);
    }    
    if (son[u]) {
        getans(son[u], u, level);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(1, 0);
    getans(1, 0, 1);
    for (int i = 1; i <= n; ++i) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}

