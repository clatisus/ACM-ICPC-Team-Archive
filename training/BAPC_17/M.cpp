#include <bits/stdc++.h>

#define MAXN (100010)

int n;
int xh, yh, xw, yw;
std::vector<std::pair<int, int> > vec;
int a[MAXN], tot;
int dp[MAXN], c[MAXN];

int ask(int x) {
    int ret = INT_MIN;
    for (; x; x -= x & (-x)) ret = std::max(ret, c[x]);
    return ret;
}

void modify(int x, int t) {
    for (; x <= tot; x += x & (-x)) {
        c[x] = std::max(c[x], t);
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d%d%d%d", &xh, &yh, &xw, &yw);
    if (xh > xw) std::swap(xh, xw), std::swap(yh, yw);
    for (int i = 0; i < n; ++i) {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        if (xh <= xi && xi <= xw && std::min(yh, yw) <= yi && yi <= std::max(yh, yw)) {
            vec.push_back({xi, yi});
            a[++ tot] = yi;
        }
    }
    std::sort(a + 1, tot + a + 1);
    tot = std::unique(a + 1, tot + a + 1) - a - 1;
    for (auto &p : vec) {
        p.second = std::lower_bound(a + 1, tot + a + 1, p.second) - a;
    }
    int m = vec.size();
    if (yh > yw) {
        for (auto &p : vec) {
            p.second = tot + 1 - p.second;
        }
    }
    std::sort(vec.begin(), vec.end());
    int ans = 0;
    for (int i = 1; i <= m; ++i) {
        //printf("%d\n", vec[i - 1].second);
        dp[i] = ask(vec[i - 1].second) + 1;
        ans = std::max(ans, dp[i]);
        modify(vec[i - 1].second, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}
