#include<bits/stdc++.h>

const int N = 1000010;
const int moder = 1e9 + 7;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int power[N];
int fac[N], inv[N];

void init(){
    power[0] = 1;
    for (int i = 1; i < N; ++ i){
        power[i] = 2ll * power[i - 1] % moder;
    }
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
    return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

int main(){
    init();
    int n;
    scanf("%d", &n);
    int sumw = 0, suml = 0;
    while (sumw < n && suml < n){
        int ans = 1ll * comb(2 * n - 2 - sumw - suml, n - sumw - 1) * power[sumw + suml + 1] % moder;
        printf("%d\n", ans);
        int x;
        scanf("%d", &x);
        if (x == 0){
            ++ sumw;
        }
        else{
            ++ suml;
        }
    }
    return 0;
}
