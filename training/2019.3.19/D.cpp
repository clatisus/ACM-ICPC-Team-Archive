#include<bits/stdc++.h>

typedef long long ll;

ll calc(ll a, ll b, ll c, ll n){
    ll m = (a * n + b) / c;
    if (!m){
        return 0;
    }
    if (!a){
        return (b / c) * (n + 1);
    }
    if (a >= c || b >= c){
        ll ret = n * (n + 1) / 2 * (a / c);
        ret += (n + 1) * (b / c);
        ret += calc(a % c, b % c, c, n);
        return ret;
    }
    ll ret = n * m - calc(c, c - b - 1, a, m - 1);
    return ret;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        int p, q, n;
        scanf("%d%d%d", &p, &q, &n);
        printf("%lld\n", 1ll * p * n * (n + 1) / 2 - calc(p, 0, q, n) * q);
    }
    return 0;
}