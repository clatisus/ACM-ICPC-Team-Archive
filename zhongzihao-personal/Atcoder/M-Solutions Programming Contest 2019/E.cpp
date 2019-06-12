#include <bits/stdc++.h>

const int moder = (int) 1e6 + 3;

int pre[moder];

int powermod(int a, int exp) {
    int ret = 1;
    for (; exp > 0; exp >>= 1) {
        if (exp & 1) {
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

void solve() {
    int x, d, n;
    scanf("%d%d%d", &x, &d, &n);
    if (!d) {
        printf("%d\n", powermod(x, n));
        return;
    }
    if (!x) {
        puts("0");
        return;
    }
    x = 1ll * powermod(d, moder - 2) * x % moder;
    if (x + n - 1 >= moder) {
        puts("0");
        return;
    }
    int ans = 1ll * pre[x + n - 1] * powermod(pre[x - 1], moder - 2) % moder * powermod(d, n) % moder;
    printf("%d\n", ans);
}

int main() {
    pre[0] = 1;
    for (int i = 1; i < moder; ++i) {
        pre[i] = 1ll * pre[i - 1] * i % moder;
    }
    int test;
    scanf("%d", &test);
    while (test--) {
        solve();
    }
    return 0;
}
