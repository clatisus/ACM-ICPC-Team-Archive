#include<bits/stdc++.h>
 
const int N = 1010;
const int moder = (int) 1e9 + 7;
 
int power[N];
int dp[N][N], p[N];
int inv100;
 
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
 
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < N; ++ i){
        power[i] = powermod(i, m);
    }
    inv100 = powermod(100, moder - 2);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &p[i]);
    }
    dp[0][0] = 1;
    int ans = 0;
    for (int i = 1; i <= n; ++ i){
        int pone = 1ll * p[i] * inv100 % moder;
        int pzero = (1 - pone + moder) % moder;
        for (int j = 1; j < i; ++ j){
            ans = (ans + 1ll * dp[i - 1][j] * pzero % moder * power[j]) % moder;
        }
        dp[i][0] = pzero;
        for (int j = 0; j < i; ++ j){
            dp[i][j + 1] = (dp[i][j + 1] + 1ll * dp[i - 1][j] * pone) % moder;
        }
    }
    for (int i = 1; i <= n; ++ i){
        ans = (ans + 1ll * dp[n][i] * power[i]) % moder;
    }
    printf("%d\n", ans);
    return 0;
}
