#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long

struct SAM {
    int tot, root, last;
    int go[MAXN << 1][26], par[MAXN << 1], maxlen[MAXN << 1];
    ll same[MAXN << 1];

    void init() { tot = 0; root = last = newnode(0); }
    int newnode(int ml) {
        maxlen[++ tot] = ml;
        memset(go[tot], 0, sizeof go[tot]);
        par[tot] = 0;
        same[tot] = 1;
        return tot;
    }
    int extend(int w) {
        int p = last, np = newnode(maxlen[p] + 1);
        for (; p && !go[p][w]; p = par[p]) go[p][w] = np;
        if (!p) par[np] = root;
        else {
            int q = go[p][w];
            if (maxlen[p] + 1 == maxlen[q]) par[np] = q;
            else {
                int nq = newnode(maxlen[p] + 1);
                memcpy(go[nq], go[q], sizeof go[q]);
                same[nq] = 0;
                par[nq] = par[q];
                par[np] = par[q] = nq;
                for (; p && go[p][w] == q; p = par[p]) go[p][w] = nq;
            }
        }
        return last = np;
    }
}sam;

int n;
char s[MAXN];
std::vector<int> vec[MAXN << 1];
int pos[MAXN];

const int max_N = (MAXN << 1);

int dfn[max_N], _dfn[max_N], p[max_N], dep[max_N], cnt;

int head[max_N], siz[max_N], max[max_N];

void dfs1(int x) {
    siz[x] = 1, max[x] = 0;
    for (auto y : vec[x]) {
        if (y == p[x]) continue;
        p[y] = x;
        dep[y] = dep[x] + 1;
        dfs1(y);
        if (siz[y] > siz[max[x]]) {
            max[x] = y;
        }
        siz[x] += siz[y];
    }
}

void dfs2(int x, int c) {
    dfn[x] = ++cnt;
    _dfn[cnt] = x;
    head[x] = c;
    if (max[x]) dfs2(max[x], c);
    for (auto y : vec[x]) {
        if (dfn[y]) continue;
        dfs2(y, y);
    }
}

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r

ll qa, len[max_N << 2], val[max_N << 2], lazy[max_N << 2];

void update(int x) {
    val[x] = val[ls(x)] + val[rs(x)];
}

void build(int x, int l, int r) {
    if (l == r) {
        len[x] = sam.maxlen[_dfn[l]] - sam.maxlen[sam.par[_dfn[l]]];
        val[x] = len[x];
    } else {
        build(lch), build(rch);
        len[x] = len[ls(x)] + len[rs(x)];
        update(x);
    }
}

void down(int x) {
    if (!lazy[x]) return;
    val[ls(x)] += len[ls(x)] * lazy[x];
    lazy[ls(x)] += lazy[x];
    val[rs(x)] += len[rs(x)] * lazy[x];
    lazy[rs(x)] += lazy[x];
    lazy[x] = 0;
}

int ql, qr;

void gao(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        qa += val[x];
        val[x] += len[x] * 2;
        lazy[x] += 2;
    } else {
        down(x);
        if (ql <= mid) gao(lch);
        if (qr > mid) gao(rch);
        update(x);
    }
}

void query(int x) {
    while (head[x] != sam.root) {
        ql = dfn[head[x]], qr = dfn[x];
        gao(1, 1, cnt);
        x = p[head[x]];
    }
    ql = 1, qr = dfn[x];
    gao(1, 1, cnt);
    printf("%lld\n", qa);
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    sam.init();
    for (int i = 0; i < n; ++ i) {
        pos[i] = sam.extend(s[i] - 'a');
    }
    for (int i = sam.tot; i >= 1; --i) {
        if (!sam.par[i]) continue;
        vec[sam.par[i]].push_back(i);
    }
    // sam.root, sam.tot
    dfs1(sam.root);
    dfs2(sam.root, sam.root);
    build(1, 1, cnt);
    for (int i = 0; i < n; ++i) {
        query(pos[i]);
    }
    return 0;
}
