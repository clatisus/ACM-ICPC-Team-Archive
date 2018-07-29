#include <bits/stdc++.h>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r

#define max_N (100010)
#define max_A (100010)
#define ll long long

int n, a[max_N], siz[max_N], max[max_N], rt;

bool vis[max_N];

std::vector<int> vec[max_N];

void find_rt(int x, int p, int sum) {
    siz[x] = 1;
    max[x] = 0;
    for (auto &y : vec[x]) {
        if (vis[y] || y == p) continue;
        find_rt(y, x, sum);
        siz[x] += siz[y];
        max[x] = std::max(max[x], siz[y]);
    }
    max[x] = std::max(max[x], sum - siz[x]);
    if (max[x] < max[rt]) {
        rt = x;
    }
}

ll seg[8][max_N << 2];

bool clr[max_N << 2];

#define seg_max_len 0
#define seg_max_val 1
#define seg_max_prod 2
#define seg_max_siz 3
#define seg_min_len 4
#define seg_min_val 5
#define seg_min_prod 6
#define seg_min_siz 7

int ql, qr, qt;

ll qa[4];

void modify(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        for (int i = 0; i < 3; ++i) {
            seg[qt + i][x] += qa[i];
        }
        ++seg[qt + 3][x];
    } else {
        if (clr[x]) {
            for (int i = 0; i < 8; ++i) {
                seg[i][ls(x)] = seg[i][rs(x)] = 0;
            }
            clr[ls(x)] = clr[rs(x)] = true;
            clr[x] = false;
        }
        if (ql <= mid) modify(lch);
        if (qr > mid) modify(rch);
        for (int i = 0; i < 4; ++i) {
            seg[qt + i][x] = seg[qt + i][ls(x)] + seg[qt + i][rs(x)];
        }
    }
}

void query(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        for (int i = 0; i < 4; ++i) {
            qa[i] += seg[qt + i][x];
        }
    } else {
        if (clr[x]) {
            for (int i = 0; i < 8; ++i) {
                seg[i][ls(x)] = seg[i][rs(x)] = 0;
            }
            clr[ls(x)] = clr[rs(x)] = true;
            clr[x] = false;
        }
        if (ql <= mid) query(lch);
        if (qr > mid) query(rch);
    }
}

#define mina 0
#define maxa 100000

ll ans;

void dfs1(int x, int p, int min, int max, int len) {
    ql = 0, qr = min;
    qt = 4;
    for (int i = 0; i < 4; ++i) {
        qa[i] = 0;
    }
    query(1, mina, maxa);
    ans -= qa[2] + qa[1] * (len - 1);
    for (int i = 0; i < 4; ++i) {
        qa[i] = seg[qt + i][1] - qa[i];
    }
    ans -= (qa[3] * (len - 1) + qa[0]) * min;

    ql = 0, qr = max;
    qt = 0;
    for (int i = 0; i < 4; ++i) {
        qa[i] = 0;
    }
    query(1, mina, maxa);
    ans += (qa[3] * (len - 1) + qa[0]) * max;
    for (int i = 0; i < 4; ++i) {
        qa[i] = seg[qt + i][1] - qa[i];
    }
    ans += qa[2] + qa[1] * (len - 1);

  //  printf("dfs1(%d, %d, %d, %d) = %lld\n", x, p, min, max, ans);

    siz[x] = 1;
    for (auto &y : vec[x]) {
        if (vis[y] || y == p) continue;
        dfs1(y, x, std::min(min, a[y]), std::max(max, a[y]), len + 1);
        siz[x] += siz[y];
    }
}

void dfs2(int x, int p, int min, int max, int len) {
    ql = qr = min;
    qa[0] = len;
    qa[1] = min;
    qa[2] = 1ll * min * len;
    qt = 4;
    modify(1, mina, maxa);

    ql = qr = max;
    qa[0] = len;
    qa[1] = max;
    qa[2] = 1ll * max * len;
    qt = 0;
    modify(1, mina, maxa);

    for (auto &y : vec[x]) {
        if (vis[y] || y == p) continue;
        dfs2(y, x, std::min(min, a[y]), std::max(max, a[y]), len + 1);
    }
}

void solve(int x) {
    vis[x] = true;

    ql = qr = a[x];
    qa[0] = 1;
    qa[1] = a[x];
    qa[2] = a[x];
    qt = 0;
    modify(1, mina, maxa);
    qt = 4;
    modify(1, mina, maxa);

    for (auto &y : vec[x]) {
        if (vis[y]) continue;
        int min = std::min(a[x], a[y]);
        int max = std::max(a[x], a[y]);
        dfs1(y, x, min, max, 2);
        dfs2(y, x, min, max, 2);
    }

    for (int i = 0; i < 8; ++i) {
        seg[i][1] = 0;
    }
    clr[1] = true;

    for (auto &y : vec[x]) {
        if (vis[y]) continue;
        rt = 0;
        find_rt(y, x, siz[y]);
        solve(rt);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i < n; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    max[rt = 0] = n + 1;
    find_rt(1, 0, n);
    solve(rt);
    printf("%lld\n", ans);
    return 0;
}

