#include <bits/stdc++.h>

const int MAXN = 500010;

#define lowbit(x) ((x) & (-(x)))

int n;
std::pair<int, int> a[MAXN];
int p[MAXN];
int c[MAXN];
int ans[2];

int getmax(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) {
        ret = std::max(ret, c[x]);
    }
    return ret;
}

void update(int x, int v) {
    for (; x < MAXN; x += lowbit(x)) {
        c[x] = std::max(c[x], v);
    }
}

int main() {
    for (int _ = 0; _ < 2; ++_) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i].first);
            a[i].second = i;
        }
        std::sort(a + 1, n + a + 1);
        for (int i = 1; i <= n; ++i) {
            p[a[i].second] = i;
        }

        for (int i = 1; i <= n; ++i) {
            int now = getmax(p[i]) + 1;
            update(p[i], now);
            ans[_] = std::max(ans[_], now);
        }

        memset(c, 0, sizeof(c));
    }
    printf("%d\n", ans[0] + ans[1]);
    return 0;
}
