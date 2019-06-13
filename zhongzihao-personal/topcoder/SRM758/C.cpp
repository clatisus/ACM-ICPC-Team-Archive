#include <bits/stdc++.h>

const int N = 110;
const int M = 20010;
const int moder = (int) 1e9 + 7;

int dp1[N][M], dp2[N][M];
int pre1[N][M], pre2[N][M];
int fac[M];

void update(int &a, int b) {
    a += b;
    a -= a >= moder ? moder : 0;
}

class PrettyLiar {
public:
    int count(int S, std::vector<int> kaede, std::vector<int> kanade) {
        fac[0] = 1;
        for (int i = 1; i < M; ++i) {
            fac[i] = 1ll * fac[i - 1] * i % moder;
        }
        int n = kaede.size();
        dp1[0][0] = dp2[0][0] = 1;
        for (auto u : kaede) {
            for (int i = n - 1; i >= 0; --i) {
                for (int j = 0; j <= S; ++j) {
                    update(dp1[i + 1][std::min(S, j + u)], dp1[i][j]);
                }
            }
        }
        for (auto u : kanade) {
            for (int i = n - 1; i >= 0; --i) {
                for (int j = 0; j <= S; ++j) {
                    update(dp2[i + 1][std::min(S, j + u)], dp2[i][j]);
                }
            }
        }
        memcpy(pre1, dp1, sizeof(dp1));
        memcpy(pre2, dp2, sizeof(dp2));
        for (int i = 0; i <= n; ++i) {
            for (int j = S - 1; j >= 0; --j) {
                update(pre1[i][j], pre1[i][j + 1]);
                update(pre2[i][j], pre2[i][j + 1]);
            }
        }
        std::vector<int> ans(2 * n);
        for (int i = 1; i <= n; ++i) {
            int sum = 0;
            for (int j = 0; j <= S; ++j) {
                sum = (sum +
                       1ll * dp1[i][j] * pre2[i][S - j] % moder * fac[i] % moder * fac[n - i] % moder * fac[i] % moder *
                       fac[n - i]) % moder;
            }
            ans[2 * i - 1] = sum;
        }
        for (int i = 1; i <= n; ++i) {
            int sum = 0;
            for (int j = 0; j <= S; ++j) {
                sum = (sum +
                       1ll * dp1[i][j] * pre2[i - 1][S - j] % moder * fac[i] % moder * fac[n - i] % moder * fac[i - 1] %
                       moder * fac[n - i + 1]) % moder;
            }
            ans[2 * i - 2] = sum;
        }
        int ret = 0;
        for (int i = 1; i < 2 * n; i += 2) {
            ret = (ret + ans[i] - ans[i - 1]) % moder;
        }
        ret += ret < 0 ? moder : 0;
        return ret;
    }
};
