#include <bits/stdc++.h>

using LL = long long;

const int max_N = 110;

int l, k;

LL f[max_N][2], ans;

int main() {
    scanf("%d%d", &l, &k);
    f[0][0] = 1;
    for (int i = 1; i <= l; ++i) {
        f[i][0] = f[i - 1][1];
        f[i][1] = f[i - 1][0];
        if (i >= k) f[i][1] += f[i - k][0];
        ans += f[i][1];
        //printf("f[%d][%d] = %lld\n", i, 0, f[i][0]);
        //printf("f[%d][%d] = %lld\n", i, 1, f[i][1]);
    }
    printf("%lld\n", ans);
    return 0;
}
