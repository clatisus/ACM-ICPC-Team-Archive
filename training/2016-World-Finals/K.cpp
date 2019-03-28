#include <bits/stdc++.h>

const int N = 105;

bool dp[N * N][N][2];
int most[N * N];
int a[N];
int cnt = 0;

bool solve(int r){
    dp[r][r][0] = true;
    for (int i = r; i < cnt; ++ i){
        int max = most[i];
        for (int j = 1; j <= r; ++ j){
            if (j == 1){
                if (dp[i][j][0]) {
                    dp[i + 1][j + 1][1] = true;
                }
            }
            else{
                if (j - 1 > max){
                    break;
                }
                if (dp[i][j][0] || dp[i][j][1]) {
                    dp[i + j - 1][j - 1][0] = true;
                }
                if (j <= max && dp[i][j][1]){
                    dp[i + j][j + 1][1] = true;
                }
            }
        }
    }
    return dp[cnt][r + 1][1];
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < a[i]; ++ j){
            most[cnt ++] = a[i] - j;
        }
    }
    for (int i = a[0]; i >= 1; -- i){
        memset(dp, 0, sizeof(dp));
        if (solve(i)){
            printf("%d\n", i);
            return 0;
        }
    }
    puts("no quotation");
    return 0;
}
