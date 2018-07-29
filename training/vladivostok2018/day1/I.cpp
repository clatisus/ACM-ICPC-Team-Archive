#include <bits/stdc++.h>

const int max_N = 1000 + 21;

int T, n;

double dp[max_N][max_N], p;

void testCase() {
    double _p;
    scanf("%d%lf", &n, &_p);
    if (std::abs(1 - _p) < 1e-7) {
        printf("%d\n", n);
        return;
    }
    double ans = 0;
    p = 1. - _p;
    for (int k = 0; k <= n; ++k) {
        double tmp = 0;
        dp[0][k] = 1.;
        for (int i = 1; i <= n + 1; ++i) {
            int h = i - k - 2;
            if (h >= 0) tmp -= dp[h][k] * p;
            tmp = tmp * _p + dp[i - 1][k] * (1. - _p);
            if (i == n + 1) {
                dp[i][k] = tmp / (1. - _p);
            } else {
                dp[i][k] = tmp;
            }
        }
        if (k) {
            ans += k * (dp[n + 1][k] - dp[n + 1][k - 1]);
        }
        p *= _p;
    }
    printf("%.10f\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}

