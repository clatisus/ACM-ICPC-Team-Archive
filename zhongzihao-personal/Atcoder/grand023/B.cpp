#include<bits/stdc++.h>

const int N = 610;

char s[N][N];
int cnt[N][N];

int calc(int x1, int y1, int x2, int y2){
    return cnt[x2][y2] - cnt[x1][y2] - cnt[x2][y1] + cnt[x1][y1];
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%s", s[i] + 1);
    }
    for (int i = 1; i <= n << 1; ++ i){
        for (int j = 1; j <= n << 1; ++ j){
            s[i][j] = s[(i - 1) % n + 1][(j - 1) % n + 1];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++ i){
        int sz = 2 * n - 1 - i;
        for (int j = 1; j <= sz; ++ j){
            for (int k = 1; k <= sz; ++ k){
                cnt[j][k] = s[j][i + k] == s[k][i + j];
            }
        }
        for (int j = 1; j <= sz; ++ j){
            for (int k = 1; k <= sz; ++ k){
                cnt[j][k] += cnt[j][k - 1];
            }
        }
        for (int k = 1; k <= sz; ++ k){
            for (int j = 1; j <= sz; ++ j){
                cnt[j][k] += cnt[j - 1][k];
            }
        }
        for (int j = 1; j <= n - i; ++ j){
           ans += calc(j - 1, j - 1, j + n - 1, j + n - 1) == n * n;
        }
    }
    for (int i = 1; i < n; ++ i){
        int sz = 2 * n - 1 - i;
        for (int j = 1; j <= sz; ++ j){
            for (int k = 1; k <= sz; ++ k){
                cnt[j][k] = s[i + j][k] == s[i + k][j];
            }
        }
        for (int j = 1; j <= sz; ++ j){
            for (int k = 1; k <= sz; ++ k){
                cnt[j][k] += cnt[j][k - 1];
            }
        }
        for (int k = 1; k <= sz; ++ k){
            for (int j = 1; j <= sz; ++ j){
                cnt[j][k] += cnt[j - 1][k];
            }
        }
        for (int j = 1; j <= n - i; ++ j){
           ans += calc(j - 1, j - 1, j + n - 1, j + n - 1) == n * n;
        }
    }
    printf("%d\n", ans);
}
