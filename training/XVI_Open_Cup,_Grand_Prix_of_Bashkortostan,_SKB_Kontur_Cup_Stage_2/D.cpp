#include <bits/stdc++.h>

using LL = long long;

const int max_N = (int) 1e5 + 21;

int n, w, a[max_N], st[max_N][20], bit[max_N];

void init() {
    for (int i = 2; i <= n; ++i) bit[i] = bit[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) st[i][0] = a[i];
    for (int j = 1; j <= bit[n]; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            st[i][j] = std::max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int rmq(int l, int r) {
    int t = bit[r - l + 1];
    return std::max(st[l][t], st[r - (1 << t) + 1][t]);
}

int main() {
    scanf("%d%d", &n, &w);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    init();
    for (int l = 1; l <= n; ++l) {
        LL tmp = -1;
        for (int i = 1; i <= n; i += l) {
            int x = rmq(i, std::min(i + l - 1, n));
            tmp += x + 1;
        }
        if (tmp <= w) return printf("%d\n", l), 0;
    }
    return 0;
}

/*
11 15
1 3 7 4 1 2 1 1 1 1 4
*/
