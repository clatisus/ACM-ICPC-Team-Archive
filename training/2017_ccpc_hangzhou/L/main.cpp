#include<bits/stdc++.h>

typedef long long ll;

const int BIT = 42;

int calc(ll a, ll b, ll c, ll n){ //special case for t1 = 0, t2 = 1
    if (!a){
        return (b / c) * (n + 1);
    }
    if (a >= c || b >= c){
        ll tmp1 = n & 1 ? n : n >> 1;
        ll tmp2 = n + 1 & 1 ? n + 1 : n + 1 >> 1;
        int ret = tmp1 * tmp2 * (a / c);
        ret += (n + 1) * (b / c);
        ret += calc(a % c, b % c, c, n);
        return ret;
    }
    ll m = ((__int128) a * n + b) / c;
    if (!m){
        return 0;
    }
    int ret = n * m - calc(c, c - b - 1, a, m - 1);
    return ret;
}

void solve(){
    ll n;
    scanf("%lld", &n);
    ll ans = 0;
    for (ll i = 1, j; i <= n; i = j + 1){
        ll tmp = 0;
        j = n / (n / i);
        if (j - i <= 1000){
            for (int k = i; k <= j; ++ k){
                ans ^= n % k;
            }
            continue;
        }
        for (int k = 0; k < BIT; ++ k){
            tmp |= (ll) (calc(n / j, n % j, 1ll << k, j - i) & 1) << k;
        }
        ans ^= tmp;
    }
    printf("%lld\n", ans);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
