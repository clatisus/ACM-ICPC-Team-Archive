#include <bits/stdc++.h>

const int max_N = 15;
const int max_S = (1 << 15);

int n, a[max_N], bitcnt[max_S], dp[max_S];

bool vis[max_S];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    std::sort(a, a + n);
    int cnt[2] = {0, 0};
    std::reverse(a, a + n);
    for (int i = 0; i < n; ++i) cnt[i & 1] += a[i];
    printf("%d %d\n", cnt[0], cnt[1]);

    return 0;
}

