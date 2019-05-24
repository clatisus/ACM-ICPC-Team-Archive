//
// Created by zzh on 2019/3/19.
//

#include <bits/stdc++.h>

using LL = long long;

const int max_N = (int) 1e5 + 21;
const int max_M = 121;

int n, m;

char s[max_N], t[max_M];

LL dp[max_N][max_M], ans;

int main() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            LL tmp = dp[i - 1][j];
            if (!tmp) continue;
            int a = j < m ? (j + (s[i] == t[j + 1])) : m;
            dp[i][a] += tmp;
        }
        int b = (s[i] == t[1]);
        ++dp[i][b];
        ans += dp[i][m];
    }
    printf("%lld\n", ans);
}
/*
abcdefghijklmnopqrstuvwxyz
a

abcdefghijklmnopqrstuvwxyz
m

penpineappleapplepen
ppap
 */