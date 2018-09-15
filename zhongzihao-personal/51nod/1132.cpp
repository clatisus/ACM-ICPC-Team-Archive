#include<bits/stdc++.h>

typedef long long ll;
typedef __int128 i128;

i128 calc(ll a, ll b, ll c, ll n){
    ll m = ((i128) a * n + b) / c;
    if (!m) return 0;
    if (!a){
        return (i128) (b / c) * (n + 1);
    }
    ll ret;
    if (a >= c || b >= c){
        ret = ((i128) n * (n + 1) >> 1) * (a / c);
        ret += (i128) (n + 1) * (b / c);
        ret += calc(a % c, b % c, c, n);
        return ret;
    }
    ret = (i128) n * m - calc(c, c - b - 1, a, m - 1);
    return ret;
}

ll ex_euc(ll a, ll b, ll &x, ll &y){
    if (!b){
        x = 1, y = 0;
        return a;
    }
    ll ret = ex_euc(b, a % b, x, y), tmp = y;
    y = x - a / b * y;
    x = tmp;
    return ret;
}

ll calc(ll n, ll a, ll b, ll x, ll y){
    ll max = std::min(n, (i128) a * b > LLONG_MAX ? LLONG_MAX : a * b - 1);
    ll ans = n - max;
    ans += max - (calc(-y, a - 1, a, max) - calc(x, 0, b, max));
    return ans;
}

void solve(){
    ll a, b, l, r;
    scanf("%lld%lld%lld%lld", &a, &b, &l, &r);
    ll x, y;
    ll gcd = ex_euc(a, b, x, y);
    if (x < 0){
        std::swap(a, b);
        std::swap(x, y);
    }
    a /= gcd, b /= gcd;
    ll ans = calc(r / gcd, a, b, x, y) - calc((l - 1) / gcd, a, b, x, y);
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
