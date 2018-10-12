#include<bits/stdc++.h>

const int N = 5010;
const int moder = (int) 1e9 + 7;

int f[N][N], g[N][N];
char s[N];

void addmult(int &a, int b, int c){
    a = (a + 1ll * b * c) % moder;
}

int main(){
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    if (n == 1){
        puts("1");
        return 0;
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; ++ i){
        if (s[i] == '<'){
            for (int j = 1; j < N; ++ j){
                addmult(f[i][j], f[i - 1][j], j);
            }
            for (int j = 1; j < N - 1; ++ j){
                addmult(f[i][j], f[i - 1][j + 1], j);
            }
        }
        else{
            for (int j = 1; j < N; ++ j){
                addmult(f[i][j], f[i - 1][j - 1], j);
            }
            for (int j = 0; j < N; ++ j){
                addmult(f[i][j], f[i - 1][j], j);
            }
        }
    }
    g[n + 1][0] = 1;
    for (int i = n; i >= 1; -- i){
        if (s[i] == '>'){
            for (int j = 1; j < N; ++ j){
                addmult(g[i][j], g[i + 1][j], j);
            }
            for (int j = 1; j < N - 1; ++ j){
                addmult(g[i][j], g[i + 1][j + 1], j);
            }
        }
        else{
            for (int j = 1; j < N; ++ j){
                addmult(g[i][j], g[i + 1][j - 1], j);
            }
            for (int j = 0; j < N; ++ j){
                addmult(g[i][j], g[i + 1][j], j);
            }
        }
    }
    for (int i = 1; i <= n; ++ i){
        int sum = 0;
        for (int j = 1; j < N; ++ j){
            addmult(sum, f[i - 1][j] << 1, g[i + 1][j]);
        }
        for (int j = 1; j < N; ++ j){
            addmult(sum, f[i - 1][j], g[i + 1][j - 1]);
            addmult(sum, f[i - 1][j - 1], g[i + 1][j]);
        }
        printf("%d%c", sum, " \n"[i == n]);
    }
    return 0;
}
