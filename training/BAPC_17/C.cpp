#include <bits/stdc++.h>

#define MAXN (500010)
#define ll long long

int n;
ll a[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", a + i);
    }
    std::set<ll> set, pre;
    for (int i = 0; i < n; ++i) {
        std::set<ll> now;
        for (auto v : pre) {
            now.insert(std::__gcd(v, a[i]));
            set.insert(std::__gcd(v, a[i]));
        }
        now.insert(a[i]);
        set.insert(a[i]);
        pre = now;
    }
    printf("%d\n", set.size());
    return 0;
}

