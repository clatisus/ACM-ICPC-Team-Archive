#include <bits/stdc++.h>

namespace fastIO {
#define BUF_SIZE (100000)
    bool IOerror = false;

    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = p1;
        if (p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if (pend == p1) {
                IOerror = true;
                return -1;
            }
        }
        return *p1++;
    }

    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    inline void read(int &x) {
        char ch;
        int f = 1;
        while (blank(ch = nc()) || ch == '-') if (ch == '-') f = -1;
        if (IOerror) return;
        for (x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
        x *= f;
    }

#undef BUF_SIZE
};

using namespace fastIO;

const int max_N = 1 << 16;
const int offset = max_N >> 2;

int n, m, u[max_N], v[max_N], w[max_N], Q[max_N];

std::bitset<offset> seg[max_N];

int f[max_N], sz[max_N], tmp[max_N];

inline int find(int u) {
    int r, v;
    for (r = u; r != f[r]; r = f[r]);
    for (; u != r; v = f[u], f[u] = r, u = v);
    return r;
}

int val[max_N], st[max_N], ed[max_N], tot, a[max_N], Time;

inline void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    ed[tmp[u]] = ed[tmp[v]] = Time - 1;
    if (sz[u] > sz[v]) std::swap(u, v);
    f[u] = v;
    sz[v] += sz[u];
    st[tmp[v] = ++tot] = Time;
    val[tot] = sz[v];
}

#define ls(u) ((u) << 1)
#define rs(u) (ls(u) | 1)
#define mid ((l + r) >> 1)
#define lch ls(u), l, mid
#define rch rs(u), mid + 1, r

long double ans = 1e60;

void solve(int u, int l, int r, std::vector<int> &vec) {
    if (u == 1) {
        seg[u].set(0);
    } else {
        seg[u] = seg[u >> 1];
    }

    std::vector<int> L, R;
    for (auto &i : vec) {
        if (st[i] <= l && r <= ed[i]) {
            seg[u] |= (seg[u] << val[i]);
        } else {
            if (st[i] <= mid) L.push_back(i);
            if (ed[i] > mid)  R.push_back(i);
        }
    }

    if (l == r) {
        for (int i = n / 2; i; --i) {
            if (seg[u].test(i)) {
                ans = std::min(ans, (long double) a[l] / i);
                // printf("%d / %d = %.10f\n", a[l], minS, 1. *a[l] / minS);
                break;
            }
        }
    } else {
        solve(lch, L), solve(rch, R);
    }
}

int main() {
    read(n), read(m);
    for (int i = 1; i <= m; ++i) {
        read(u[i]), read(v[i]), read(w[i]);
        ++u[i], ++v[i], Q[i] = i;
    }
    std::sort(Q + 1, Q + 1 + m, [&](int x, int y) { return w[x] > w[y]; });

    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        val[tmp[i] = ++tot] = sz[i] = 1;
        st[tot] = 1;
    }

    for (int i = 1, j, k = 1; i <= m; i = j) {
        a[++Time] = w[Q[i]];
        for (; k < i; ++k) merge(u[Q[k]], v[Q[k]]);
        for (j = i; j <= m && w[Q[i]] == w[Q[j]]; ++j);
    }

    std::vector<int> vec;
    for (int i = 1; i <= tot; ++i) {
        vec.push_back(i);
        if (!ed[i]) ed[i] = Time;
        // printf("event %d -> %d, %d\n", st[i], ed[i], val[i]);
    }
    solve(1, 1, Time, vec);

    printf("%.10Lf\n", ans);

    return 0;
}
