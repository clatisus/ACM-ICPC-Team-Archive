#include<bits/stdc++.h>

const int N = 60;
const int moder = 1e9 + 7;

char a[N], b[N], c[N];
int dp[N][2];

int main(){
    scanf("%s%s%s", a + 1, b + 1, c + 1);
    int n = strlen(a + 1);
    std::reverse(a + 1, a + 1 + n);
    std::reverse(b + 1, b + 1 + n);
    std::reverse(c + 1, c + 1 + n);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++ i){
        for (int j = 0; j < 2; ++ j){
            int abegin, aend;
            if (a[i] == '?'){
                abegin = 0;
                aend = 9;
            }
            else{
                abegin = aend = a[i] - '0';
            }
            if (i == n){
                abegin = std::max(abegin, 1);
            }
            for (int u = abegin; u <= aend; ++ u){
                int bbegin, bend;
                if (b[i] == '?'){
                    bbegin = 0;
                    bend = 9;
                }
                else{
                    bbegin = bend = b[i] - '0';
                }
                if (i == n){
                    bbegin = std::max(bbegin, 1);
                }
                for (int v = bbegin; v <= bend; ++ v){
                    int carry = u + v + j >= 10;
                    int digit = (u + v + j) % 10;
                    if (c[i] != '?' && digit != c[i] - '0') continue;
                    int &w = dp[i][carry];
                    w += dp[i - 1][j];
                    w -= w >= moder ? moder : 0;
                }
            }
        }
    }
    printf("%d\n", dp[n][0]);
    return 0;
}
