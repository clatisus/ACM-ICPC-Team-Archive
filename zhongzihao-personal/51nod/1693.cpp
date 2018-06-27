#include<bits/stdc++.h>

const int N = (int) 1e6 + 10;
const int MAX = 50;

int dp[N];

int main(){
    memset(dp, 0x7f, sizeof(dp));
    dp[1] = 0;
    for (int i = 1; i < N; ++ i){
        for (int j = 2; j <= MAX; ++ j){
            int y = i * j;
            if (y >= N + MAX) break;
            int x = dp[i] + j;
            if (x >= MAX) break;
            for (int k = 0, sz = std::min(MAX + 1, j); k < sz; ++ k){
                int z = y - k;
                if (z >= N) continue;
                int u = x + k;
                if (u >= MAX) break;
                dp[z] = std::min(dp[z], u);
            }
        }
    }
    int max = 0;
    for (int i = 1; i < N; ++ i){
        max = std::max(max, dp[i]);
    }
    //printf("%d\n", max);
    int n;
    scanf("%d", &n);
    printf("%d\n", dp[n]);
    return 0;
}
