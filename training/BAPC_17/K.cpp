#include <bits/stdc++.h>

#define MAXN (1010)

int n;
char str[MAXN][MAXN];
bool vis[MAXN];
std::vector<int> vec[MAXN], ans;

void dfs(int u) {
    vis[u] = true;
    for (auto v : vec[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
    ans.push_back(u);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= n; ++j) {
            if (str[i][j] == '1') {
                vec[i].push_back(j);
            }
        }
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            printf("impossible\n");
            return 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d%c", ans[i] - 1, " \n"[i == n - 1]);
    }
    return 0;
}

