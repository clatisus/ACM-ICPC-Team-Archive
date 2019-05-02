#include <bits/stdc++.h>

const int N = 210;

int c[N];
double prob[N][N], e[N][N];
double dp[N][N], dpp[N][N];
double comb[N][N];

int main(){
    for (int i = 0; i < N; ++ i){
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j){
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    int n, g, t;
    scanf("%d%d%d", &n, &g, &t);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &c[i]);
        c[i] = std::min(c[i], g);
    }
    for (int i = n; i < n + t; ++ i){
        c[i] = g;
    }
    std::sort(c, c + n + t);
    for (int len = 1; len <= n + t; ++ len){
        for (int i = 0; i < n + t; ++ i){
            int j = i + len - 1;
            if (j >= n + t){
                break;
            }
            for (int k = i; k <= j; ++ k){
                int left = (i ? c[i - 1] : 0) + 1, right = c[k];
                if (left > right){
                    continue;
                }
                double prob1 = k == i ? 1 : prob[i][k - 1], prob2 = k == j ? 1 : prob[k + 1][j];
                double e1 = k == i ? 0 : e[i][k - 1], e2 = k == j ? 0 : e[k + 1][j];
                double nprob = 1.0 * (right - left + 1) / g;
                prob[i][j] += comb[j - i][k - i] * prob1 * prob2 * nprob;
                double expvalue = k >= n ? 0 : 1.0 * (left + right) * 0.5;
                e[i][j] += comb[j - i][k - i] * (e1 * prob2 + e2 * prob1 + expvalue * prob1 * prob2) * nprob;
            }
        }
    }
    for (int i = 1; i <= n + t; ++ i){
        for (int j = 1; j <= i; ++ j){
            dp[i][j] += e[i - j][i - 1];
            dpp[i][j] += prob[i - j][i - 1];
            for (int k = 1; k <= i - j - 1; ++ k){
                for (int u = 1; u <= k; ++ u){
                    dp[i][j + u] += comb[j + u][j] * (e[i - j][i - 1] * dpp[k][u] + prob[i - j][i - 1] * dp[k][u]);
                    dpp[i][j + u] += comb[j + u][j] * prob[i - j][i - 1] * dpp[k][u];
                }
            }
        }
    }
    double ans = 0;
    for (int i = 0; i <= n + t; ++ i){
        ans += dp[i][t];
    }
    printf("%.15f\n", ans);
    return 0;
}
