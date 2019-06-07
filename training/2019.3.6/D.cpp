#include <bits/stdc++.h>

const int BIT = 11;
const int N = 1 << BIT;
typedef long double ld;

ld f[N];
ld dp[BIT][N];
ld fac[N];

ld comb(int n, int m) {
    return fac[n] - fac[m] - fac[n - m];
}

int main() {
    for (int i = 1; i < N; ++i) {
        f[i] = f[i - 1] + std::log(2 * i - 1);
        fac[i] = fac[i - 1] + std::log(i);
    }
    int n, k;
    scanf("%d%d", &n, &k);
    k = (1 << n) - k;
    dp[n][k] = 1;
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j < 1 << i; ++j) {
            for (int k = 0; k < 1 << (i - 1); ++k) {
                int left = j - 1, right = (1 << i) - 2 - left;
                int leftpair = k;
                if (leftpair * 2 > left) {
                    continue;
                }
                ld sum = comb(left, leftpair * 2);
                sum += f[leftpair];
                left -= leftpair << 1;
                if (right < left) {
                    continue;
                }
                sum += fac[left] + comb(right, left);
                right -= left;
                sum += f[right >> 1];
                sum -= f[(1 << (i - 1)) - 1];
                dp[i - 1][k] += std::exp(sum) * (1.0 * j / ((1 << i) - 1)) * dp[i][j];
            }
        }
    }
    ld ans = 0;
    for (int i = 1; i < BIT; ++i) {
        for (int j = 0; j < N; ++j) {
            ans += dp[i][j];
        }
    }
    printf("%.15Lf\n", ans);
    return 0;
}
