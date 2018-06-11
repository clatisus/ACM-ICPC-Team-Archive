#include<bits/stdc++.h>

typedef long long ll;

const ll N = 3010;
const ll moder = 1e9 + 7;

ll dp[N][N][2];

void add(ll &a, ll b){
    a += b;
    a -= a >= moder ? moder : 0;
    a += a < 0 ? moder : 0;
}

void addmult(ll &a, ll b, ll c){
    a = (a + 1ll * b * c) % moder;
    a += a < 0 ? moder : 0;
}

int main(){
    ll n, m;
    scanf("%lld%lld", &n, &m);
    dp[0][0][1] = 1;
    for (int i = 1; i <= n; ++ i){
       dp[0][i][0] = 1;
    }
    for (ll i = 0; i < m; ++ i){
        for (ll j = 0; j <= n; ++ j){
            if (!j){
                add(dp[i + 1][j + 1][1], dp[i][j][1]);
                add(dp[i + 1][j][1], dp[i][j][1]);
                continue;
            }
            for (int k = 0; k < 2; ++ k){
                if (j == 1){
                    add(dp[i + 1][j - 1][1], dp[i][j][k]);
                    add(dp[i + 1][j][1], dp[i][j][k]);
                    if (n > 1){
                        add(dp[i + 1][j][k], dp[i][j][k]);
                        add(dp[i + 1][j + 1][k], dp[i][j][k]);
                    }
                    continue;
                }
                if (j == n){
                    add(dp[i + 1][j - 1][k], dp[i][j][k]);
                    add(dp[i + 1][j][k], dp[i][j][k]);
                    continue;
                }
                add(dp[i + 1][j - 1][k], dp[i][j][k]);
                addmult(dp[i + 1][j][k], 2, dp[i][j][k]);
                add(dp[i + 1][j + 1][k], dp[i][j][k]);
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i <= n; ++ i){
        add(ans, dp[m][i][1]);
    }
    printf("%lld\n", ans);
    return 0;
}
