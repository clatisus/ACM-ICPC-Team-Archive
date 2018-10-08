#include <bits/stdc++.h>

const int max_N = (int) 2e5 + 21;
const int log_N = 20;

int T, n, rt, m, q, c[max_N], h[max_N], tot;

int Q[max_N], u[max_N], v[max_N], w[max_N], ret[max_N];

int f[max_N], val[max_N], ls[max_N], rs[max_N], anc[max_N][log_N];

inline int rk(int x) {
    return std::lower_bound(h + 1, h + 1 + tot, x) - h;
}

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

#define mid ((l + r) >> 1)

using ptr = struct node *;
using DATA = std::pair<int, int>;

struct node {
    DATA data;
    ptr ls, rs;
} pool[max_N * log_N];

ptr tail = pool, seg[max_N];

void new_node(ptr &x, int l, int r, int pos) {
    x = tail++;
    x->data = {1, -pos};
    x->ls = x->rs = nullptr;
    if (l == r) return;
    if (pos <= mid) {
        new_node(x->ls, l, mid, pos);
    } else {
        new_node(x->rs, mid + 1, r, pos);
    }
}

ptr merge(ptr x, ptr y, int l, int r) {
    if (!x) return y;
    if (!y) return x;
    if (l == r) {
        x->data.first += y->data.first;
    } else {
        x->ls = merge(x->ls, y->ls, l, mid);
        x->rs = merge(x->rs, y->rs, mid + 1, r);
        x->data = {INT_MIN, INT_MIN};
        if (x->ls) x->data = std::max(x->data, x->ls->data);
        if (x->rs) x->data = std::max(x->data, x->rs->data);
    }
    return x;
}

void dfs(int u) {
    if (!u) return;
    for (int i = 1; i < log_N; ++i) {
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
    }
    std::vector<int> vec = {ls[u], rs[u]};
    for (auto v : vec) {
        if (!v) continue;
        anc[v][0] = u;
        dfs(v);
    }
    if (ls[u]) seg[u] = merge(seg[ls[u]], seg[rs[u]], 1, tot);
    ret[u] = -seg[u]->data.second;
    //printf("ret[%d] = (%d, %d)\n", u, seg[u]->data.first, seg[u]->data.second);
}

void clr() {
    tail = pool;
    for (int i = 1; i <= rt; ++i) {
        val[i] = ls[i] = rs[i] = anc[i][0] = ret[i] = 0;
        seg[i] = nullptr;
    }
}

int query(int u, int w) {
    for (int i = log_N - 1; ~i; --i) {
        if (!anc[u][i] || val[anc[u][i]] > w) continue;
        u = anc[u][i];
    }
    return h[ret[u]];
}

void testCase() {
    static int id = 0;
    printf("Case #%d:\n", ++id);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
        h[i] = c[i];
        f[i] = i;
    }
    std::sort(h + 1, h + 1 + n);
    tot = std::unique(h + 1, h + 1 + n) - (h + 1);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", u + i, v + i, w + i);
        Q[i] = i;
    }
    std::sort(Q + 1, Q + 1 + m, [&] (int x, int y) { return w[x] < w[y]; });
    rt = n;
    for (int i = 1; i <= m; ++i) {
        int x = find(u[Q[i]]);
        int y = find(v[Q[i]]);
        if (x == y) continue;
        ++rt;
        f[rt] = rt;
        f[x] = f[y] = rt;
        val[rt] = w[Q[i]];
        ls[rt] = x, rs[rt] = y;
        // printf("[%d] ls = %d, rs = %d, val = %d\n", rt, ls[rt], rs[rt], val[rt]);
    }
    for (int i = 1; i <= n; ++i) {
        // printf("rk = %d\n", rk(c[i]));
        new_node(seg[i], 1, tot, rk(c[i]));
    }
    dfs(rt);
    scanf("%d", &q);
    int last = 0;
    while (q--) {
        int u, w;
        scanf("%d%d", &u, &w);
        u ^= last, w ^= last;
        last = query(u, w);
        printf("%d\n", last);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
        clr();
    }
    return 0;
}
