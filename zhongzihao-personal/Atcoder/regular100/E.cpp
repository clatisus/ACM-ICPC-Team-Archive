#include<bits/stdc++.h>

const int BIT = 18;
const int MAX = 1 << BIT;
typedef std::pair <int, int> pii;

int ans[MAX];
int a[MAX];
int dp[MAX][BIT + 1][2];

pii calc(int a, int b, int c, int d){
    std::vector <int> vec = {a, b, c, d};
    std::sort(vec.begin(), vec.end(), std::greater <int>());
    return {vec[0], vec[1]};
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 1 << n; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < 1 << n; ++ i){
        dp[i][0][1] = a[i];
        for (int j = 1; j <= n; ++ j){
            if (!(i >> j - 1 & 1)){
                dp[i][j][0] = dp[i][j - 1][0];
                dp[i][j][1] = dp[i][j - 1][1];
            }
            else{
                pii p = calc(dp[i][j - 1][0], dp[i][j - 1][1], dp[i ^ 1 << j - 1][j - 1][0], dp[i ^ 1 << j - 1][j - 1][1]);
                dp[i][j][1] = p.first;
                dp[i][j][0] = p.second;
            }
        }
    }
    for (int i = 1; i < 1 << n; ++ i){
        ans[i] = std::max(ans[i - 1], dp[i][n][0] + dp[i][n][1]);
        printf("%d\n", ans[i]);
    }
    return 0;
}
