#include <bits/stdc++.h>

#define MAXN (1000010)

int n;
std::vector<int> vec[MAXN];
int sz[MAXN];
int cnt[MAXN];

void dfs(int u, int fa) {
    sz[u] = 1;
    for (auto v : vec[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    ++ cnt[sz[u]];
}

bool check(int i) {
    ++ i;
    if (n % i) return false;
    int ret = 0;
    int w = n / i;
    for (int j = w; j <= n; j += w) ret += cnt[j];
    return ret == i;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++ i) {
        if (check(i)) {
            printf("%d ", i);
        }
    }
    puts("");
    return 0;
}
