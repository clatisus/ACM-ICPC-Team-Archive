#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 2000010;

int fac[N], inv[N], invf[N];

int main(){
    fac[0] = invf[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
    int n;
    scanf("%d", &n);
    -- n;
    int sum = 0;
    for (int i = 0; i <= n; ++ i){
        sum = (sum + 1ll * inv[n - i + 1] * fac[2 * n - i] % moder * invf[i] % moder * invf[n - i] % moder * invf[n - i]) % moder;
    }
    printf("%d\n", sum);
    return 0;
}
