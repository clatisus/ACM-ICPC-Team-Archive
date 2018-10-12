#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 110;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int h[N], c[N];
int dp[N][N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &h[i]);
        c[i + 1] = h[i];
    }
    std::sort(c, c + n + 1);
    int cnt = std::unique(c, c + n) - c;
    for (int i = cnt - 1; i >= 0; -- i){
        if (c[i] > h[0]){
            continue;
        }
        dp[0][i] = powermod(2, std::min(h[0] - c[i] + 1, h[0]));
    }
    for (int i = 0; i < cnt; ++ i){
        dp[0][i] -= dp[0][i + 1];
        dp[0][i] += dp[0][i] < 0 ? moder : 0;
    }
    for (int i = 1; i < n; ++ i){
        dp[i][0] = 1ll * powermod(2, h[i] - h[i - 1]) * dp[i - 1][0] % moder;
        int sit = std::lower_bound(c, c + cnt, h[i]) - c;
        for (int j = 1; j < N; ++ j){
            if (c[j] > h[i - 1]) break;
            if (c[j] == h[i - 1] && h[i - 1] < h[i]){
                for (int k = cnt - 1; k >= j; -- k){
                    if (c[k] > h[i]) continue;
                    dp[i][k] = (dp[i][k] + 1ll * powermod(2, h[i] - c[k] + 1) * dp[i - 1][j]) % moder;
                    dp[i][k] += dp[i][k] < 0 ? moder : 0;
                }
                for (int k = j; k < cnt; ++ k){
                    dp[i][k] -= dp[i][k + 1];
                    dp[i][k] += dp[i][k] < 0 ? moder : 0;
                }
                continue;
            }
            if (c[j] < h[i]){
                dp[i][j] = (dp[i][j] + 1ll * powermod(2, h[i] - h[i - 1]) * dp[i - 1][j]) % moder;
            }
            else{
                auto &u = dp[i][std::min(j, sit)];
                u = (u + 2ll * powermod(2, h[i] - h[i - 1]) * dp[i - 1][j]) % moder;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < N; ++ i){
        ans += dp[n - 1][i];
        ans -= ans >= moder ? moder : 0;
    }
    printf("%d\n", ans);
    return 0;
}
