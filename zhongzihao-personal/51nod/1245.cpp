#include<bits/stdc++.h>

typedef long long ll;
const int N = 100;

ll digit[N];
ll dp[N][N][2];

void solve(){
    memset(dp, 0, sizeof(dp));
    ll n, p;
    scanf("%lld%lld", &n, &p);
    int cnt = 0;
    while (n){
        digit[cnt ++] = n % p;
        n /= p;
    }
    dp[0][0][0] = 1;
    for (int i = 1; i <= cnt; ++ i){
        for (int j = 0; j < N; ++ j){
            if (dp[i - 1][j][0]){
                ll x = digit[i - 1] + 1;
                dp[i][j][0] += dp[i - 1][j][0] * x;
                dp[i][j + 1][1] += dp[i - 1][j][0] * (p - x);
            }
            if (dp[i - 1][j][1]){
                ll x = digit[i - 1];
                dp[i][j][0] += dp[i - 1][j][1] * x;
                dp[i][j + 1][1] += dp[i - 1][j][1] * (p - x);
            }
        }
    }
    for (int i = 0; i < N; ++ i){
        if (dp[cnt][i][0]){
            printf("%lld ", dp[cnt][i][0]);
        }
    }
    puts("");
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
