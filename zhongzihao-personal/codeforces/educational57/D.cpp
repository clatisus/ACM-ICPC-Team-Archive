#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;

char s[N];
int a[N];
ll dp[N][4];

void update(ll &x, ll y){
    if (y == -1){
        return;
    }
    if (x == -1 || x > y){
        x = y;
    }
}

int main(){
    int n;
    scanf("%d%s", &n, s);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < 4; ++ j){
            if (dp[i][j] == -1) continue;
            update(dp[i + 1][j], dp[i][j] + a[i]);
            int nj = j;
            if (j == 0 && s[i] == 'h'){
                nj = 1;
            }
            if (j == 1 && s[i] == 'a'){
                nj = 2;
            }
            if (j == 2 && s[i] == 'r'){
                nj = 3;
            }
            if (j == 3 && s[i] == 'd'){
                continue;
            }
            update(dp[i + 1][nj], dp[i][j]);
        }
    }
    ll ans = -1;
    for (int i = 0; i < 4; ++ i){
        update(ans, dp[n][i]);
    }
    printf("%lld\n", ans);
    return 0;
}
