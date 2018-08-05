#include<bits/stdc++.h>

const int moder = (int) 1e9 + 7;
const int N = 1000010;
const int M = 53;

int toid(char ch){
    return islower(ch) ? ch - 'a' : ch - 'A' + 26;
}

char s[N];
int pre[N][M], suf[N][M];
int tmp[M][M], tmp2[M][M];

void add(int &a, int b){
    a += b;
    a -= a >= moder ? moder : 0;
}

void sub(int &a, int b){
    a -= b;
    a += a < 0 ? moder : 0;
}

void init(int n){
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < M; ++ i){
        tmp[i][i] = 1;
    }
    for (int i = 0; i <= n; ++ i){
        for (int j = 0; j < M; ++ j){
            pre[i][j] = tmp[M - 1][j];
        }
        if (i < n){
            int x = toid(s[i]);
            for (int j = 0; j < M; ++ j){
                sub(tmp2[x][j], tmp[x][j]);
                sub(tmp2[M - 1][j], tmp[x][j]);
                add(tmp2[x][j], tmp[M - 1][j]);
                add(tmp2[M - 1][j], tmp[M - 1][j]);
            }
            for (int j = 0; j < M; ++ j){
                add(tmp[x][j], tmp2[x][j]);
                add(tmp[M - 1][j], tmp2[M - 1][j]);
                tmp2[x][j] = tmp2[M - 1][j] = 0;
            }
        }
    }
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < M; ++ i){
        tmp[i][i] = 1;
    }
    for (int i = 0; i <= n; ++ i){
        for (int j = 0; j < M; ++ j){
            suf[i][j] = tmp[j][M - 1];
        }
        if (i < n){
            int x = toid(s[i]);
            for (int j = 0; j < M; ++ j){
                add(tmp2[j][x], tmp[j][x]);
                add(tmp2[j][x], tmp[j][M - 1]);
                sub(tmp2[j][M - 1], tmp[j][x]);
                sub(tmp2[j][M - 1], tmp[j][M - 1]);
            }
            for (int j = 0; j < M; ++ j){
                add(tmp[j][x], tmp2[j][x]);
                add(tmp[j][M - 1], tmp2[j][M - 1]);
                tmp2[j][x] = tmp2[j][M - 1] = 0;
            }
        }
    }
}

int main(){
    fgets(s, N, stdin);
    int n = strlen(s);
    s[-- n] = '\0';
    init(n);
    int Q, a0, b0, p, q, r;
    scanf("%d%d%d%d%d%d", &Q, &a0, &b0, &p, &q, &r);
    int z = 0;
    while (Q --){
        int a1 = (1ll * p * a0 + 1ll * q * b0 + z + r) % moder;
        int b1 = (1ll * p * b0 + 1ll * q * a0 + z + r) % moder;
        a0 = a1, b0 = b1;
        int x = a0 % n + 1;
        int y = b0 % n + 1;
        if (x > y){
            std::swap(x, y);
        }
        z = 0;
        for (int i = 0; i < M; ++ i){
            z = (z + 1ll * suf[x - 1][i] * pre[y][i]) % moder;
        }
    }
    printf("%d\n", z);
    return 0;
}
