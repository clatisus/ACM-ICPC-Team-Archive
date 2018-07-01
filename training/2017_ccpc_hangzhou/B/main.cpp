#include<bits/stdc++.h>

const int moder = 998244353;

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

void solve(){
    int m;
    scanf("%d", &m);
    int ans = 1;
    for (int i = 0, p, n; i < m; ++ i){
        scanf("%d%d", &p, &n);
        int sum = 1ll * n * powermod(p, n - 1) % moder * (p - 1) % moder;
        sum += powermod(p, n);
        sum -= sum >= moder ? moder : 0;
        ans = 1ll * ans * sum % moder;
    }
    printf("%d\n", ans);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

