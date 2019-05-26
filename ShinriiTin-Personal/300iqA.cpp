#include <bits/stdc++.h>

namespace zxa {
    const int max_N = 23333;
    int n;
    std::vector<int> vec[max_N];
    int S[max_N], Q[max_N], *Top, idx;
    int f[max_N], pre[max_N], nxt[max_N], vis[max_N];
    void add_edge(int u, int v) {
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    int find(int x) {
        return x == f[x] ? x : f[x] = find(f[x]);
    }
    int lca(int x, int y) {
        ++idx;
        x = find(x);
        y = find(y);
        while (true) {
            if (x) {
                if (vis[x] == idx) return x;
                vis[x] = idx;
                x = find(pre[nxt[x]]);
            }
            std::swap(x, y);
        }
    }
    void blossom(int x, int y, int z) {
        while (find(x) != z) {
            pre[x] = y;
            if (S[nxt[x]] == 1) {
                S[*++Top = nxt[x]] = 0;
            }
            f[x] = f[nxt[x]] = z;
            y = nxt[x];
            x = pre[y];
        }
    }
    void match(int x) {
        for (int i = 1; i <= n; ++i) f[i] = i;
        memset(S, -1, sizeof(S));
        memset(Q, 0, sizeof(Q));
        S[*(Top = Q + 1) = x] = 0;
        for (int *i = Q + 1; *i; ++i) {
            for (auto &g : vec[*i]) {
                if (S[g] == -1) {
                    pre[g] = *i, S[g] = 1;
                    if (!nxt[g]) {
                        int u = g, v = *i, lst;
                        while (v) {
                            lst = nxt[v], nxt[v] = u, nxt[u] = v;
                            v = pre[u = lst];
                        }
                        return;
                    }
                    S[*++Top = nxt[g]] = 0;
                } else if (!S[g] && find(g) != find(*i)) {
                    int z = lca(g, *i);
                    blossom(g, *i, z);
                    blossom(*i, g, z);
                }
            }
        }
    }
    void solve() {
        memset(nxt, 0, sizeof(nxt));
        memset(pre, 0, sizeof(pre));
        for (int i = 1; i <= n; ++i) {
            if (nxt[i]) continue;
            match(i);
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            if (nxt[i]) ++ans;
        ans >>= 1;
    }
}

const int max_N = 233;

int n, m;

char a[max_N][max_N];

inline int id1(int x, int y) { return x * m + y + 1; }

inline int id2(int x, int y) { return id1(x, y) + n * m; }

inline std::pair<int, int> inv_id1(int id) {
    --id;
    return {id / m, id % m};
}

void gather_color(std::vector<int>& color, int x, int y) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            if (nx < 0 || nx >= n) continue;
            int ny = y + dy;
            if (ny < 0 || ny >= m) continue;
            if (islower(a[nx][ny])) {
                color.push_back(a[nx][ny] - 'a');
            }
        }
    }
}

int mex(std::vector<int> &color) {
    if (color.empty()) return 0;
    std::sort(color.begin(), color.end());
    color.erase(std::unique(color.begin(), color.end()), color.end());
    int ret = 0;
    for (; ret < color.size() && color[ret] == ret; ++ret)
        ;
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", a[i]);
    }
    zxa::n = n * m << 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '*') {
                zxa::add_edge(id1(i, j), id2(i, j));
                if (i && a[i - 1][j] == '.') {
                    zxa::add_edge(id1(i, j), id1(i - 1, j));
                }
                if (i < n - 1 && a[i + 1][j] == '.') {
                    zxa::add_edge(id1(i, j), id1(i + 1, j));
                }
                if (j && a[i][j - 1] == '.') {
                    zxa::add_edge(id2(i, j), id1(i, j - 1));
                }
                if (j < m - 1 && a[i][j + 1] == '.') {
                    zxa::add_edge(id2(i, j), id1(i, j + 1));
                }
            } else if (a[i][j] == '+') {
                zxa::add_edge(id1(i, j), id2(i, j));
                if (i && a[i - 1][j] == '.') {
                    zxa::add_edge(id1(i, j), id1(i - 1, j));
                    zxa::add_edge(id2(i, j), id1(i - 1, j));
                }
                if (i < n - 1 && a[i + 1][j] == '.') {
                    zxa::add_edge(id1(i, j), id1(i + 1, j));
                    zxa::add_edge(id2(i, j), id1(i + 1, j));
                }
                if (j && a[i][j - 1] == '.') {
                    zxa::add_edge(id1(i, j), id1(i, j - 1));
                    zxa::add_edge(id2(i, j), id1(i, j - 1));
                }
                if (j < m - 1 && a[i][j + 1] == '.') {
                    zxa::add_edge(id1(i, j), id1(i, j + 1));
                    zxa::add_edge(id2(i, j), id1(i, j + 1));
                }
            }
        }
    }
    zxa::solve();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '*' || a[i][j] == '+') {
                if (zxa::nxt[id1(i, j)] == id2(i, j)) continue;
                if (!zxa::nxt[id1(i, j)] || !zxa::nxt[id2(i, j)]) continue;
                auto p1 = inv_id1(zxa::nxt[id1(i, j)]);
                auto p2 = inv_id1(zxa::nxt[id2(i, j)]);
                std::vector<int> color;
                gather_color(color, p1.first, p1.second);
                gather_color(color, p2.first, p2.second);
                gather_color(color, i, j);
                char c = 'a' + mex(color);
                a[p1.first][p1.second] = a[p2.first][p2.second] = a[i][j] = c;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        puts(a[i]);
    }
}
