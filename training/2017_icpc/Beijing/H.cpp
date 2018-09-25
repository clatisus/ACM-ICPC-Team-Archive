#include <bits/stdc++.h>

#define MAXN (200)

int n, m, P;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int c[MAXN][MAXN];
int tmp[MAXN];
int pr[MAXN], sr[MAXN];
int pc[MAXN], sc[MAXN];
int max;

int main() {
    while (~scanf("%d%d%d", &n, &m, &P)) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", a[i] + j);
                b[i][j] = b[i - 1][j] + a[i][j];
                c[i][j] = c[i][j - 1] + a[i][j];
            }
        }
        max = INT_MIN;
        for (int i = 0; i <= n + 1; ++i) pr[i] = sr[i] = INT_MIN;
        for (int i = 0; i <= m + 1; ++i) pc[i] = sc[i] = INT_MIN;

        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                for (int k = 1; k <= m; ++k) {
                    tmp[k] = b[j][k] - b[i - 1][k];
                }
                int pre = 0;
                for (int k = 1; k <= m; ++k) {
                    pre = std::max(0, pre) + tmp[k];
                    max = std::max(max, pre);
                    pr[j] = std::max(pr[j], pre);
                    sr[i] = std::max(sr[i], pre);
                }
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; ++j) {
                for (int k = 1; k <= n; ++k) {
                    tmp[k] = c[k][j] - c[k][i - 1];
                }
                int pre = 0;
                for (int k = 1; k <= n; ++k) {
                    pre = std::max(0, pre) + tmp[k];
                    pc[j] = std::max(pc[j], pre);
                    sc[i] = std::max(sc[i], pre);
                }
            }
        }

        for (int i = 2; i <= n; ++i) pr[i] = std::max(pr[i], pr[i - 1]);
        for (int i = n - 1; i; --i) sr[i] = std::max(sr[i], sr[i + 1]);
        for (int j = 2; j <= m; ++j) pc[j] = std::max(pc[j], pc[j - 1]);
        for (int j = m - 1; j; --j) sc[j] = std::max(sc[j], sc[j + 1]);

        int ans = max;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int now = INT_MIN;
                if (i) now = std::max(now, pr[i - 1]);
                if (i != n) now = std::max(now, sr[i + 1]);
                if (j) now = std::max(now, pc[j - 1]);
                if (j != m) now = std::max(now, sc[j + 1]);

                if (now != max) {
                    ans = std::min(ans, std::max(max - a[i][j] + P, now));
                }
            }
        }
        printf("%d\n", ans);

    }
    return 0;
}

