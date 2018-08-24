#include<bits/stdc++.h>

typedef long long ll;
const int N = 30;
const int M = 1 << 15;

int a[N], cnt[N];
ll dp[N][M][N];

int main(){
    int n;
    scanf("%d", &n);
    bool flag = true;
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
        if (a[i]){
            if (a[i] <= n >> 1){
                if (!(i & 1)){
                    flag = false;
                }
                ++ cnt[a[i]];
            }
            else{
                if (i & 1){
                    flag = false;
                }
            }
        }
    }
    if (!flag){
        puts("0");
        return 0;
    }
    for (int i = 1; i <= n; ++ i){
        cnt[i] += cnt[i - 1];
    }
    dp[n >> 1][0][0]= 1;
    for (int i = (n + 1) >> 1; i <= n; ++ i){
        int left = 0, right = n - 1;
        for (int j = 0; j < n; ++ j){
            if (a[j] == i){
                left = right = j;
            }
        }
        for (int j = left; j <= right; j += 2){
            for (int k = 0; k < 1 << ((n + 1) >> 1); ++ k){
                if (k >> (j >> 1) & 1) continue;
                for (int u = 0; u <= n; ++ u){
                    if (!dp[i - 1][k][u]) continue;
                    int state = k | 1 << (j >> 1), used = u, coe = 1;
                    if (j && !(k >> ((j - 2) >> 1) & 1)){
                        if (a[j - 1] && a[j - 1] > i >> 1){
                            coe = 0;
                        }
                        if (!a[j - 1]){
                            int possible = (i >> 1) - cnt[i >> 1] - used;
                            if (possible <= 0){
                                coe = 0;
                            }
                            else{
                                coe *= possible;
                                ++ used;
                            }
                        }
                    }
                    if (j < n - 1 && !(k >> ((j + 2) >> 1) & 1)){
                        if (a[j + 1] && a[j + 1] > i >> 1){
                            coe = 0;
                        }
                        if (!a[j + 1]){
                            int possible = (i >> 1) - cnt[i >> 1] - used;
                            if (possible <= 0){
                                coe = 0;
                            }
                            else{
                                coe *= possible;
                                ++ used;
                            }
                        }
                    }
                    dp[i][state][used] += dp[i - 1][k][u] * coe;
                }
            }
        }
    }
    printf("%lld\n", dp[n][(1 << ((n + 1) >> 1)) - 1][(n >> 1) - cnt[n]]);
    return 0;
}
