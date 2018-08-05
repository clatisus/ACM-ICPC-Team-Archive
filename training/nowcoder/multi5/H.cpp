#include <bits/stdc++.h>
 
const int max_N = (int) 5e5 + 21;
using ll = long long;
const ll inf = (ll) 1e18 + 21;
 
int n, a[max_N], h[max_N], tot, ans[max_N], m;
 
ll dp[max_N], bit[max_N], k;
 
ll sum(int x) {
    ll res = 0;
    for (; x; x -= (x & -x)) {
        res += bit[x];
        if (res > inf) res = inf;
    }
    return res;
}
 
void add(int x, ll y) {
    for (; x <= tot; x += (x & -x)) {
        bit[x] += y;
        if (bit[x] > inf) bit[x] = inf;
    }
}
 
int main() {
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        h[i] = a[i];
    }
    std::sort(h + 1, h + 1 + n);
    tot = std::unique(h + 1, h + 1 + n) - (h + 1);
    for (int i = n; i; --i) {
        int rk = std::lower_bound(h + 1, h + 1 + tot, a[i]) - h;
        dp[i] = 1 + sum(tot - rk);
        if (dp[i] > inf) dp[i] = inf;
        add(tot - rk + 1, dp[i]);
    }
    if (sum(tot) < k) return puts("-1"), 0;
    int last = 0;
    for (int i = 1; i <= n; ++i) {
        //printf("dp[%d] = %lld\n", i, dp[i]);
        if (a[i] <= last) continue;
        if (k > dp[i]) k -= dp[i];
        else {
            ans[++m] = i;
            last = a[i];
            if (!--k) break;
        }
    }
    printf("%d\n", m);
    for (int i = 1; i <= m; ++i) {
        printf("%d%c", ans[i], " \n"[i == m]);
    }
    return 0;
}
