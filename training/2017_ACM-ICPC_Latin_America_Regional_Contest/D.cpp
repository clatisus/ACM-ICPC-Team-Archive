#include <bits/stdc++.h>

inline void read(int &x) {
   char c;
   while (!isdigit(c = getchar()));
   x = c - '0';
   while (isdigit(c = getchar())) {
       (x *= 10) += c - '0';
   }
}

const int max_N = (int) 1e5 + 21;
const int sqrt_N = 400 + 21;

int n, m, q, tot;

int B, c[max_N], cnt[sqrt_N][max_N], lazy[sqrt_N], Cnt[max_N];

#define block_id(x) ((x - 1) / B)

void down(int i) {
    int l = i * B + 1;
    int r = i < tot ? l + B : n + 1;
    if (lazy[i]) {
        for (int j = l; j < r; ++j) {
            c[j] = lazy[i];
        }
        lazy[i] = 0;
        for (int j = l; j < r; ++j) ++cnt[i][c[j]];
    }
}

int query(int col) {
    int ret = 0;
    for (int i = 0; i <= tot; ++i) {
        int l = i * B + 1;
        int r = i < tot ? l + B : n + 1;
        if (lazy[i]) {
            if (lazy[i] == col) ret += r - l;
        }
        else ret += cnt[i][col];
    }
    return ret;
}

void block_modify(int i, int col) {
    if (!lazy[i]) {
        int l = i * B + 1;
        int r = i < tot ? l + B : n + 1;
        for (int j = l; j < r; ++j) --cnt[i][c[j]];
    }
    lazy[i] = col;
}

void modify(int l, int r, int col) {
    int li = block_id(l);
    int ri = block_id(r);
    if (li == ri) {
        down(li);
        for (int i = l; i <= r; ++i) {
            --cnt[li][c[i]];
            c[i] = col;
            ++cnt[li][col];
        }
    } else {
        int ll, rr;
        ll = l;
        rr = (li + 1) * B;
        down(li);
        for (int i = ll; i <= rr; ++i) {
            --cnt[li][c[i]];
            c[i] = col;
            ++cnt[li][col];
        }
        for (int i = li + 1; i < ri; ++i) block_modify(i, col);
        ll = ri * B + 1;
        rr = r;
        down(ri);
        for (int i = ll; i <= rr; ++i) {
            --cnt[ri][c[i]];
            c[i] = col;
            ++cnt[ri][col];
        }
    }
}

void testCase() {
    B = std::sqrt(n) + 1;
    tot = block_id(n);
    for (int i = 1; i <= n; ++i) c[i] = 1;
    for (int i = 0, l = 1; i <= tot; ++i) {
        int r = i < tot ? l + B : n + 1;
        lazy[i] = 0;
        cnt[i][1] = r - l;
        l += B;
    }
    while (q--) {
        int u, v, a, b;
        read(u), read(v), read(a), read(b);
        int s = query(u);
        int m1 = (a + 1ll * s * s) % n + 1;
        int m2 = (a + 1ll * (s + b) * (s + b)) % n + 1;
        if (m1 > m2) std::swap(m1, m2);
        modify(m1, m2, v);
    }
    for (int i = 0; i <= tot; ++i) down(i);
    for (int i = 1; i <= m; ++i) Cnt[i] = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int id = block_id(i);
        ans = std::max(ans, ++Cnt[c[i]]);
        --cnt[id][c[i]];
    }
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &q)) testCase();
    return 0;
}

