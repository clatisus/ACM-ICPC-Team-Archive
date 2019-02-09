#include<bits/stdc++.h>

const int N = 4010;
const int moder = 998244353;

int dp[N][N];
char s[N];
int a[N], idr[N], idb[N];

void add(int &a, int b){a += b; a -= a >= moder ? moder : 0;}

int main(){
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 1; i <= n; ++ i){
        a[i] = s[i - 1] - '0';
    }
    int cntr = 0, cntb = 0;
    memset(idr, -1, sizeof(idr));
    memset(idb, -1, sizeof(idb));
    for (int i = 1; i <= n; ++ i){
        for (int j = 0; j < 2 - a[i]; ++ j){
            idr[++ cntr] = i;
        }
        for (int j = 0; j < a[i]; ++ j){
            idb[++ cntb] = i;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= 2 * n; ++ i){
        for (int j = 0; j <= i - 1; ++ j){
            if (!dp[i - 1][j]) continue;
            int x = j + 1;
            if (idr[x] != -1 && idr[x] <= i){
                add(dp[i][j + 1], dp[i - 1][j]);
            }
            x = (i - 1 - j) + 1;
            if (idb[x] != -1 && idb[x] <= i){
                add(dp[i][j], dp[i - 1][j]);
            }
        }
    }
    printf("%d\n", dp[2 * n][cntr]);
    return 0;
}
