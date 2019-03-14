#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long
#define lowbit(x) ((x) & (-(x)))

int n;
std::pair<int, int> a[MAXN];
int c[MAXN];

void insert(int x, int d) {
    for (; x < MAXN; x += lowbit(x)) {
        c[x] += d;
    }
}

int getsum(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) {
        ret += c[x];
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i].first);
        a[i].second = i;
        insert(i, 1);
    }
    std::sort(a + 1, n + a + 1);
    ll ans = 0;
    int tot = n;
    for (int i = 1, j; i <= n; i = j) {
        for (j = i; a[i].first == a[j].first; ++j);
        int k = j - 1;
        while (i <= k) {
            int disl = getsum(a[i].second - 1);
            int disr = tot - getsum(a[k].second);
            if (disl < disr) {
                ans += disl;
                insert(a[i].second, -1);
                ++i;
            } else {
                ans += disr;
                insert(a[k].second, -1);
                --k;
            }
            --tot;
        }
    }
    printf("%lld\n", ans);
    return 0;
}