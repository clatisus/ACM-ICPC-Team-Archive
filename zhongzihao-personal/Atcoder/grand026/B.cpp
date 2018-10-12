#include<bits/stdc++.h>

typedef long long ll;

bool solve(){
    ll a, b, c, d;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    if (a < b){
        return false;
    }
    if (b > d){
        return false;
    }
    ++ c;
    ll gcd = std::__gcd(b, d);
    ll div = c / gcd;
    if (c % gcd > a % gcd){
        ++ div;
    }
    c = div * gcd + a % gcd;
    return c >= b;
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        puts(solve() ? "Yes" : "No");
    }
    return 0;
}
