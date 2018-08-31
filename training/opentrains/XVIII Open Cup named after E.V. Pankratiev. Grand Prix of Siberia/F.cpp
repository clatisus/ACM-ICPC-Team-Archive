#include <bits/stdc++.h>

#define block_id(x) ((x - 1) / B)

const int max_N = (int) 1e5 + 21;
const int sqrt_N = 400 + 21;
const int mod = (int) 1e9 + 7;

int qpow(int x, int k) {
    int ret = 1;
    for (; k; x = 1ll * x * x % mod, k >>= 1)
        if (k & 1) ret = 1ll * ret * x % mod;
    return ret;
}

int n, m, a[max_N], b[max_N], fen[max_N], val[max_N];

int B, tot, Q[max_N], rk[max_N];

int ans[sqrt_N], pre[sqrt_N], pos[sqrt_N], last[sqrt_N];

void modify(int x, int a) {
    for (; x && x <= n; x += (x & -x)) {
        fen[x] = std::max(fen[x], a);
    }
}

int max(int x) {
    int ret = 0;
    for (; x; x -= (x & -x)) {
        ret = std::max(ret, fen[x]);
    }
    return ret;
}

int find(int a) {
    int ret = 0;
    for (int i = (1 << 20); i; i >>= 1) {
        if (ret + i > n || fen[ret + i] > a) continue;
        ret += i;
    }
    return ret;
}

void init() {
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        modify(i, b[i]);
        s = std::max(s, b[i]);
        val[i] = std::min(a[i], s);
        Q[i] = i;
    }
    B = std::sqrt(n * std::log(n)) + 1;
    tot = block_id(n);
    for (int i = 0, l = 1; i <= tot; ++i) {
        int r = i < tot ? l + B : n + 1;
        ans[i] = pre[i] = 1;
        for (int j = l; j < r; ++j) ans[i] = 1ll * ans[i] * val[j] % mod;
        last[i] = 0;
        pos[i] = l;
        std::sort(Q + l, Q + r, [&](int x, int y) { return a[x] < a[y]; });
        l += B;
    }
    for (int i = 1; i <= n; ++i) rk[Q[i]] = i;
}

void down(int i, bool tp = true) {
    int l = i * B + 1;
    int r = i < tot ? l + B : n + 1;
    if (last[i]) {
        for (int j = l; j < r; ++j)
            if (a[j] >= last[i]) {
                val[j] = last[i];
            }
        last[i] = 0;
        pos[i] = l;
    }
    if (tp) {
        pre[i] = ans[i] = 1;
        for (int j = l; j < r; ++j) {
            ans[i] = 1ll * ans[i] * val[j] % mod;
        }
    }
}

void query() {
    int ret = 1;
    for (int i = 0; i <= tot; ++i) {
        ret = 1ll * ret * ans[i] % mod;
    }
    printf("%d\n", ret);
}

void change(int x, int y) {
    int i = block_id(x);
    down(i, false);
    int l = i * B + 1;
    int r = i < tot ? l + B : n + 1;
    a[x] = y;
    val[x] = std::min(y, max(x));
    while (rk[x] + 1 < r) {
        int y = Q[rk[x] + 1];
        if (a[x] <= a[y]) break;
        std::swap(Q[rk[x]], Q[rk[x] + 1]);
        ++rk[x], --rk[y];
    }
    down(i);
}

void block_modify(int i, int x) {
    assert(x >= last[i]);
    if (x == last[i]) return;
    int l = i * B + 1, r = l + B;
    if (pos[i] == r) return;
    while (pos[i] < r) {
        int j = Q[pos[i]];
        if (a[j] >= x) break;
        val[j] = a[j];
        pre[i] = 1ll * pre[i] * val[j] % mod;
        ++pos[i];
    }
    ans[i] = 1ll * pre[i] * qpow(x, r - pos[i]) % mod;
    last[i] = x;
}

void modify(int l, int r, int x) {
    if (l > r) return;
    int li = block_id(l);
    int ri = block_id(r);
    if (li == ri) {
        down(li, false);
        for (int i = l; i <= r; ++i) {
            if (a[i] < x) val[i] = a[i];
            else val[i] = x;
        }
        down(li);
    } else {
        int ll, rr;
        ll = l, rr = (li + 1) * B + 1;
        down(li, false);
        for (int i = ll; i < rr; ++i) {
            if (a[i] < x) val[i] = a[i];
            else val[i] = x;
        }
        down(li);
        for (int i = li + 1; i < ri; ++i) {
            block_modify(i, x);
        }
        ll = ri * B + 1, rr = r + 1;
        down(ri, false);
        for (int i = ll; i < rr; ++i) {
            if (a[i] < x) val[i] = a[i];
            else val[i] = x;
        }
        down(ri);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, b + 1);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 2; i <= n + 1; ++i) scanf("%d", b + i);
    init();
    query();
    for (int i = 1, t, k, v; i <= m; ++i) {
        scanf("%d%d%d", &t, &k, &v);
        if (!t) change(k, v);
        else {
            if (++k <= n) {
                b[k] = v;
                modify(k, v);
                modify(k, find(v), v);
            }
        }
        query();
    }
    return 0;
}
