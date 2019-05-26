#include <bits/stdc++.h>

const long double eps = 1e-9;
const int N = 1010;

inline int sig(long double p){return (p > eps) - (p < -eps);}

long double mat[N][N];
long double r[N];
long double p[N][N];
int sit[N];
long double value[N];

int main(){
    int y, c, q;
    scanf("%d%d%d", &y, &c, &q);
    int n = 0, m = c + c + y - 1;
    for (int i = 1; i < y; ++ i){
        scanf("%Lf", &r[i]);
        if (r[i] > 0){
            mat[n][c + c + i - 1] = 1;
            mat[n][m] = std::log(r[i]);
            ++ n;
        }
    }
    for (int i = 1; i <= y; ++ i){
        for (int j = 1; j <= c; ++ j) {
            scanf("%Lf", &p[i][j]);
            if (p[i][j] > 0){
                mat[n][j - 1] = 1;
                mat[n][c + j - 1] = i - 1;
                for (int k = 1; k < i; ++ k){
                    mat[n][2 * c + k - 1] = 1;
                }
                mat[n][m] = std::log(p[i][j]);
                ++ n;
            }
        }
    }
    int now = 0;
    memset(sit, -1, sizeof(sit));
    for (int i = 0; i < m; ++ i){
        long double max = 0;
        int sit = -1;
        for (int j = now; j < n; ++ j){
            if (std::abs(mat[j][i]) > max){
                max = std::abs(mat[j][i]);
                sit = j;
            }
        }
        if (!sig(max)){
            continue;
        }
        for (int k = i; k <= m; ++ k){
            std::swap(mat[sit][k], mat[now][k]);
        }
        ::sit[i] = now;
        for (int j = m; j >= i; -- j){
            mat[now][j] /= mat[now][i];
        }
        for (int j = 0; j < n; ++ j){
            if (j == now) continue;
            for (int k = m; k >= i; -- k){
                mat[j][k] -= mat[j][i] * mat[now][k];
            }
        }
        ++ now;
    }
    while (q --){
        int a, b;
        scanf("%d%d", &a, &b);
        memset(value, 0, sizeof(value));
        value[a - 1] = 1;
        value[c + a - 1] = b - 1;
        for (int i = 1; i < b; ++ i){
            value[2 * c + i - 1] = 1;
        }
        bool flag = true;
        long double ans = 0;
        for (int i = 0; i < m; ++ i){
            if (sig(value[i])){
                if (sit[i] == -1){
                    flag = false;
                    puts("-1.0");
                    break;
                }
                ans += value[i] * mat[sit[i]][m];
                for (int j = m - 1; j >= i; -- j){
                    value[j] -= value[i] * mat[sit[i]][j];
                }
            }
        }
        if (flag){
            printf("%.15Lf\n", std::exp(ans));
        }
    }
}
