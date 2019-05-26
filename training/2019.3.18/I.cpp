//
// Created by zzh on 2019/3/18.
//

#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int sqrt_N = 512;

int n, m, a[max_N];

std::bitset<max_N> cnt[sqrt_N], tmp;

#define block(x) ((x) / sqrt_N)

inline void rev(std::bitset<max_N> &set, int x) {
    if (set.test(x)) {
        set.reset(x);
    } else {
        set.set(x);
    }
}

void modify(int x, int y) {
    for (int i = block(x); i <= m; ++i) {
        rev(cnt[i], y);
    }
}

void query(int l, int r) {
    int lb = block(l);
    int rb = block(r);
    tmp.reset();
    tmp.set(1e5 + 1);
    if (lb == rb) {
        for (int i = l; i <= r; ++i) {
            rev(tmp, a[i]);
        }
    } else {
        if (rb - lb >= 1) {
            tmp ^= cnt[rb - 1];
            tmp ^= cnt[lb];
        }
        for (int i = l; i < (lb + 1) * sqrt_N; ++i) {
            rev(tmp, a[i]);
        }
        for (int i = rb * sqrt_N; i <= r; ++i) {
            rev(tmp, a[i]);
        }
    }
    int p = tmp._Find_first();
    if (p > 1e5) p = -1;
    printf("%d\n", p);
}

int main() {
    scanf("%d", &n);
    m = block(n - 1);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        modify(i, a[i]);
    }
    int q, opt, x, y;
    while (scanf("%d", &q), q) {
        while (q--) {
            scanf("%d%d%d", &opt, &x, &y);
            --x;
            if (opt == 1) {
                modify(x, a[x]);
                modify(x, a[x] = y);
            } else {
                --y;
                query(x, y);
                fflush(stdout);
            }
        }
    }
}