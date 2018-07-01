#include<bits/stdc++.h>

const int N = 100010;
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

int pre[2][N];

void solve(){
    memset(pre, 0, sizeof(pre));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, l, r, x; i < m; ++ i){
        scanf("%d%d%d", &l, &r, &x);
        -- l, -- r;
        ++ pre[x - 2][l];
        -- pre[x - 2][r + 1];
    }
    int min2 = INT_MAX, min3 = INT_MAX;
    for (int i = 1; i < n; ++ i){
        pre[0][i] += pre[0][i - 1];
        pre[1][i] += pre[1][i - 1];
    }
    for (int i = 0; i < n; ++ i){
        min2 = std::min(min2, pre[0][i]);
        min3 = std::min(min3, pre[1][i]);
    }
    int ans = 1ll * powermod(2, min2) * powermod(3, min3) % moder;
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

