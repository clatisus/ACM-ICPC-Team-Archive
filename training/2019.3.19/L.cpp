#include <bits/stdc++.h>

const int MAXN = 200010;

namespace HK {
    int match[MAXN], d[MAXN];
    bool vis[MAXN];
    int dis;

    std::vector<int> vec[MAXN];
    std::vector<int> left;

    bool bfs() {
        std::queue<int> q;
        dis = INT_MAX;
        memset(d, -1, sizeof(d));
        for (auto u : left) {
            if (match[u] == -1) {
                d[u] = 0;
                q.push(u);
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (d[u] > dis) break;
            for (auto v : vec[u]) {
                if (d[v] != -1) continue;
                d[v] = d[u] + 1;
                if (match[v] == -1) dis = d[v];
                else {
                    d[match[v]] = d[v] + 1;
                    q.push(match[v]);
                }
            }
        }
        return dis != INT_MAX;
    }

    bool dfs(int u) {
        for (auto v : vec[u]) {
            if (!vis[v] && d[v] == d[u] + 1) {
                vis[v] = true;
                if (match[v] != -1 && d[v] == dis) continue;
                if (match[v] == -1 || dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        return false;
    }

    int hk() {
        memset(match, -1, sizeof(match));
        int ret = 0;
        while (bfs()) {
            memset(vis, 0, sizeof(vis));
            for (auto u : left) {
                if (match[u] == -1 && dfs(u)) {
                    ++ret;
                }
            }
        }
        return ret;
    }
}

using namespace HK;

int n, m;
bool ans[MAXN];

void wjj(int u) {
    //printf("u = %d\n", u);
    ans[u] = true;
    for (auto v : vec[u]) {
        if (match[v] != -1 && !ans[match[v]]) {
            wjj(match[v]);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        left.push_back(i);
    }
    for (int i = 1; i <= m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        vec[a + n].push_back(b);
        vec[b].push_back(a + n);
    }
    int dyx = n - hk() - 1;
    printf("%d\n", dyx);
    if (!dyx) {
        puts("");
        return 0;
    }

    for (int i = 1; i <= n + n; ++i) {
        if (match[i] == -1) {
            wjj(i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (ans[i] || ans[i + n]) {
            printf("%d ", i);
        }
    }
    puts("");

    return 0;
}
/*
4 4
 1 2
 1 3
 2 4
 3 4
 */