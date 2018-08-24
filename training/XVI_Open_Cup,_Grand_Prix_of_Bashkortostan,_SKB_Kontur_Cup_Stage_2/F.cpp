#include <bits/stdc++.h>

const int max_N = 300+ 21;

int n, a[max_N][max_N], w[max_N][max_N];

void floyd() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            w[i][j] = a[i][j];
        }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) if (~w[i][k])
            for (int j = 1; j <= n; ++j) if (~w[k][j]) {
                int tp = w[i][k] + w[k][j];
                if (w[i][j] == -1 || w[i][j] > tp) w[i][j] = tp;
            }
    }
}

int root, vis[max_N];

void dfs(int u, int rt) {
    vis[u] = rt;
    for (int i = 1; i <= n; ++i) {
        if (a[u][i] == -1 || i == u || vis[i]) continue;
        if (w[root][i] == w[root][u] + a[u][i]) {
            dfs(i, rt);
        }
    }
}

void solve(int x) {
    memset(vis + 1, 0 , n * sizeof(int));
    int ret = -1;
    root = x;
    for (int i = 1; i <= n; ++i)
        if (a[x][i] != -1 && i != x && !vis[i]) {
            if (a[x][i] == w[x][i]) dfs(i, i);
        }
    for (int i = 1; i <= n; ++i) if (vis[i]) {
        if (vis[i] != i && a[x][i] != -1) {
            int tp = w[x][i] + a[x][i];
            if (ret == -1 || ret > tp) ret = tp;
        }
        for (int j = 1; j <= n; ++j) if(vis[j]) {
            if (a[i][j] == -1 || vis[i] == vis[j]) continue;
            int tp = w[x][i] + w[x][j] + a[i][j];
            if (ret == -1 || ret > tp) ret = tp;
        }
    }
    printf("%d\n", ret);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", a[i] + j);
        }
    }
    floyd();
    for (int i = 1; i <= n; ++i) solve(i);
    return 0;
}
