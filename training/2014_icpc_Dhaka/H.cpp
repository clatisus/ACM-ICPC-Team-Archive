#include <bits/stdc++.h>

#define MAXN (10010)

int n;
int c[MAXN], cnt[200];
int dp[5][200], pre[5][200];

int main() {
    int T;
    scanf("%d", &T);
    int Case = 0;
    while (T --) {
        scanf("%d", &n);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) {
            scanf("%d", c + i);
            ++ cnt[c[i]];
        }
        for (int i = 1; i <= 160; ++i) cnt[i] += cnt[i - 1];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= 160; ++i) {
            dp[1][i] = std::abs(4 * cnt[i] - n);
        }
        for (int i = 2; i <= 3; ++i) {
            for (int j = i - 1; j <= 160; ++j) {
                int tmp = INT_MAX, sit = 0;
                for (int jj = i - 2; jj + 1 <= j; ++jj) {
                    if (dp[i - 1][jj] == INT_MAX) continue;
                    int now = dp[i - 1][jj] + std::abs(4 * (cnt[j] - cnt[jj]) - n);
                    if (now < tmp) {
                        tmp = now;
                        sit = jj;
                    }
                }
                //printf("dp[%d][%d] = %d\n", i, j, tmp);
                dp[i][j] = tmp;
                pre[i][j] = sit;
            }
        }
        int ans = INT_MAX, sit = 0;
        for (int i = 2; i + 1 <= 160; ++i) {
            if (dp[3][i] == INT_MAX) continue;
            int now = dp[3][i] + std::abs(4 * (cnt[160] - cnt[i]) - n);
            if (now < ans) {
                ans = now;
                sit = i;
            }
        }
        printf("Case %d: %d %d %d\n", ++Case, pre[2][pre[3][sit]], pre[3][sit], sit);
    }
    return 0;
}
