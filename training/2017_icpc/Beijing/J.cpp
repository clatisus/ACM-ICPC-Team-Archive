#include<bits/stdc++.h>

const int N = 110;
const int INF = 0x3f3f3f3f;

int n, l, r;
int a[N], pre[N];
int dp[N][N][N];

int getpre(int sit){
    return sit >= 0 ? pre[sit] : 0;
}

void solve(){
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
        pre[i] = (i ? pre[i - 1] : 0) + a[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int len = 1; len <= n; ++ len){
        for (int i = 0; i + len - 1 < n; ++ i){
            int j = i + len - 1;
            int x = getpre(j) - getpre(i - 1);
            if (len == 1){
                dp[i][j][1] = 0;
            }
            else if (len >= l && len <= r){
                dp[i][j][1] = x;
            }
            for (int k = 2; k <= r; ++ k){
                for (int u = i; u < j; ++ u){
                    dp[i][j][k] = std::min(dp[i][j][k], dp[i][u][k - 1] + dp[u + 1][j][1]);
                }
            }
            for (int k = l; k <= r; ++ k){
                dp[i][j][1] = std::min(dp[i][j][1], dp[i][j][k] + x);
            }
        }
    }
    printf("%d\n", dp[0][n - 1][1] == INF ? 0 : dp[0][n - 1][1]);
}

int main(){
    while (scanf("%d%d%d", &n, &l, &r) != EOF){
        solve();
    }
    return 0;
}
