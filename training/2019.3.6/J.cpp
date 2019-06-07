//
// Created by zzh on 2019/3/6.
//

#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int sqrt_N = 500 + 21;

const int mod = 998244353;

inline void updt(int &x, int a) {
    if ((x += a) >= mod) x -= mod;
}

int n, a[max_N], dp[max_N], sum[sqrt_N][sqrt_N];

inline void set(int x, int a) {
    dp[x] = a;
    for (int i = 1; i < sqrt_N; ++i) {
        if (::a[x] == i) continue;
        updt(sum[i][x % i], a);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) {
        scanf("%d", a + i);
    }
    a[n] = -1;
    set(n, 1);
    for (int i = n - 1; i; --i) {
        int tmp = 0;
        if (a[i] < sqrt_N) {
            tmp = sum[a[i]][i % a[i]];
        } else {
            for (int k = i + a[i]; k <= n; k += a[i]) {
                if (a[k] == a[i]) continue;
                updt(tmp, dp[k]);
            }
        }
        set(i, tmp);
    }
    for (int i = 1 + a[0]; i <= n; i += a[0]) {
        if (a[0] == a[i]) continue;
        updt(dp[0], dp[i]);
    }
    if (a[0] != a[1]) {
        updt(dp[0], dp[1]);
    }
    printf("%d\n", dp[0]);
}