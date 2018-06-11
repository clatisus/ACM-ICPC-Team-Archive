#include<bits/stdc++.h>

const int N = 1000010;
const int moder = 1e9 + 7;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int fac[N];
int inv[N];
int ans[N];

int comb(int n, int m){
    if (n < m || m < 0) return 0;
    return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

int main(){
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[N - 1] = powermod(fac[N - 1], moder - 2);
    for (int i = N - 1; i; -- i){
        inv[i - 1] = 1ll * inv[i] * i % moder;
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n - 1; ++ i){
        ans[i] = 1ll * comb(i - 1, n - i - 1) * fac[i] % moder * fac[n - i - 1] % moder;
    }
    int ret = 0;
    for (int i = 1; i <= n - 1; ++ i){
        ret = (ret + 1ll * (ans[i] - ans[i - 1]) * i) % moder;
        ret += ret < 0 ? moder : 0;
    }
    printf("%d\n", ret);
    return 0;
}
