#include <bits/stdc++.h>

const int max_N = (int) 3e5 + 21;
const int log_N = 19;

int n, q, siz[max_N], max[max_N], rt;

bool vis[max_N], on[max_N];

std::vector<std::pair<int, int>> vec[max_N];

void find_rt(int x, int p, int sum) {
    siz[x] = 1;
    max[x] = 0;
    for (auto &e : vec[x]) {
        int y = e.first;
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

int dep[max_N], par[max_N][log_N], dis[max_N][log_N];

std::multiset<int> set[max_N][2];

void dfs(int rt, int x, int p, int depth) {
    par[x][depth] = rt;
    siz[x] = 1;
    for (auto &e : vec[x]) {
        int y = e.first;
        if (vis[y] || y == p) {
            continue;
        }
        dis[y][depth] = dis[x][depth] + e.second;
        dfs(rt, y, x, depth);
        siz[x] += siz[y];
    }
}

void build(int x, int depth) {
    vis[x] = true;
    dep[x] = depth;
    dfs(x, x, 0, depth);
    for (auto &e : vec[x]) {
        int y = e.first;
        if (vis[y]) continue;
        rt = 0;
        find_rt(y, x, siz[y]);
        build(rt, depth + 1);
    }
}

void query(int x) {
    if (on[x]) {
        puts("0");
        return;
    }

    int res = 0x3f3f3f3f;
    if (!set[x][1].empty()) {
        res = std::min(res, *set[x][1].begin());
    }
    for (int i = dep[x]; i; --i) {
        if (on[par[x][i - 1]]) {
            res = std::min(res, dis[x][i - 1]);
            continue;
        }

        if (!set[par[x][i]][0].empty()) {
            auto it = set[par[x][i - 1]][1].find(*set[par[x][i]][0].begin());
            set[par[x][i - 1]][1].erase(it);
        }

        if (!set[par[x][i - 1]][1].empty()) {
            res = std::min(res, *set[par[x][i - 1]][1].begin() + dis[x][i - 1]);
        }

        if (!set[par[x][i]][0].empty()) {
            auto it = *set[par[x][i]][0].begin();
            set[par[x][i - 1]][1].insert(it);
        }
    }

    printf("%d\n", res);
}

void add(int x) {
    on[x] = true;
    for (int i = dep[x]; i; --i) {
        if (!set[par[x][i]][0].empty()) {
            auto it = set[par[x][i - 1]][1].find(*set[par[x][i]][0].begin());
            set[par[x][i - 1]][1].erase(it);
        }

        set[par[x][i]][0].insert(dis[x][i - 1]);

        if (!set[par[x][i]][0].empty()) {
            auto it = *set[par[x][i]][0].begin();
            set[par[x][i - 1]][1].insert(it);
        }
    }
}

void del(int x) {
    on[x] = false;
    for (int i = dep[x]; i; --i) {
        if (!set[par[x][i]][0].empty()) {
            auto it = set[par[x][i - 1]][1].find(*set[par[x][i]][0].begin());
            set[par[x][i - 1]][1].erase(it);
        }

        auto it = set[par[x][i]][0].find(dis[x][i - 1]);
        set[par[x][i]][0].erase(it);

        if (!set[par[x][i]][0].empty()) {
            auto it = *set[par[x][i]][0].begin();
            set[par[x][i - 1]][1].insert(it);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++ i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        vec[u].push_back({v, w});
        vec[v].push_back({u, w});
    }
    max[rt = 0] = n + 1;
    find_rt(1, 0, n);
    build(rt, 0);
    for (int i = 1; i <= n; ++i) {
        on[i] = false;
    }
    add(1);
    scanf("%d", &q);
    while (q--) {
        int x;
        char opt[3];
        scanf("%s%d", opt, &x);
        if (*opt == '?') {
            query(x);
        } else if (*opt == '+') {
            add(x);
        } else {
            del(x);
        }
    }
    return 0;
}
