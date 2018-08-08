#include <bits/stdc++.h>

const int max_N = 2000 + 21;
const int mod = (int) 1e9 + 7;

int T, n, k, dp[4][4][max_N][max_N], fac[max_N], inv[max_N], r[max_N];
//dp[bit(n)bit(1)][bit(i + 1)bit(i)][i][j]

void add(int &x, int y) {
    if ((x += y) >= mod) x -= mod;
}

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % mod;
        }
        a = 1ll * a * a % mod;
    }
    return ret;
}

int comb(int n, int m){
    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

void init(int n) {
    fac[0] = inv[0] = 1;
    for (int i = 1; i < max_N; ++i) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
        inv[i] = powermod(fac[i], mod - 2);
    }
    //initial 1
    dp[0][0][1][0] = dp[2][0][1][1] = dp[1][1][1][1] = dp[0][2][1][1] = 1;
    //transfer 2
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int a = 0; a < 4; ++a) {
                for (int b = 0; b < 4; ++b) {
                    int tmp = dp[a][b][i][j];
                    if (!tmp) continue;
                    //do not choose
                    add(dp[a][b >> 1][i + 1][j], tmp);
                    //choose i
                    if (!(b & 1)) {
                        if (i == 1) add(dp[a | 1][b >> 1][i + 1][j + 1], tmp);
                        else add(dp[a][b >> 1][i + 1][j + 1], tmp);
                    }
                    //choose i + 1
                    if (!(b & 2)) {
                        add(dp[a][1][i + 1][j + 1], tmp);
                    }
                    //choose i + 2
                    add(dp[a][2 | (b >> 1)][i + 1][j + 1], tmp);
                }
            }
        }
    }
}

void testCase() {
    static int caseID = 0;
    scanf("%d%d", &n, &k);
    for (int j = 0; j <= n; ++j) {
        r[j] = 0;
        for (int a = 0; a < 4; ++a)
            for (int b = 0; b < 4; ++b) {
                if ((a & 1) && (b & 2)) continue;
                if ((a & 2) && (b & 1)) continue;
                add(r[j], dp[a][b][n][j]);
            }
        //printf("r[%d] = %d\n", j, r[j]);
    }
    int ans = 0;
    for (int i = k; i <= n; ++ i){
        int sum = 0;
        for (int j = i; j <= n; ++ j){
            sum = (sum + (j - i & 1 ? -1ll : 1ll) * r[j] * fac[n - j] % mod * comb(j, i)) % mod;
            sum += sum < 0 ? mod : 0;
        }
        ans += sum;
        ans -= ans >= mod ? mod : 0;
    }
    printf("Case %d: %d\n", ++caseID, ans);
}

int main() {
    init(2000);
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
