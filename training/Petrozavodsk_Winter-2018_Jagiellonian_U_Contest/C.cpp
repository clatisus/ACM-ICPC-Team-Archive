//
// Created by zzh on 2019/3/5.
//

#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
    int c;
    while (!isdigit(c = getchar()));
    x = c - '0';
    while (isdigit(c = getchar())) {
        x = x * 10 + c - '0';
    }
}

const int max_N = (int) 2e5 + 21;

int T, n, m, a[max_N], b[max_N], h[max_N], dp[max_N], Q[max_N];

inline int rk(int x) {
    return std::lower_bound(h + 1, h + 1 + m, x) - h;
}

bool cmp(int x, int y) {
    return a[x] < a[y];
}

int bit[max_N];

#define lbt(x) ((x) & -(x))

inline void updt(int x, int a) {
    for (int i = x; i <= m; i += lbt(i)) {
        bit[i] = a ? std::max(bit[i], a) : 0;
    }
}

inline int query(int x) {
    int ret = 0;
    for (int i = x; i; i -= lbt(i)) {
        ret = std::max(ret, bit[i]);
    }
    return ret;
}

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    int tot = 0;
    for (int i = l; i <= r; ++i) {
        Q[++tot] = i;
    }
    std::sort(Q + 1, Q + 1 + tot, cmp);
    for (int i = 1, j = 1; i <= tot; ++i) {
        if (Q[i] <= mid) continue;
        while (j <= tot && a[Q[i]] > a[Q[j]]) {
            if (Q[j] <= mid) {
                updt(b[Q[j]], dp[Q[j]]);
            }
            ++j;
        }
        int tmp = query(b[Q[i]] - 1) + 1;
        dp[Q[i]] = std::max(dp[Q[i]], tmp);
    }
    for (int i = 1; i <= tot; ++i) {
        if (Q[i] <= mid) {
            updt(b[Q[i]], 0);
        }
    }
    solve(mid + 1, r);
}

void testCase() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        dp[i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        read(b[i]);
        h[i] = b[i];
    }
    std::sort(h + 1, h + 1 + n);
    m = std::unique(h + 1, h + 1 + n) - h - 1;
    for (int i = 1; i <= n; ++i) {
        b[i] = rk(b[i]);
    }
    solve(1, n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = std::max(ans, dp[i]);
    }
    printf("%d\n", ans);
}


int main() {
    read(T);
    while (T--) {
        testCase();
    }
}
/*
1
6
1 2 6 3 4 6
4 1 3 5 7 7
 */