#include<bits/stdc++.h>

const int moder = (int) 1e9 + 7;
const int N = 2000010;

int fac[N], invf[N], inv[N];

int comb(int n, int m){
    if (n < m || m < 0){
        return 0;
    }
    return 1ll * fac[n] * invf[m] % moder * invf[n - m] % moder;
}

int main(){
    fac[0] = invf[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    n -= k - m;
    if (m == 1){
        printf("%d\n", n - 1);
        return 0;
    }
    int ans = 0;
    for (int i = 1; i < n; ++ i){
        ans = (ans + 1ll * comb(i - 1, m - 2) * (n - i - 1)) % moder;
    }
    for (int l = 1; l < m; ++ l){
        ans = (ans + 1ll * comb(n - l - 1, m - l) * (n - l - 1)) % moder;
        ans = (ans - 1ll * comb(n - l, m - l + 1) * (m - l)) % moder;
    }
    ans += ans < 0 ? moder : 0;
    printf("%d\n", ans);
}
