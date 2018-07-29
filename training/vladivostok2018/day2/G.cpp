#include <bits/stdc++.h>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r

const int max_N = (int) 1e5 + 21;

int n, q, a[max_N], seg[max_N << 2];

int dep[max_N], p[max_N], siz[max_N], max[max_N];

int head[max_N], dfn[max_N], cnt;

std::vector<int> vec[max_N];

void dfs1(int x) {
    siz[x] = 1, max[x] = 0;
    for (auto &y : vec[x]) {
        if (y == p[x]) continue;
        p[y] = x;
        dep[y] = dep[x] + 1;
        dfs1(y);
        if (siz[y] > siz[max[x]]) {
            max[x] = y;
        }
        siz[x] += siz[x];
    }
}

void dfs2(int x, int c) {
    head[x] = c;
    dfn[x] = ++cnt;
    if (max[x]) {
        dfs2(max[x], c);
    }
    for (auto & y : vec[x]) {
        if (dfn[y]) continue;
        dfs2(y, y);
    }
}

int ql, qr, qa;

void modify(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        seg[x] = qa;
    } else {
        if (ql <= mid) modify(lch);
        if (qr > mid) modify(rch);
        seg[x] = std::max(seg[ls(x)], seg[rs(x)]);
    }
}

void query(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        qa = std::max(qa, seg[x]);
    } else {
        if (ql <= mid) query(lch);
        if (qr > mid) query(rch);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs1(1), dfs2(1, 1);
    scanf("%d", &q);
    while (q--) {
        int a, b;
        char opt[3];
        scanf("%s%d%d", opt, &a, &b);
        if (*opt == 'I') {
            ::a[a] += b;
            ql = qr = dfn[a];
            qa = ::a[a];
            modify(1, 1, n);
        } else {
            qa = 0;
            while (head[a] != head[b]) {
                if (dep[head[a]] > dep[head[b]]) {
                    std::swap(a, b);
                }
                ql = dfn[head[b]];
                qr = dfn[b];
                query(1, 1, n);
                b = p[head[b]];
            }
            if (dep[a] > dep[b]) {
                std::swap(a, b);
            }
            ql = dfn[a];
            qr = dfn[b];
            query(1, 1, n);
            printf("%d\n", qa);
        }
    }
    return 0;
}

