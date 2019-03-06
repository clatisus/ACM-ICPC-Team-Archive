#include <bits/stdc++.h>

const int N = 210;
const int moder = (int) 1e9 + 7;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int dp[N][N];
int fac[N];

void solve(){
    memset(dp, 0, sizeof(dp));
    int n, a;
    scanf("%d%d", &n, &a);
    dp[0][0] = 1;
    for (int i = 1; i <= a; ++ i){
        for (int j = 0; j < i; ++ j){
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % moder;
            dp[i][j + 1] = (dp[i][j + 1] + 1ll * dp[i - 1][j] * (i - j)) % moder;
        }
    }
    int ans = 0;
    for (int i = 0; i <= a; ++ i){
        ans = (ans + (i & 1 ? -1ll : 1ll) * dp[a][i] * powermod(a - i, n - a) % moder * fac[a - i]) % moder;
    }
    ans += ans < 0 ? moder : 0;
    printf("%d\n", ans);
}

int main(){
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
