#include <bits/stdc++.h>

typedef long long ll;

ll calc00(ll n, ll k){
    ll left = std::max(0ll, n - 2 * k + 1);
    ll right = std::min(k - 1, n - k);
    return std::max(0ll, right - left + 1);
}

ll calc0k(ll n, ll k){
    ll left = std::max(0ll, n - 3 * k + 1);
    ll right = std::min(k - 1, n - 2 * k);
    return std::max(0ll, right - left + 1);
}

int main(){
    ll n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    if (k == 1){
        printf("%d\n", n * m & 1 ? n * m : 0);
        return 0;
    }
    if (n > m){
        std::swap(n, m);
    }
    if (n == 3 * k && m == 3 * k){
        puts("1");
        return 0;
    }
    ll ans = calc00(n, k) * calc00(m, k);
    if (n == 3 * k - 1){
        ans += calc00(n, k) * calc0k(m, k) * 2;
        if (m == 3 * k){
            ans += calc00(n, k) * 2;
        }
    }
    if (m == 3 * k - 1){
        ans += calc00(m, k) * calc0k(n, k) * 2;
    }
    if (m == 3 * k){
        ans += calc00(n, k);
        if (n <= 3 * k - 2){
            ans += calc0k(n, k) * 4;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
