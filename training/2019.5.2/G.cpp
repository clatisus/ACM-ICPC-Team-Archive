#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

int n, m, out[max_N];

std::vector<int> vec[max_N], rev[max_N];

bool inf[2][max_N], vis[2][max_N];

std::queue<std::pair<int, int>> queue;

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    memset(inf, true, sizeof(inf));
    memset(vis, false, sizeof(vis));

    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        out[i] = vec[i].size();
        if (!out[i]) {
            inf[0][i] = false;
            queue.emplace(0, i);
            inf[1][i] = false;
            queue.emplace(1, i);
        }
    }
    while (!queue.empty()) {
        int p = queue.front().first;
        int u = queue.front().second;
        queue.pop();
        for (auto &v : rev[u]) {
            if ((p && !--out[v]) || (!p && inf[1][v])) {
                inf[p ^ 1][v] = false;
                queue.emplace(p ^ 1, v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        out[i] = vec[i].size();
        if (!out[i]) {
            vis[0][i] = true;
            queue.emplace(0, i);
        }
    }
    while (!queue.empty()) {
        int p = queue.front().first;
        int u = queue.front().second;
        queue.pop();
        for (auto &v : rev[u]) {
            if ((p && !--out[v]) || (!p && !vis[1][v])) {
                vis[p ^ 1][v] = true;
                queue.emplace(p ^ 1, v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (inf[0][i]) putchar('D');
        else {
            putchar(vis[0][i] ? 'L' : 'W');
        }
    }
    puts("");
    for (int i = 1; i <= n; ++i) {
        if (inf[1][i]) putchar('D');
        else {
            putchar(vis[1][i] ? 'W' : 'L');
        }
    }
    puts("");
}