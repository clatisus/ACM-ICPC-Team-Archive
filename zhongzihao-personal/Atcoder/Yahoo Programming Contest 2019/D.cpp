#include<bits/stdc++.h>

const int N = 200010;
typedef long long ll;

ll dp[N][5];
int a[N];

void update(ll &a, ll b){
    if (a == -1 || a > b){
        a = b;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
    }
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n + 1; ++ i){
        for (int j = 0; j <= 0; ++ j){
            if (dp[i - 1][j] != -1){
                update(dp[i][0], dp[i - 1][j] + a[i]);
            }
        }
        for (int j = 0; j <= 1; ++ j){
            if (dp[i - 1][j] != -1){
                update(dp[i][1], dp[i - 1][j] + (a[i] == 0 ? 2 : a[i] & 1));
            }
        }
        for (int j = 0; j <= 2; ++ j){
            if (dp[i - 1][j] != -1){
                update(dp[i][2], dp[i - 1][j] + !(a[i] & 1));
            }
        }
        for (int j = 0; j <= 3; ++ j){
            if (dp[i - 1][j] != -1){
                update(dp[i][3], dp[i - 1][j] + (a[i] == 0 ? 2 : a[i] & 1));
            }
        }
        for (int j = 0; j <= 4; ++ j){
            if (dp[i - 1][j] != -1){
                update(dp[i][4], dp[i - 1][j] + a[i]);
            }
        }
    }
    printf("%lld\n", dp[n + 1][4]);
    return 0;
}
