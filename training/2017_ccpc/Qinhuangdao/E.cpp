#include <bits/stdc++.h>

const int inf = 0x3f3f3f3f;

const int max_N = (int) 2e5 + 21;

int T, n, m = 4, fail[7] = {0, 0, 1, 0, 1}, dp[max_N][4][4];

char s[max_N], t[7] = "@CCPC", sigma[3] = "CP";

inline std::pair<int, int> trans(int u, char c) {
    int ret = 0;
    while (u && c != t[u + 1]) u = fail[u];
    if (t[u + 1] == c && ++u == 4) {
        u = fail[u], ++ret;
    }
    return {u, ret};
}

inline void max_it(int &u, int a) {
    (u < a) && (u = a);
}

void testCase() {
    scanf("%d%s", &n, s + 1);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k) {
                dp[i][j][k] = -inf;
            }
    dp[0][0][0] = 0;
    int ans = 0;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < 4; ++j)
            for (int u = 0; u < 4; ++u) {
                int tmp = dp[i][j][u];
                if (tmp == -inf) continue;
                ans = std::max(ans, tmp);
                if (i < n) {
                    auto pr = trans(u, s[i + 1]);
                    int v = pr.first, ttmp = tmp + pr.second;
                    max_it(dp[i + 1][j][v], ttmp);
                }
                if (j < 3) {
                    for (int k = 0; k < 2; ++k) {
                        auto pr = trans(u, sigma[k]);
                        int v = pr.first, ttmp = tmp + pr.second - j;
                        max_it(dp[i][j + 1][v], ttmp);
                    }
                }
            }
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}
