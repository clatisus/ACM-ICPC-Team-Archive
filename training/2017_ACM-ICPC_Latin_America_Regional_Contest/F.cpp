#include <bits/stdc++.h>

#define lbt(x) ((x) & -(x))

using LL = long long;

const int max_N = (int) 1e5 + 21;

int T, n, m, h[max_N], tot;

int rk(int x) {
    return std::lower_bound(h + 1, h + 1 + tot, x) - h;
}

LL bit[max_N], dp[max_N], ans;

void modify(int x, LL a) {
    for (; x && x <= tot; x += lbt(x)) {
        bit[x] = std::max(bit[x], a);
    }
}

LL query(int x) {
    LL ret = 0;
    for (; x; x -= lbt(x)) {
        ret = std::max(ret, bit[x]);
    }
    return ret;
}

struct node {
    int x, y;
    LL val;
} p[max_N];

void testCase() {
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%lld", &p[i].x, &p[i].y, &p[i].val);
        h[++tot] = p[i].y;
    }
    std::sort(h + 1, h + 1 + tot);
    tot = std::unique(h + 1, h + 1 + tot) - (h + 1);
    std::sort(p + 1, p + 1 + n, [&](const node &a, const node&b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    m = 0;
    for (int i = 1; i <= n; ++i) {
        if (!i || p[i].x != p[i - 1].x || p[i].y != p[i - 1].y) {
            p[++m] = p[i];
        } else {
            p[m].val += p[i].val;
        }
    }
    ans = 0;
    for (int i = 1, j = 1; i <= m; ++i) {
        while (j <= m && p[i].x > p[j].x) {
            modify(rk(p[j].y), dp[j]);
            ++j;
        }
        dp[i] = query(rk(p[i].y) - 1) + p[i].val;
        ans = std::max(ans, dp[i]);
    }
    printf("%lld\n", ans);
    for (int i = 1; i <= tot; ++i) bit[i] = 0;
    tot = 0;
}

int main() {
    while (~scanf("%d", &n)) testCase();
    return 0;
}

