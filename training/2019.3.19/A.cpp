#include <bits/stdc++.h>

const int N = 3010;

long double x[N], y[N];
long double fac[N];

long double cross(long double x1, long double y1, long double x2, long double y2){
    return x1 * y2 - y1 * x2;
}

long double comb(int n, int m){
    return fac[n] - fac[m] - fac[n - m];
}

int main(){
    for (int i = 1; i < N; ++ i){
        fac[i] = fac[i - 1] + std::log(i);
    }
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++ i){
        scanf("%Lf%Lf", &x[i], &y[i]);
    }
    long double ans = 0;
    for (int i = 0; i < n; ++ i){
        for (int j = i + 1; j < i + n; ++ j){
            if (n - (j - i + 1) < k - 2){
                continue;
            }
            ans += cross(x[i], y[i], x[j % n], y[j % n]) * std::exp(comb(n - (j - i + 1), k - 2) - comb(n, k));
        }
    }
    printf("%.15Lf\n", ans * -0.5);
    return 0;
}
