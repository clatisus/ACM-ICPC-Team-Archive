#include<bits/stdc++.h>

const int N = 2000010;
const int moder = (int) 1e9 + 7;
const double PI = std::acos(-1.0);

int fac[N], inv[N], invf[N];

void init(){
    fac[0] = invf[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * i * fac[i - 1] % moder;
        inv[i] = i > 1 ? moder - 1ll * (moder / i) * inv[moder % i] % moder : 1;
        invf[i] = 1ll * inv[i] * invf[i - 1] % moder;
    }
}

int comb(int n, int m){
    return 1ll * fac[n] * invf[m] % moder * invf[n - m] % moder;
}

int main(){
    init();
    int n;
    scanf("%d", &n);
    if (n < 4){
        puts("1");
        return 0;
    }
    int ans = 0;
    for (int i = 0; ; ++ i){
        int left = std::max(-1.0, std::floor(n - (i + 1) * PI - 4)), right = std::max(-1.0, std::floor(n - i * PI - 4));
        if (left == right) break;
        for (int j = left + 1; j < right; ++ j){
            ans += comb(i + j, i);
            ans -= ans >= moder ? moder : 0;
        }
        ans = (ans + 2ll * comb(i + right, i)) % moder;
    }
    printf("%d\n", ans);
    return 0;
}
