#include <bits/stdc++.h>

#define MAXN (10010)
#define MAXS (110)

int n, m;
int BLOCKSIZE;
std::vector<int> vec[2][MAXN];
std::pair<int, int> t[2][MAXN];

int f[MAXN], sz[MAXN], nowans;
int ans[MAXN];
std::pair<int, int> git[MAXN << 1];

int par[2][MAXN];
int cen[2][MAXN];
int idx[2][MAXN];
int stack[MAXN], top;

bool iscen[2][MAXN];

std::vector<int> q[MAXS][MAXS];

void dfs(int u, int fa, int k)
{
    int bottom = top;
    for (auto v : vec[k][u]) {
        if (v == fa) continue;
        par[k][v] = u;
        dfs(v, u, k);
        if (top - bottom >= BLOCKSIZE) {
            if (!iscen[k][u]) {
                iscen[k][u] = true;
                idx[k][u] = ++ idx[k][0];
            }
            while (top != bottom) {
                cen[k][stack[-- top]] = u;
            }
        }
    }
    stack[top ++] = u;
}

void merge(int u, int v)
{
    while (u != f[u]) u = f[u];
    while (v != f[v]) v = f[v];
    if (u == v) return;
    if (sz[u] > sz[v]) std::swap(u, v);
    git[top ++] = {u, v};
    f[u] = v;
    -- nowans;
    sz[v] += sz[u];
}

void recover(int bottom)
{
    while (top != bottom) {
        auto &p = git[-- top];
        int u = p.first;
        int v = p.second;
        f[u] = u;
        f[v] = v;
        ++ nowans;
        sz[v] -= sz[u];
    }
}

void solve(int u, int fa, int k, int _u = 0)
{
    auto &e = t[k][u];
    int before_bottom = top;
    merge(e.first, e.second);
    int after_bottom = top;
    if (iscen[k][u]) {
        if (k == 0) {
            solve(1, 0, 1, u);

        } else {
            for (auto i : q[idx[0][_u]][idx[1][u]]) {
                int j = i;
                while (j != _u) merge(t[0][j].first, t[0][j].second), j = par[0][j];
                j = i;
                while (j !=  u) merge(t[1][j].first, t[1][j].second), j = par[1][j];
                ans[i] = nowans;
                recover(after_bottom);
            }
        }
    }
    for (auto v : vec[k][u]) {
        if (v == fa) continue;
        solve(v, u, k, _u);
    }
    recover(before_bottom);
}

void testCase()
{
    scanf("%d%d", &n, &m);
    nowans = m;
    top = 0;
    for (int i = 1; i <= m; ++ i) f[i] = i, sz[i] = 1;
    for (int k = 0; k < 2; ++ k) {
        for (int i = 1; i <= n; ++ i) {
            vec[k][i].clear();
            iscen[k][i] = false;
            idx[k][0] = 0;
        }
        int u, v;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d", &u, &v);
            t[k][i] = {u, v};
        }
        for (int i = 1; i < n; ++ i) {
            scanf("%d%d", &u, &v);
            vec[k][u].push_back(v);
            vec[k][v].push_back(u);
        }
    }
    BLOCKSIZE = (int)sqrt(n);
    for (int k = 0; k < 2; ++ k) {
        dfs(1, 0, k);
        if (!iscen[k][1]) {
            iscen[k][1] = true;
            idx[k][1] = ++ idx[k][0];
        }
        while (top) {
            cen[k][stack[-- top]] = 1;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        int a = idx[0][cen[0][i]];
        int b = idx[1][cen[1][i]];
        q[a][b].push_back(i);
    }
    solve(1, 0, 0);
    for (int i = 1; i <= n; ++ i) {
        printf("%d\n", ans[i]);
    }
    for (int i = 1; i <= idx[0][0]; ++ i) {
        for (int j = 1; j <= idx[1][0]; ++ j) {
            q[i][j].clear();
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T --) {
        testCase();
    }
    return 0;
}
