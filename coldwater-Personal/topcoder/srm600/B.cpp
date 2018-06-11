#include <bits/stdc++.h>

#define MAXN (20)

class PalindromeMatrix
{
    int n, m;
    int a[MAXN][MAXN];
    int c[2][2];
    int f[MAXN][MAXN];
    int cost[MAXN][3];

    int sub2x2(int x0, int x1, int y0, int y1) {
        int o = 0;
        for (int i = 0; i < 2; ++ i) {
            for (int j = 0; j < 2; ++ j) {
                o += c[i][j];
            }
        }
        // all connected
        if (x0 + x1 + y0 + y1 >= 3) return std::min(o, 4 - o);
        if (x0 && y0) {
            o -= c[1][1];
            return std::min(o, 3 - o);
        }
        if (x0 && y1) {
            o -= c[1][0];
            return std::min(o, 3 - o);
        }
        if (x1 && y0) {
            o -= c[0][1];
            return std::min(o, 3 - o);
        }
        if (x1 && y1) {
            o -= c[0][0];
            return std::min(o, 3 - o);
        }
        int ret = 0;
        if (x0) ret += c[0][0] != c[0][1];
        if (x1) ret += c[1][0] != c[1][1];
        if (y0) ret += c[0][0] != c[1][0];
        if (y1) ret += c[0][1] != c[1][1];
        return ret;
    }

    int solve(int rc, int mask) {
        for (int i = 0; i < n / 2; ++ i) {
            for (int j = 0; j < 3; ++ j) {
                cost[i][j] = m + m;
            }
            for (int x0 = 0; x0 < 2; ++ x0) {
                for (int x1 = 0; x1 < 2; ++ x1) {
                    int now = 0;
                    for (int j = 0; j < m / 2; ++ j) {
                        int y0 = (mask >> j) & 1;
                        int y1 = (mask >> (m - j - 1)) & 1;
                        c[0][0] = a[i][j];
                        c[0][1] = a[i][m - j - 1];
                        c[1][0] = a[n - i - 1][j];
                        c[1][1] = a[n - i - 1][m - j - 1];
                        now += sub2x2(x0, x1, y0, y1);
                    }
                    cost[i][x0 + x1] = std::min(cost[i][x0 + x1], now);
                }
            }
        }

        f[0][0] = 0;
        for (int j = 1; j <= rc; ++ j) f[0][j] = n * m;
        for (int i = 1; i <= n / 2; ++ i) {
            for (int j = 0; j <= rc; ++ j) {
                f[i][j] = n * m;
                for (int k = 0; k < 3 && k <= j; ++ k) {
                    f[i][j] = std::min(f[i][j], f[i - 1][j - k] + cost[i - 1][k]);
                }
            }
        }

        return f[n / 2][rc];
    }

public:
    int minChange(std::vector<std::string> A, int rc, int cc) {
        n = (int)(A.size());
        m = (int)(A[0].length());

        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                a[i][j] = A[i][j] - '0';
            }
        }

        int ans = INT_MAX;
        for (int s = 0; s < (1 << m); ++ s) {
            if (__builtin_popcount(s) != cc) continue;
            ans = std::min(ans, solve(rc, s));
        }

        return ans;
    }
};

int main()
{
    PalindromeMatrix run;
    printf("%d\n", run.minChange(
                {"11111101001110"
                ,"11000111111111"
                ,"00010101111001"
                ,"10110000111111"
                ,"10000011010010"
                ,"10001101101101"
                ,"00101010000001"
                ,"10111010100100"
                ,"11010011110111"
                ,"11100010110110"
                ,"00100101010100"
                ,"01001011001000"
                ,"01010001111010"
                ,"10100000010011"},
                6,
                8
            ));
    return 0;
}
