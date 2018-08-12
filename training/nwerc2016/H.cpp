#include <bits/stdc++.h>

#define MAXN (70)
#define ll long long

int n;
char s[MAXN], t[MAXN];

ll getrank(char *s, int n) {
    if (n == -1) return 0;
    if (s[::n - n - 1] == '1') {
        return (1ll << (n + 1)) - 1 - getrank(s, n - 1);
    }
    return getrank(s, n - 1);
}

int main() {
    scanf("%d", &n);
    scanf("%s%s", &s, &t);
    ll a = getrank(s, n - 1);
    ll b = getrank(t, n - 1);
    printf("%lld\n", std::abs(a - b) - 1);
    return 0;
}
