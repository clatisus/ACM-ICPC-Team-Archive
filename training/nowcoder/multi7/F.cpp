#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 500010;

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

int fac[N], inv[N], ans[N];

void init(){
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[N - 1] = powermod(fac[N - 1], moder - 2);
    for (int i = N - 1; i; -- i){
        inv[i - 1] = 1ll * inv[i] * i % moder;
    }
}

int comb(int n, int m){
    if (n < m || m < 0) return 0;
    return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

int n;

int calc(int n, int t, int k){
    int a0, a1, a2;
    a2 = moder - 1;
    a1 = (::n - 2ll * t + 3) % moder;
    a1 += a1 < 0 ? moder : 0;
    a0 = 1ll * (t - 1) * (t - 2) % moder;
    a0 = (a0 + 1ll * (t - 1) * a1) % moder;
    a0 += a0 < 0 ? moder : 0;
    int ret = 1ll * a2 * (k + 1) % moder * (k + 2) % moder * comb(n - t + 3, k + 3) % moder;
    ret = (ret + 1ll * a1 * (k + 1) % moder * comb(n - t + 2, k + 2)) % moder;
    ret = (ret + 1ll * a0 * comb(n - t + 1, k + 1)) % moder;
    return ret;
}

int main(){
    init();
    scanf("%d", &n);
    for (int d = 1; d < n; ++ d){
        for (int k = 2; k <= n && (k - 1) * (d - 1) < n; ++ k){
            ans[d] = (ans[d] + calc(n - 1, (k - 1) * (d - 1) + 1, k - 2) - calc(0, (k - 1) * (d - 1) + 1, k - 2)) % moder;
        }
        ans[d] += ans[d] < 0 ? moder : 0;
    }
    int ret = 0;
    for (int d = 1; d < n; ++ d){
        ret = (ret + 1ll * d * (ans[d] - ans[d + 1])) % moder;
    }
    ret += ret < 0 ? moder : 0;
    printf("%d\n", ret);
    return 0;
}
