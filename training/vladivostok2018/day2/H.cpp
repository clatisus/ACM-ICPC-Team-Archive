#include <bits/stdc++.h>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r

const int max_N = (int) 2e5 + 21;

int n, q;

int p[max_N], dep[max_N], siz[max_N], max[max_N];

int dfn[max_N], head[max_N], cnt;

std::vector<int> vec[max_N];

void dfs1(int x) {
    siz[x] = 1;
    max[x] = 0;
    for (auto &y : vec[x]) {
        if (y == p[x]) continue;
        p[y] = x;
        dep[y] = dep[x] + 1;
        dfs1(y);
        siz[x] += siz[y];
        if (siz[y] > siz[max[x]]) {
            max[x] = y;
        }
    }
}

void dfs2(int x, int c) {
    dfn[x] = ++cnt;
    head[x] = c;
    if (max[x]) dfs2(max[x], c);
    for (auto &y : vec[x]) {
        if (dfn[y]) continue;
        dfs2(y, y);
    }
}

int ql, qr, qa;

int seg[2][max_N << 2], lazy[max_N << 2], last[max_N];

void downLight(int x) {
    if (seg[1][x] > std::max(seg[1][ls(x)] ,seg[1][rs(x)])) {
        seg[1][ls(x)] = seg[1][rs(x)] = seg[1][x];
    }
}

void upLight(int x) {
    seg[1][x] = std::max(seg[1][ls(x)], seg[1][rs(x)]);
}

void updateLight(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        seg[1][x] = qa;
    } else {
        downLight(x);
        if (ql <= mid) updateLight(lch);
        if (qr > mid) updateLight(rch);
        upLight(x);
    }
}

void queryLight(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        qa = seg[1][x];
    } else {
        downLight(x);
        if (ql <= mid) queryLight(lch);
        if (qr > mid) queryLight(rch);
    }
}

void downHeavy(int x, int l, int r) {
    if (~lazy[x]) {
        seg[0][ls(x)] = lazy[x] * (mid - l + 1);
        seg[0][rs(x)] = lazy[x] * (r - mid);
        lazy[ls(x)] = lazy[rs(x)] = lazy[x];
        lazy[x] = -1;
    }
}

void upHeavy(int x) {
    seg[0][x] = seg[0][ls(x)] + seg[0][rs(x)];
}
 
void updateHeavy(int x, int l, int r) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) {
        seg[0][x] = qa * (r - l + 1);
        lazy[x] = qa;
    } else {
        downHeavy(x, l, r);
        if (ql <= mid) updateHeavy(lch);
        if (qr > mid) updateHeavy(rch);
        upHeavy(x);
    }
}

void queryHeavy(int x, int l, int r) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) {
        qa += seg[0][x];
    } else {
        downHeavy(x, l, r);
        if (ql <= mid) queryHeavy(lch);
        if (qr > mid) queryHeavy(rch);
    }
}

int query(int u, int v) {
    int res = 0;

    while (head[u] != head[v]) {
        if (dep[head[u]] > dep[head[v]]) {
            std::swap(u, v);
        }

        res += dep[v] - dep[head[v]] + 1;

        ql = dfn[head[v]];
        qr = dfn[v];
        qa = 0;
        queryHeavy(1, 1, n);
        res -= qa;

        ql = qr = dfn[p[head[v]]];
        queryLight(1, 1, n);
        if (last[head[v]] >= qa) --res;

        v = p[head[v]];
    }

    if (dep[u] > dep[v]) {
        std::swap(u, v);
    }

    res += dfn[v] - dfn[u];

    ql = dfn[u] + 1;
    qr = dfn[v];
    qa = 0;
    queryHeavy(1, 1, n);
    res -= qa;

    return res;
}

void modify(int u, int v, int t) {
    while (head[u] != head[v]) {
        if (dep[head[u]] > dep[head[v]]) {
            std::swap(u, v);
        }

        ql = dfn[head[v]] + 1;
        qr = dfn[v];
        qa = 1;
        updateHeavy(1, 1, n);

        --ql;
        qa = t;
        updateLight(1, 1, n);
        last[head[v]] = t;

        if (max[v]) {
            ql = qr = dfn[v] + 1;
            qa = 0;
            updateHeavy(1, 1, n);
        }


        v = p[head[v]];
    }

    if (dep[u] > dep[v]) {
        std::swap(u, v);
    }

    ql = dfn[u] + 1;
    qr = dfn[v];
    qa = 1;
    updateHeavy(1, 1, n);

    --ql;
    qa = t;
    updateLight(1, 1, n);

    if (max[v]) {
        ql = qr = dfn[v] + 1;
        qa = 0;
        updateHeavy(1, 1, n);
    }

    if (dfn[u] > 1) {
        if (max[p[u]] == u) {
            ql = qr = dfn[u];
            qa = 0;
            updateHeavy(1, 1, n);
        } else {
            last[u] = -1;
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; ++i) {
        last[i] = -1;
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int opt, u, v;
        scanf("%d%d%d", &opt, &u, &v);
        if (opt) modify(u, v, i);
        else printf("%d\n", query(u, v));
    }
    return 0;
}
