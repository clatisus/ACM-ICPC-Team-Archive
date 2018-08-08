#include <bits/stdc++.h>

const int max_N = 20;
const int max_S = (1 << max_N);

int n, m, maxs, inout[max_N];

int sum[max_S], dp[max_S];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int a, b, p;
        scanf("%d%d%d", &a, &b ,&p);
        inout[a] += p;
        inout[b] -= p;
    }
    for (int i = 0; i < n; ++i) sum[1 << i] = inout[i];
    maxs = (1 << n);
    for (int s = 1; s < maxs; ++s) {
        int lbt = s & -s;
        if (lbt == s) continue;
        sum[s] = sum[s ^ lbt] + sum[lbt];
    }
    for (int s = 1; s < maxs; ++s) {
        for (int i = 0; i < n; ++i)
            if ((s >> i) & 1) {
                dp[s] = std::max(dp[s], dp[s ^ (1 << i)]);
            }
        if (!sum[s]) ++dp[s];
    }
    printf("%d\n", n - dp[maxs - 1]);
    return 0;
}

