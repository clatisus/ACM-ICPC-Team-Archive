#include <bits/stdc++.h>

const int MAXN = (1 << 13) + 10;
const int MAXS = 1594323 + 10;
const int inf = 0x3f3f3f3f;

int n, k;
bool vis[MAXN], no[MAXS];
int dp[MAXS], pow3[20];

void update(int &u, int v1, int v2) {
    if (v1 == inf && v2 == inf) return;
    if (v1 != inf && v2 == inf) u = std::min(u, v1);
    if (v1 == inf && v2 != inf) u = std::min(u, v2);
    if (v1 != inf && v2 != inf) u = std::min(u, std::max(v1, v2) + 1);

}

int debug = 0;

int main() {
    auto t = clock();
    int T;
    if (debug) {
        T = 20;
    }
    else scanf("%d", &T);
    pow3[0] = 1;
    for (int i = 1; i <= 14; ++i) {
        pow3[i] = pow3[i - 1] * 3;
    }
    while (T--) {
        if (debug) n = 1 << 13, k = 13;
        else scanf("%d%d", &n, &k);
        for (int i = 0; i < (1 << k); ++i) {
            vis[i] = false;
        }
        static char s[30];
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            if (!debug) scanf("%s", s);
            int now = 0;
            int now3 = 0;
            for (int j = 0; j < k; ++j) {
                if (debug) {
                    now |= (1 << j) * (((i - 1) >> (k - 1 - j)) & 1);
                    now3 |= pow3[j] * (((i - 1) >> (k - 1 - j)) & 1);
                } else {
                    now |= (1 << j) * (s[k - 1 - j] - '0');
                    now3 += pow3[j] * (s[k - 1 - j] - '0');
                }
            }
            vis[now] = true;
            dp[now3] = 0;
        }

        memset(no, 0, sizeof(no));
        for (int i = 0; i < (1 << k); ++i) {
            if (vis[i]) continue;
            int now3 = 0;
            for (int j = 0; j < k; ++j) {
                if ((i >> j) & 1) {
                    now3 += pow3[j];
                }
            }
            no[now3] = true;
        }

        for (int s = 0; s < pow3[k]; ++s) {
            if (dp[s] != inf || no[s]) continue;
            int ss = s;
            for (int i = 0; i < 13; ++i) {
                int c = ss % 3; ss /= 3;
                if (c == 2) {
                    int s1 = s - pow3[i], s2 = s1 - pow3[i];
                    update(dp[s], dp[s1], dp[s2]);
                }
            }
        }
        printf("%d\n", dp[pow3[k] - 1]);
    }
    if (debug) printf("%f\n", 1.0 * (clock() - t) / CLOCKS_PER_SEC);
    return 0;
}

/*
1
4 3
000
100
010
011

*/