#include <bits/stdc++.h>

using LL = long long;

const int max_N = (int) 1e5 + 21;

int T, n, m, p, s[max_N], a[max_N], b[max_N], tot;

LL ret[max_N], sum, ans;

struct node {
    LL k;
    int v, id;
    bool operator<(const node& o) const {
        return k > o.k;
    }
} event[max_N * 3];

void testCase() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", s + i);
    }
    tot = 0;
    for (int i = 1; i <= p; ++i) {
        scanf("%d%d", a + i, b + i);
        LL k = s[a[i]] - b[i] % m;
        for (int j = 0; j < 3; ++j) {
            //printf("event : %d %d %d\n", k, i, j);
            event[++tot] = {k, i, j};
            k += m;
        }
        ret[i] = 0;
    }
    std::sort(event + 1, event + 1 + tot);
    sum = 0;
    ans = LLONG_MAX;
    for (int i = 1, j; i <= tot; i = j) {
        if (event[i].k < 1) break;
        for (j = i; j <= tot && event[i].k == event[j].k; ++j) {
            int v = event[j].v, id = event[j].id;
            sum -= ret[v];
            ret[v] = s[a[v]] - b[v] % m + 1ll * id * m;
            sum += ret[v];
        }
        if (event[i].k > m) continue;
        // printf("updt sum = %lld, event[i].k = %lld\n", sum, event[i].k);
        ans = std::min(ans, sum - event[i].k * p);
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}

