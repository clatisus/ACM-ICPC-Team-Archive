#include<bits/stdc++.h>

typedef long double ld;
const int N = 60;
const ld eps = 1e-9;

inline int sig(ld x){return (x > eps) - (x < -eps);}
template <typename T> T sqr(T x){return x * x;}

ld ans[N][N];
int d[N][N];
int x[N], y[N], z[N];
int first[N];

void solve(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n - i - 1; ++ j){
            scanf("%d", &d[i][i + j + 1]);
            d[i][i + j + 1] -= sqr(x[i] - x[i + j + 1]) + sqr(y[i] - y[i + j + 1]) + sqr(z[i] - z[i + j + 1]);
            d[i + j + 1][i] = d[i][i + j + 1];
        }
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j){
            if (d[i][j] < 0){
                puts("Goodbye World!");
                return;
            }
        }
    }
    int m = 0; 
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            ld sum = (d[i][0] + d[first[j]][0] - d[first[j]][i]) / 2.0;
            for (int k = 0; k < j; ++ k){
                sum -= ans[i][k] * ans[first[j]][k];
            }
            ans[i][j] = sum / ans[first[j]][j];
        }
        for (int j = 1; j < i; ++ j){
            ld sum = (d[i][0] + d[j][0] - d[i][j]) / 2.0;
            for (int k = 0; k < m; ++ k){
                sum -= ans[i][k] * ans[j][k];
            }
            if (sig(sum)){
                puts("Goodbye World!");
                return;
            }
        }
        ld sum = d[i][0];
        for (int j = 0; j < m; ++ j){
            sum -= sqr(ans[i][j]);
        }
        if (sig(sum) < 0){
            puts("Goodbye World!");
            return;
        }
        if (sig(sum) > 0){
            first[m] = i;
            ans[i][m ++] = std::sqrt(sum);
        }
    }
    printf("%d\n", m + 3);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
