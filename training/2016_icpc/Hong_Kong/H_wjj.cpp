#include <bits/stdc++.h>

#define MAXN (14010)
#define MAXM (30010)

int n, m;
int f[MAXN], sz[MAXN], born[MAXN];
std::bitset<MAXN> b;
double ans;
struct edge {
    int u, v, w;
    bool operator < (const edge &rhs) const {
        return w > rhs.w;
    }
} e[MAXM];
struct event {
    int l, r, sz;
};

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void solve(int l, int r, std::vector<event> &vec) {
    std::bitset<MAXN> tmp = b;
    if (l == r) {
        // bitset for time l means after add edge [1, l]
        // the state of sz
        if (l == m) return;
        for (auto &p : vec) tmp |= tmp << p.sz;
        for (int i = n / 2; i; --i) {
            if (tmp[i]) {
                ans = std::min(ans, 1.0 * e[l + 1].w / i);
                break;
            }
        }
        return;
    }

    std::vector<event> vl, vr;
    int m = (l + r) >> 1;
    for (auto &p : vec) {
        if (p.l <= l && r <= p.r) b |= b << p.sz;
        else {
            if (p.l <= m) vl.push_back(p);
            if (p.r >  m) vr.push_back(p);
        }
    }
    solve(l, m, vl);
    solve(m + 1, r, vr);
    b = tmp;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[i] = {u + 1, v + 1, w};
    }
    std::sort(e + 1, m + e + 1);

    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        sz[i] = 1;
        born[i] = 0;
    }
    std::vector<event> vec;
    for (int i = 1; i <= m; ++i) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;
        // sz[u] and sz[v] come to an end
        vec.push_back({born[u], i - 1, sz[u]});
        vec.push_back({born[v], i - 1, sz[v]});

        f[u] = v;
        sz[v] += sz[u];
        born[v] = i;
    }
    for (int i = 1; i <= n; ++i) if (f[i] == i) {
        vec.push_back({born[i], m, sz[i]});
    }

    ans = 1e200;
    b.set(0);
    solve(0, m, vec);
    printf("%.10f\n", ans);
    return 0;
}


