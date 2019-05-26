#include <bits/stdc++.h>

const int MAXN = (1 << 20) + 10;

int n;
int a[MAXN];
int dp[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        a[i] ^= a[i - 1];
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = n; i; --i) {
        dp[a[i]] = i;
    }
    for (int s = (1 << 20) - 1; ~s; --s) {
        for (int j = 0; j < 20; ++j) {
            if ((s >> j) & 1) continue;
            dp[s] = std::min(dp[s], dp[s | (1 << j)]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        int now = 0;
        for (int j = 19; ~j; --j) {
            if ((a[i] >> j) & 1) continue;
            if (dp[now | (1 << j)] <= i) {
                now |= 1 << j;
            }
        }
        now += a[i] ^ now;
        printf("%d%c", now, " \n"[i == n]);
    }
    return 0;
}
