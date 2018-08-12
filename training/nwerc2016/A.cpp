#include<bits/stdc++.h>

const int N = 410;
const int M = 50;
const int K = 10;

int dp[N][M][M][K], pre[N][M][M][K];
int dppre[N][M][M][K], prepre[N][M][M][K];
char s[M][N];
char ans[M][N];
int m;

void dfs(int n, int l, int r, int col){
    if (n == m || l > r) return;
    int mincol = prepre[n][l][r][col];
    int presit = dppre[n][l][r][mincol];
    for (int i = presit; i <= r; ++ i){
        ans[i][n] = mincol + '0';
    }
    dfs(n, l, presit - 1, mincol - 1);
    dfs(n + 1, presit, r, K - 1);
}

int main(){
    int n;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i){
        scanf("%s", s[i]);
    }
    memset(dp, 0x7f, sizeof(dp));
    memset(pre, 0x7f, sizeof(pre));
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j){
            for (int k = 0; k < K; ++ k){
                dp[m][i][j][k] = pre[m][i][j][k] = 0;
            }
        }
    }
    for (int i = m - 1; i >= 0; -- i){
        for (int j = 0; j < n; ++ j){
            for (int len = 0; j + len < n; ++ len){
                dp[i][j][j + len][0] = pre[i + 1][j][j + len][K - 1];
                for (int k = j; k <= j + len; ++ k){
                    dp[i][j][j + len][0] += s[k][i] != '0';
                }
                pre[i][j][j + len][0] = dp[i][j][j + len][0];
                dppre[i][j][j + len][0] = j;
                for (int k = 1; k < K; ++ k){
                    int sum = 0;
                    auto &v = dp[i][j][j + len][k];
                    for (int u = j + len; u >= j; -- u){
                        sum += s[u][i] != k + '0';
                        int newv = sum + pre[i + 1][u][j + len][K - 1];
                        if (u > j){
                            newv += pre[i][j][u - 1][k - 1];
                        }
                        if (v > newv){
                            v = newv;
                            dppre[i][j][j + len][k] = u;
                        }
                    }
                    if (pre[i][j][j + len][k - 1] < v){
                        pre[i][j][j + len][k] = pre[i][j][j + len][k - 1];
                        prepre[i][j][j + len][k] = prepre[i][j][j + len][k - 1];
                    }
                    else{
                        pre[i][j][j + len][k] = v;
                        prepre[i][j][j + len][k] = k;
                    }
                }
            }
        }
    }
    //printf("%d\n", pre[0][0][n - 1][K - 1]);
    dfs(0, 0, n - 1, K - 1);
    for (int i = 0; i < n; ++ i){
        puts(ans[i]);
    }
    return 0;
}
