#include <bits/stdc++.h>

#define mod (1000000007)

int n, m, k;

int powmod(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
    }
    return ret;
}

void testCase(int cs) {
    scanf("%d%d%d", &n, &m, &k);
    if (n == 1 && m == 1) {
        printf("Case #%d: %d\n", cs, 2 * k);
        return;
    }
    int ans = powmod(k, n * m);
    int tmp = 0;
    for (int i = 1; i < k; ++i) {
        tmp = (tmp + powmod(i, n + m - 2)) % mod;
    }
    tmp = 1ll * tmp * powmod(k, n * m - n - m + 1) % mod;
    tmp = 1ll * n * m * tmp % mod;
    printf("Case #%d: %d\n", cs, (tmp + ans) % mod);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int _ = 1; _ <= T; ++_) {
        testCase(_);
    }
    return 0;
}
