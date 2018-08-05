#include<bits/stdc++.h>

const __float128 eps = 1e-9;
const int N = (int) 1e5 + 10;

int x[N], y[N];
__float128 k[N], kk[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; ++ i){
        scanf("%d%d", &x[i], &y[i]);
    }
    if (1ll * (y[n] - y[n - 1]) * (x[1] - x[0]) != -1ll * (x[n] - x[n - 1]) * (y[1] - y[0])){
        puts("No");
        return 0;
    }
    for (int i = 0; i < n; ++ i){
        k[i] = 1.0 * (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    }
    __float128 sum = 0;
    for (int i = 0; i < n - 1; ++ i){
        kk[i] = (k[i + 1] - k[i]) / 2;
        sum += kk[i];
    }
    __float128 value = 0;
    for (int i = 0; i < n - 1; ++ i){
        value += kk[i] * std::abs(x[0] - x[i + 1]);
    }
    if (value - y[0] > eps || value - y[0] < -eps){
        puts("No");
        return 0;
    }
    puts("Yes");
    return 0;
}
