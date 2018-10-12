#include <bits/stdc++.h>

using ll = long long;

ll n, k;

int calc(ll a, ll b) {
    int ret, i;
    for (i = 0; ; ++i) {
        if (a >= (n - a) / 2) break;
        a <<= 1;
    }
    ret = i;
    ll x = n - a;
    for (i = 0; ; ++i) {
        if (x <= b) break;
        x = (x + 1) >> 1;
    }
    ret += i + 1;
    return ret;
}

int main() {
    scanf("%lld%lld", &n, &k);
    int res = 0x3f3f3f3f;
    for (auto i = 1; i < k; ++i) {
        res = std::min(res, calc(i, k - i));
    }
    printf("%d\n", res);
    return 0;
}

