#include <bits/stdc++.h>

const int max_S = (1 << 10);
const int max_N = 50;
const int inf = 0x3f3f3f3f;

int n, s, maxs, Q[max_N], last[max_N], tot, a[max_N], b[max_N];

int dp[max_N][max_S], bitcnt[max_S];;

bool vis[max_N][max_S];

int calc(int x, int sta) {
    if (x > tot) return 0;
    if (vis[x][sta]) return dp[x][sta];
    int cur = Q[x];
    int &ret = dp[x][sta];
    if (cur <= n) {
        ret = -inf;
        if (!((sta >> (cur - 1)) & 1)) {
            int tmp = b[b[0] - bitcnt[sta]];
            tmp += calc(x + 1, sta | (1 << (cur - 1)));
            ret = std::max(ret, tmp);
        }
        if (((sta >> (cur - 1)) & 1) || last[cur] > x) {
            int tmp = a[a[0] - (x - bitcnt[sta]) + 1];
            tmp += calc(x + 1, sta);
            ret = std::max(ret, tmp);
        }
    } else {
        ret = inf;
        if (!((sta >> (cur - 1)) & 1)) {
            int tmp = -b[b[0] - bitcnt[sta]];
            tmp += calc(x + 1, sta | (1 << (cur - 1)));
            ret = std::min(ret, tmp);
        }
        if (((sta >> (cur - 1)) & 1) || last[cur] > x) {
            int tmp = -a[a[0] - (x - bitcnt[sta]) + 1];
            tmp += calc(x + 1, sta);
            ret = std::min(ret, tmp);
        }
    }
    vis[x][sta] = true;
    return ret;
}

int main() {
    scanf("%d%d", &n, &s);
    maxs = (1 << (n * 2));
    for (int i = 1; i < maxs; ++i) {
        bitcnt[i] = bitcnt[i - (i & -i)] + 1;
    }
    tot = n * (s + 1) * 2;
    for (int i = 1; i <= tot; ++i) {
        scanf("%d", Q + i);
        last[Q[i]] = i;
    }
    scanf("%d", a);
    for (int i = 1; i <= a[0]; ++i) {
        scanf("%d", a + i);
    }
    std::sort(a + 1, a + 1 + a[0]);
    scanf("%d", b);
    for (int i = 1; i <= b[0]; ++i) {
        scanf("%d", b + i);
    }
    std::sort(b + 1, b + 1 + b[0]);
    printf("%d\n", calc(1, 0));
    return 0;
}
