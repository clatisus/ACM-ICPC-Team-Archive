#include <bits/stdc++.h>

#define MAXN (80)
#define ll long long

int n, K;
ll dp[2][MAXN][2 * MAXN * MAXN];
std::vector<int> a;
int h[MAXN], c[MAXN];

int main() {
    scanf("%d%d", &n, &K);
    a.push_back(0);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", h + i, c + i);
        for (int j = -70; j <= 70; ++j) {
            if (h[i] + j > 0) {
                a.push_back(h[i] + j);
            }
        }
    }
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    int m = (int)a.size() - 1;

    int cur = 0;
    memset(dp[cur], -1, sizeof(dp[cur]));
    for (int k = 1; k <= m; ++k) {
        dp[cur][1][k] = 1ll * std::abs(a[k] - h[1]) * c[1];
       // if (a[k] <= 9) printf("dp[%d][%d][%d] = %lld\n", 1, 1, a[k], dp[0][1][k]);
    }
    for (int i = 2; i <= n; ++i) {
        cur ^= 1;
        memset(dp[cur], -1, sizeof(dp[cur]));
        for (int j = 1; j <= i; ++j) {
            for (int k = j; k <= m; ++k) {
                dp[cur][j][k] = dp[cur ^ 1][j][k];
                if (dp[cur][j][k] == -1) continue;
                if (h[i] > a[k]) {
                    dp[cur][j][k] += 1ll * std::abs(a[k] - h[i]) * c[i];
                }
            }
        }
        for (int j = 1; j <= i; ++j) {
            ll min = dp[cur ^ 1][j - 1][j - 1];
           // if (min == -1) {
           //     printf("dp[%d][%d][%d] = %lld\n", i - 1, j - 1, a[j - 1], dp[cur ^ 1][j - 1][j - 1]);
           // }
            //if (i == 4 && j == 3){
              //  printf("wjj!\n");
            //}
            for (int k = j; k <= m; ++k) {
               // assert(min != -1);
                if (min != -1) {
                    ll tmp = min + 1ll * std::abs(a[k] - h[i]) * c[i];
                    if (dp[cur][j][k] == -1) dp[cur][j][k] = tmp;
                    else dp[cur][j][k] = std::min(dp[cur][j][k], tmp);
                } else {
                    min = dp[cur ^ 1][j - 1][k];
                }

                //if (a[k] <= 9) printf("dp[%d][%d][%d] = %lld\n", i, j, a[k], dp[cur][j][k]);

                if (dp[cur ^ 1][j - 1][k] != -1) {
                    min = std::min(min, dp[cur ^ 1][j - 1][k]);
                }
            }
        }
    }

    ll ans = LLONG_MAX;
    for (int j = K; j <= n; ++j) {
        for (int k = 1; k <= m; ++k) {
            if (dp[cur][j][k] == -1) continue;
            ans = std::min(ans, dp[cur][j][k]);
        }
    }
    printf("%lld\n", ans);

    return 0;
}

