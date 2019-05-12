#include <bits/stdc++.h>

typedef long long ll;
const int N = 1000010;

double dp[N], pre[N];
char s[N];

int main(){
    freopen("foreign.in", "r", stdin);
    freopen("foreign.out", "w", stdout);
    scanf("%s", s);
    int n = strlen(s);
    dp[0] = 0.0;
    ll cntC = 0, cntW = 0;
    for (int i = 1; i <= n; ++ i){
        if (s[n - i] == 'C'){
            cntC += i;
        }
        else{
            cntW += i;
        }
        dp[i] = (s[n - i] == 'C' ? cntW : cntC) + pre[i - 1];
        dp[i] /= i;
        pre[i] = pre[i - 1] + dp[i];
    }
    printf("%.15f\n", dp[n]);
    return 0;
}
