#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

int T, n, m, deg[max_N], _deg[max_N], tmp[max_N], top, Q[max_N];

std::vector<int> vec[max_N];

int f[max_N], siz[max_N], vis[max_N];

int find(int u) {
    return f[u] == u ? u : find(f[u]);
}

std::pair<int, int> st[max_N];

inline void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    if (siz[u] > siz[v]) {
        std::swap(u, v);
    }
    f[u] = v;
    siz[v] += siz[u];
    st[++top] = {u, v};
}

inline void recover() {
    auto pr = st[top--];
    int u = pr.first;
    int v = pr.second;
    f[u] = u;
    siz[v] -= siz[u];
}

struct ans {
    int p;
    std::vector<int> vec;
} ret[max_N];

inline bool cmp(int u, int v) {
    return deg[u] == deg[v] ? u < v : deg[u] < deg[v];
}

void testCase() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        deg[i] = 0;
        std::vector<int>().swap(vec[i]);
        std::vector<int>().swap(ret[i].vec);
    }
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
        ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= n; ++i) {
        _deg[i] = deg[i];
        f[i] = Q[i] = i;
        siz[i] = 1;
        vis[i] = 0;
    }
    std::sort(Q + 1, Q + 1 + n, cmp);
    top = 0;
    for (int i = 1; i <= n; ++i) {
        int u = Q[i];
        tmp[u] = top;
        for (auto v : vec[u]) {
            if (cmp(u, v)) continue;
            merge(u, v);
        }
    }
    for (int i = n; i; --i) {
        int u = Q[i];
        if (_deg[u] + 1 < siz[find(u)]) {
            puts("No");
            return;
        }
        while (top > tmp[u]) {
            recover();
        }
        ret[i].p = u;
        for (auto v : vec[u]) {
            if (cmp(u, v)) continue;
            --_deg[v];
            int w = find(v);
            if (vis[w] != u) {
                ret[i].vec.push_back(v);
                vis[w] = u;
            }
        }
    }
    puts("Yes");
    for (int i = 1; i <= n; ++i) {
        printf("%d %d", ret[i].p, (int) ret[i].vec.size());
        for (auto x : ret[i].vec) {
            printf(" %d", x);
        }
        puts("");
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}

