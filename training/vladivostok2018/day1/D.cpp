#include<bits/stdc++.h>

const int N = 20;
typedef long long ll;

ll dp[N][N][N];
int digit[N];

bool lucky(int a){
    return a == 4 || a == 7;
}

bool almost(int a){
    return a == 3 || a == 5 || a == 6 || a == 8;
}

ll solve(ll n){
    ++ n;
    ll nn = n;
    int cnt = 0;
    while (nn){
        digit[cnt ++] = nn % 10;
        nn /= 10;
    }
    std::reverse(digit, digit + cnt);
    int cntl = 0, cnta = 0;
    ll ans = 0;
    for (int i = 1; i < cnt; ++ i){
        for (int k = 0; k < N; ++ k){
            for (int j = 0; j < N; ++ j){
                if (j >= k){
                    ans += dp[i][j][k];
                }
            }
        }
    }
    for (int i = 0; i < cnt; ++ i){
        for (int j = i ? 0 : 1; j < digit[i]; ++ j){
            if (lucky(j) || almost(j)){
                for (int k = 0; k < N; ++ k){
                    for (int u = 0; u < N; ++ u){
                        if (k + cntl + lucky(j) >= u + cnta + almost(j)){
                            ans += dp[cnt - i - 1][k][u];
                        }
                    }
                }
            }
        }
        cntl += lucky(digit[i]);
        cnta += almost(digit[i]);
        if (!lucky(digit[i]) && !almost(digit[i])){
            break;
        }
    }
    return ans;
}

int main(){
    dp[0][0][0] = 1;
    for (int i = 1; i < N; ++ i){
        for (int j = 0; j < N; ++ j){
            for (int k = 0; k < N; ++ k){
                if (j < N - 1){
                    dp[i][j + 1][k] += 2 * dp[i - 1][j][k];
                }
                if (k < N - 1){
                    dp[i][j][k + 1] += 4 * dp[i - 1][j][k];
                }
            }
        }
    }
    int test;
    scanf("%d", &test);
    while (test --){
        ll a, b;
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", solve(b) - solve(a - 1));
    }
    return 0;
}

