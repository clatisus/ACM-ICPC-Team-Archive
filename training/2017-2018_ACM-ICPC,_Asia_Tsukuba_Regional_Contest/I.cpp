#include <bits/stdc++.h>

#define lbt(x) ((x) & -(x))

const int N = 100000, max_N = (int) 2e5 + 21;

int n, a[max_N], b[max_N], bit[2][max_N], s[max_N], ans1, ans2;

void add(int *bit, int x) {
    for (; x && x <= N; x += lbt(x)) ++bit[x];
}

int sum(int *bit, int x) {
    int ret = 0;
    for (; x; x -= lbt(x)) ret += bit[x];
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", a + i, b + i);
        add(bit[0], N - a[i] + 1);
        add(bit[1], b[i]);
        ++s[a[i]], --s[b[i]];
    }
    for (int i = 1; i <= n; ++i) {
        int ret = n;
        ret -= sum(bit[0], N - b[i] + 1);
        ret -= sum(bit[1], a[i]);
        ans1 = std::max(ans1, ret);
    }
    for (int i = 1; i <= N; ++i) {
        s[i] += s[i - 1];
        ans2 = std::max(s[i], ans2);
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}

