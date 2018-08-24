#include <bits/stdc++.h>

#define ll long long

std::map<ll, ll> map;

ll dfs(ll u) {
    if (u == 1) return 0;
    if (map.count(u)) return map[u];
    if (u % 2 == 0) {
        map[u] = dfs(u / 2) + u;
    } else {
        map[u] = dfs((3 * u + 1) / 2) + u + 1;
    }
    return map[u];
}

int main() {
    ll n;
    scanf("%lld", &n);
    printf("%lld\n", dfs(n));
    return 0;
}
