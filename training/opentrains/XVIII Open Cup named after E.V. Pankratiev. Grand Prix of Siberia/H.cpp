#include <bits/stdc++.h>

#define mid ((l + r) >> 1)
#define lch(x) ((x) ? (x)->ls : nullptr)
#define rch(x) ((x) ? (x)->rs : nullptr)
#define siz(x) ((x) ? (x)->siz : 0)
#define sum(x) ((x) ? (x)->sum : 0)

using LL = long long;

const int max_N = 150000 + 21;

int n, m, Q[max_N], rk[max_N];

LL a[max_N], d[max_N], s[max_N], delta[max_N];

using ptr = struct node *;

struct node {
    int siz;
    LL sum;
    ptr ls, rs;
} pool[max_N * 20];

ptr tail = pool, rt[max_N];

void updt(ptr &x, ptr y, int l, int r, int pos, LL val) {
    x = tail++;
    if (y) *x = *y;
    x->siz++;
    x->sum += val;
    if (l == r) return;
    if (pos <= mid) {
        updt(x->ls, lch(y), l, mid, pos, val);
    } else {
        updt(x->rs, rch(y), mid + 1, r, pos, val);
    }
}

LL kth(int l, int r, int k) {
    // printf("kth(%d %d %d) = ", l, r, k);
    auto a = rt[l - 1], b = rt[r];
    int lo = 1, hi = n;
    LL ret = 0;
    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        int cnt = siz(lch(b)) - siz(lch(a));
        LL sum = sum(lch(b)) - sum(lch(a));
        if (k > cnt) {
            k -= cnt;
            ret += sum;
            a = rch(a);
            b = rch(b);
            lo = mi + 1;
        } else {
            a = lch(a);
            b = lch(b);
            hi = mi;
        }
    }
    ret += sum(b) - sum(a);
    // printf("%d, %lld\n", lo, ret);
    return ret;
}

void query(int l, int r) {
    int len = (r - l + 1) / 3;
    LL ret = s[r] - s[l - 1];
    ret += kth(l, r, len);
    ret += kth(l, r, len * 2);
    ret -= kth(l, r, len * 3);
    if (ret & 1) {
        printf("%lld.5\n", ret >> 1);
    } else {
        printf("%lld\n", ret >> 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", d + i);
    }
    for (int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + a[i] + d[i];
        delta[i] = a[i] - d[i];
        Q[i] = i;
    }
    std::sort(Q + 1, Q + 1 + n, [&](int x, int y) { return delta[x] > delta[y]; });
    for (int i = 1; i <= n; ++i) rk[Q[i]] = i;
    for (int i = 1; i <= n; ++i) {
        updt(rt[i], rt[i - 1], 1, n, rk[i], delta[i]);
        // printf("[%d] rk = %d, delta = %lld\n", i, rk[i], delta[i]);
    }
    scanf("%d", &m);
    for (int i = 1, l, r; i <= m; ++i) {
        scanf("%d%d", &l, &r);
        query(l, r);
    }
    return 0;
}
/*
11
1 4 3 2 4 6 7 2 3 5 1
9 3 5 2 5 9 2 4 5 8 3
5
1 6
2 10
5 7
6 11
3 8
*/
