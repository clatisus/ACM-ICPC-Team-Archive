#include<bits/stdc++.h>

const int N = 1010;

char s[N];
int d;
bool dp[N][N];
int power[N];

void solve(){
    power[0] = 1;
    for (int i = 1; i < N; ++ i){
        power[i] = power[i - 1] * 10 % d;
    }
    int n = strlen(s);
    memset(dp, 0, sizeof(dp));
    dp[n][0] = true;
    for (int i = n - 1, now = 1; i >= 0; -- i){
        int left = !i, right = 9;
        if (s[i] != '?'){
            left = right = s[i] - '0';
        }
        for (int j = left; j <= right; ++ j){
            for (int k = 0; k < d; ++ k){
                if (!dp[i + 1][k]) continue;
                dp[i][(j * now + k) % d] = true;
            }
        }
        now = now * 10 % d;
    }
    if (!dp[0][0]){
        puts("*");
        return;
    }
    for (int i = 0, prev = 0; i < n; ++ i){
        if (s[i] == '?'){
            int left = !i, right = 9;
            for (int j = left; j <= right; ++ j){
                int x = (prev + j * power[n - i - 1]) % d;
                x = x ? d - x : 0;
                if (dp[i + 1][x]){
                    s[i] = j + '0';
                    break;
                }
            }
        }
        prev = (prev + (s[i] - '0') * power[n - i - 1]) % d;
    }
    puts(s);
}

int main(){
    while (scanf("%s%d", s, &d) != EOF){
        solve();
    }
    return 0;
}

