//Xudyh orz
#include <bits/stdc++.h>
 
template <class T> void read(T &x) {
    int c; while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); (x *= 10) += (c - '0'));
}
 
const int max_N = (int) 2e5 + 21;
const int mod = (int) 1e9 + 7;
 
int n, D, p[max_N], sz[max_N], mx[max_N], Q[max_N];
 
int pw[max_N], ans;
 
bool vis[max_N];
 
std::vector<int> vec[max_N];
 
inline int find(int u) {
    int tot = 1;
    Q[1] = u, p[u] = 0;
    for (int i = 1; i <= tot; ++i) {
        u = Q[i];
        sz[u] = 1, mx[u] = 0;
        for (auto v : vec[u]) {
            if (vis[v] || v == p[u]) continue;
            p[Q[++tot] = v] = u;
        }
    }
    for (int i = tot; i; --i) {
        u = Q[i];
        mx[u] = std::max(mx[u], tot - sz[u]);
        if (mx[u] * 2 <= tot) return u;
        sz[p[u]] += sz[u];
        mx[p[u]] = std::max(mx[p[u]], sz[u]);
    }
    return 0;
}
 
int dep[max_N], maxd[max_N], vp[max_N], cnt;
 
int par[max_N], l[max_N], r[max_N], rt[max_N];
 
void dfs(int u, int root) {
    vp[++cnt] = u;
    rt[u] = root;
    maxd[u] = dep[u];
    for (auto v : vec[u]) {
        if (vis[v] || v == par[u]) continue;
        par[v] = u, dep[v] = dep[u] + 1;
        dfs(v, root);
        maxd[u] = std::max(maxd[u], maxd[v]);
    }
}
 
int a[max_N], s[max_N], ret[max_N];
std::unordered_map<int, int> ext[max_N];
 
inline void getAS(int u) {
    memset(a, 0, (maxd[u] + 1) * sizeof(int));
    for (int i = l[u]; i <= r[u]; ++i) {
        int v = vp[i];
        if (v <= n) ++a[dep[v]];
    }
    for (int i = 0; i <= maxd[u]; ++i) {
        s[i] = a[i];
        if (i) s[i] += s[i - 1];
    }
}
 
void solve(int u) {
    u = find(u);
    dep[u] = 0;
    vp[l[u] = cnt = 1] = u;
    for (auto v : vec[u]) {
        if (vis[v]) continue;
        l[v] = cnt + 1;
        par[v] = u, dep[v] = 1, dfs(v, v);
        r[v] = cnt;
        maxd[u] = std::max(maxd[u], maxd[v]);
    }
    r[u] = cnt;
 
    getAS(u);
    for (int i = 1; i <= cnt; ++i) {
        int v = vp[i];
        if (v <= n && dep[v] <= D) ++ret[u];
        if (v <= n && dep[v] == D) ++ext[u][rt[v]];
        if (v != u && dep[v] <= D) {
            ret[v] += s[std::min(maxd[u], D - dep[v])];
            if (D - dep[v] <= maxd[u]) ext[v][par[v]] += a[D - dep[v]];
        }
    }
 
    for (auto v : vec[u]) {
        if (vis[v]) continue;
        getAS(v);
        for (int i = l[v]; i <= r[v]; ++i) {
            int w = vp[i];
            if (dep[w] <= D) {
                ret[w] -= s[std::min(maxd[v], D - dep[w])];
                if (D - dep[w] <= maxd[v]) ext[w][par[w]] -= a[D - dep[w]];
            }
        }
    }
 
    vis[u] = true;
    for (auto v : vec[u]) if (!vis[v]) solve(v);
}
 
int main() {
    read(n);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) pw[i] = (pw[i - 1] << 1) % mod;
    int tot = n;
    for (int i = 1, u, v; i < n; ++i) {
        read(u), read(v);
        ++tot;
        vec[u].push_back(tot), vec[tot].push_back(u);
        vec[v].push_back(tot), vec[tot].push_back(v);
    }
    read(D);
    solve(1);
    for (int i = 1; i <= tot; ++i) {
        int inner = ret[i];
        int bord = 0, wbord = 0;
        for (auto pr : ext[i]) {
            bord += pr.second;
            wbord = (wbord + pw[pr.second] - 1) % mod;
            if (wbord < 0) wbord += mod;
        }
        inner -= bord;
        wbord = (pw[bord] - 1 - wbord) % mod;
        if (wbord < 0) wbord += mod;
        ans = (ans + 1ll * pw[inner] * wbord) % mod;
    }
    printf("%d\n", ans);
    return 0;
}
