#include <bits/stdc++.h>

inline void read(int &x) {
    int c;
    while (!isdigit(c = getchar()));
    x = c - '0';
    while (isdigit(c = getchar())) {
        x = x * 10 + c - '0';
    }
}

#define ALL(x) (x).begin(), (x).end()

using LL = long long;

const int max_N = (int) 1e5 + 21;

int B, n, m, L[max_N], R[max_N], tot, deg[max_N], prev[max_N];

std::vector<int> lower[max_N], upper[max_N];

int q, ql[max_N], qr[max_N], Q[max_N], small[max_N], cnt;

int f[max_N], siz[max_N], top;

std::pair<int, int> st[max_N];

inline int find(int x, bool rec = false) {
    int r, y;
    for (r = x; f[r] != r; r = f[r]);
    if (!rec) {
        for (; x != r; y = f[x], f[x] = r, x = y);
    }
    return r;
}

LL ans, ret[max_N];

inline void merge(int u, int v, bool rec = false) {
    u = find(u, rec);
    v = find(v, rec);
    if (u == v) return;
    if (siz[u] > siz[v]) {
        std::swap(u, v);
    }
    f[u] = v;
    ans += 1ll * siz[u] * siz[v];
    siz[v] += siz[u];
    if (rec) {
        st[++top] = {u, v};
    }
}

inline void recycle() {
    while (top) {
        auto pr = st[top--];
        int u = pr.first;
        int v = pr.second;
        siz[v] -= siz[u];
        ans -= 1ll * siz[u] * siz[v];
        f[u] = u;
    }
}

inline void init() {
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        siz[i] = 1;
    }
    ans = 0;
}

inline void calc(int x, int u, int v) {
    int a = u;
    while (a >= ql[x]) {
        for (auto b : upper[a]) {
            if (b > v) break;
            merge(a, b, true);
        }
        --a; 
        //a = prev[a];
    }
    ret[x] = ans;
    recycle();
}

inline void solve(int u, int l, int r) {
    if (l >= r) return;
    std::sort(Q + l, Q + r, [&] (int x, int y) { return qr[x] < qr[y]; });
    init();
    int v = u;
    for (int i = l; i < r; ++i) {
        int x = Q[i];
        if (qr[x] <= u) {
            small[++cnt] = x;
        } else {
            while (v < qr[x]) {
                ++v;
                for (auto w : lower[v]) {
                    if (w < u) break;
                    merge(v, w);
                }
            }
            calc(x, u, v);
        }
    }
}

inline void solve_small(int x) {
    calc(x, qr[x], qr[x]);
}

inline void testCase() {
    read(n), read(m), read(q);
    for (int i = 1, u, v; i <= m; ++i) {
        read(u), read(v);
        if (u > v) std::swap(u, v);
        upper[u].push_back(v);
        lower[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        deg[i] = lower[i].size() + upper[i].size();
        std::sort(ALL(lower[i]));
        std::reverse(ALL(lower[i]));
        std::sort(ALL(upper[i]));
    }
    B = m > 1 ? (std::sqrt(2 * m / std::log(2 * m)) + 1) : 1;
    int pre = 0, siz = 0;
    tot = 0;
    for (int i = 1; i <= n; ++i) {
        prev[i] = pre;
        if (deg[i]) pre = i;
        siz += deg[i];
        if (siz >= B) {
            R[++tot] = i;
            L[tot] = R[tot - 1] + 1;
            siz = 0;
        }
    }
    for (int i = 1; i <= q; ++i) {
        read(ql[i]), read(qr[i]);
        Q[i] = i;
    }
    std::sort(Q + 1, Q + 1 + q, [&](int x, int y) { return ql[x] < ql[y]; });
    int l = 1, r;
    cnt = 0;
    for (int i = 1; i < tot; ++i) {
        int x = R[i];
        for (r = l; r <= q && ql[Q[r]] <= x; ++r);
        solve(x, l, r);
        l = r;
    }
    while (l <= q) small[++cnt] = Q[l++];
    init();
    for (int i = 1; i <= cnt; ++i) {
        solve_small(small[i]);
    }
    for (int i = 1; i <= q; ++i) {
        printf("%lld\n", ret[i]);
    }
    for (int i = 1; i <= n; ++i) {
        std::vector<int>().swap(lower[i]);
        std::vector<int>().swap(upper[i]);
    }
}

int main() {
    int T;
    read(T);
    while (T--) {
        testCase();
    }
    return 0;
}

