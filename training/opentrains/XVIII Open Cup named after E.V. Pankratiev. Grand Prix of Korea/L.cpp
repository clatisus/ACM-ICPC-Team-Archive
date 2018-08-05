#include<bits/stdc++.h>

const int N = 100010;

typedef long long ll;

int powermod(int a, int exp, int moder){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int a[N], pre[N << 1];
int n, k;
ll T;

int main(){
    scanf("%d%d%lld", &n, &k, &T);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < 60; ++ i){
        if ((T >> i & 1) == 0) continue;
        ll x = 1ll << i, gcd = std::__gcd(x, 1ll * n);
        int dis = x % n;
        for (int j = 0; j < gcd; ++ j){
            for (int k = 0; k < n / gcd; ++ k){
                pre[k] = (k ? pre[k - 1] : 0) ^ a[(1ll * dis * k + j) % n];
            }
            for (int k = n / gcd; k < n / gcd << 1; ++ k){
                pre[k] = pre[n / gcd - 1] ^ pre[k % (n / gcd)];
            }
            int y = k % (n / gcd);
            for (int k = 0; k < n / gcd; ++ k){
                int sit = (1ll * dis * k + j) % n;
                a[sit] = ::k / (n / gcd) & 1 ? pre[n / gcd - 1] : 0;
                a[sit] ^= pre[k + y - 1] ^ (sit ? pre[k - 1] : 0);
            }
        }
    }
    for (int i = 0; i < n; ++ i){
        printf("%d%c", a[i], " \n"[i == n - 1]);
    }
    return 0;
}
