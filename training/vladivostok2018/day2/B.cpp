#include <bits/stdc++.h>

#define max_N (100010)

int n, a[max_N], siz[max_N], max[max_N], rt;
int col[max_N];
bool vis[max_N];

int anc[max_N][21], dis[max_N][21];

std::vector<std::pair<int, int> > vec[max_N];
std::vector<std::pair<int, int> > dq[max_N];

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

void dfs(int x, int fa, int depth, int d) {
    dis[x][depth] = d;
    anc[x][depth] = rt;
    siz[x] = 1;
    for (auto &e : vec[x]) {
        int y = e.first, w = e.second;
        if (vis[y] || y == fa) continue;
        dfs(y, x, depth, d + w);
        siz[x] += siz[y];
    }
}

void solve(int x, int depth) {
    vis[x] = true;
    dfs(x, 0, depth, 0);
    for (auto &e : vec[x]) {
        int y = e.first;
        if (vis[y]) continue;
        rt = 0;
        find_rt(y, x, siz[y]);
        solve(rt, depth + 1);
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
    solve(rt, 0);
    int q;
    scanf("%d", &q);
    for (int ti = 1; ti <= q; ++ ti) {
        int opt, v, d, c;
        scanf("%d%d", &opt, &v);
        if (opt == 1) {
            scanf("%d%d", &d, &c);
            col[ti] = c;
            for (int i = 20; ~i; -- i) {
                if (anc[v][i] && dis[v][i] <= d) {
                    int u = anc[v][i], w = d - dis[v][i];
                    while (dq[u].size() && dq[u].rbegin() -> first <= w) dq[u].pop_back();
                    dq[u].push_back({w, ti});
                }
            }
        } else {
            int ret = 0;
            for (int i = 20; ~i; -- i) {
                if (anc[v][i]) {
                    int u = anc[v][i];
                    if (dq[u].empty() || dq[u].begin() -> first < dis[v][i]) continue;
                    /*
                    for (auto p : dq[u]) {
                        printf("dq[%d] = (%d, %d)\n", u, p.first, col[p.second]);
                    }*/
                    int l = 0, r = dq[u].size() - 1, ans = -1;
                    while (l <= r) {
                        int m = (l + r) >> 1;
                        if (dq[u][m].first >= dis[v][i]) {
                            ans = dq[u][m].second;
                            l = m + 1;
                        } else {
                            r = m - 1;
                        }
                    }
                    if (ans != -1 && ret < ans) {
                        ret = ans;
                    }
                }
            }
            printf("%d\n", col[ret]);
        }
    }
    return 0;
}

