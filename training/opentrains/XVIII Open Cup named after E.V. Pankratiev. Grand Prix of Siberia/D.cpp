#include <bits/stdc++.h>

#define MAXN (510)
#define ll long long

int n;
int x[MAXN], y[MAXN];
ll dp[MAXN][MAXN];
int pre[MAXN][MAXN];
struct node {
    int x1, y1, x2, y2;

    void write() {
        if (x1 < x2) std::swap(x1, x2);
        if (y1 < y2) std::swap(y1, y2);
        printf("%d %d %d %d\n", x1, y1, x2, y2);
    }
};
std::vector<node> vec;

void add(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) return;
    vec.push_back({x1, y1, x2, y2});
}

ll getdp(int l, int r) {
    if (l == r) return dp[l][r] = 0;
    if (dp[l][r] != -1) return dp[l][r];
    if (l == 1 && r == n) {
        dp[l][r] = x[r] - x[l] + y[l] - y[r];
    } else {
        dp[l][r] = 0;
    }
    ll tmp = LLONG_MAX;
    int sit = 0;
    for (int m = l; m < r; ++m) {
        ll now = getdp(l, m) + getdp(m + 1, r) + x[m] - x[l] + y[m + 1] - y[r];
        if (tmp > now) {
            tmp = now;
            sit = m;
        }
    }
    dp[l][r] += tmp;
    pre[l][r] = sit;
    return dp[l][r];
}

void getvec(int l, int r) {
    if (l == r) return;
    int m = pre[l][r];
    if (m != l) {
        add(x[l], y[m], x[m], y[m]);
    }
    if (m + 1 != r) {
        add(x[m + 1], y[r], x[m + 1], y[m + 1]);
    }
    getvec(l, m);
    getvec(m + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", x + i, y + i);
    }
    ll ans;
    if (n == 1) {
        int tx = x[1], ty = y[1];
        ans = tx + ty;
        add(0, ty, tx, ty);
        add(0, 0, 0, ty);
    } else {
        memset(dp, -1, sizeof(dp));
        getdp(1, n);
        add(x[1], y[n], x[1], y[1]);
        add(x[1], y[n], x[n], y[n]);
        getvec(1, n);
        int tx = x[1], ty = y[n];
        ans = dp[1][n] + tx + ty;
        add(0, ty, tx, ty);
        add(0, 0, 0, ty);
    }
    printf("%d %lld\n", (int)vec.size(), ans);
    for (auto p : vec) {
        p.write();
    }
    return 0;
}
