#include <bits/stdc++.h>

#define lbt(x) ((x) & -(x))

using LL = long long;

const int max_N = (int) 2e5 + 21;

int n, m, tot, pos[max_N];

LL a[max_N], b[max_N], h[max_N], bit[max_N];

void add(int x, LL a) {
    for (; x && x <= tot; x += lbt(x)) bit[x] += a;
}

LL sum(int x) {
    LL ret = 0;
    for (; x; x -= lbt(x)) ret += bit[x];
    return ret;
}

std::multiset<LL> set;

int rk(LL x) {
    return std::lower_bound(h + 1, h + 1 + tot, x) - h;
}

void query() {
    int ret = 0, x;
    for (auto it = set.begin(); it != set.end(); it = set.lower_bound(std::max(*it + 1, sum(x)))) {
        //printf("it = %lld\n", *it);
        x = rk(*it);
        if (*it >= sum(x - 1)) ++ret;
    }
    if (sum(rk(*set.begin())) > *set.begin()) ++ret;
    printf("%d\n", ret);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
        h[++tot] = a[i];
        set.insert(a[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%lld", pos + i, b + i);
        h[++tot] = b[i];
    }
    std::sort(h + 1, h + 1 + tot);
    tot = std::unique(h + 1, h + 1 + tot) - (h + 1);
    for (int i = 1; i <= n; ++i) add(rk(a[i]), a[i]);
    query();
    for (int i = 1; i <= m; ++i) {
        LL x = a[pos[i]], y = b[i];
        add(rk(x), -x), add(rk(y), y);
        set.erase(set.lower_bound(x));
        set.insert(y);
        a[pos[i]] = y;
        query();
    }
    return 0;
}

