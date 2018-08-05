#include <bits/stdc++.h>
 
#define lbt(x) ((x) & -(x))
 
#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r
 
const int max_N = (int) 2e5 + 21;
 
int n, b[max_N], a[max_N], bit[max_N];
 
int sum(int x) {
    int res = 0;
    for (; x; x -= lbt(x)) res += bit[x];
    return res;
}
 
void add(int x) {
    for (; x <= n; x += lbt(x)) ++bit[x];
}
 
int seg[max_N << 1], lazy[max_N << 1];
 
void update(int x) {
    seg[x] = std::min(seg[ls(x)], seg[rs(x)]);
}
 
void build(int x, int l, int r) {
    if (l == r) seg[x] = l;
    else {
        build(lch), build(rch);
        update(x);
    }
}
 
void down(int x) {
    if (!lazy[x]) return;
    seg[ls(x)] += lazy[x], lazy[ls(x)] += lazy[x];
    seg[rs(x)] += lazy[x], lazy[rs(x)] += lazy[x];
    lazy[x] = 0;
}
 
int ql, qr, qa;
 
void modify(int x, int l, int r) {
    if (ql <= l && r <= qr) {
        seg[x] += qa;
        lazy[x] += qa;
    } else {
        down(x);
        if (ql <= mid) modify(lch);
        if (qr > mid) modify(rch);
        update(x);
    }
}
 
long long ans;
 
int main() {
    scanf("%d", &n);
    n >>= 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", b + i);
        b[i] >>= 1;
        a[b[i]] = i;
        ans += sum(n - b[i]);
        add(n - b[i] + 1);
    }
    // printf("even ans = %lld\n", ans);
    build(1, 0, n);
    for (int i = 1; i <= n; ++i) {
        ans += seg[1];
        int x = a[i];
        ql = 0, qr = x - 1, qa = 1;
        modify(1, 0, n);
        ql = x, qr = n, qa = -1;
        modify(1, 0, n);
    }
    printf("%lld\n", ans);
    return 0;
}
