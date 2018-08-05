#include <bits/stdc++.h>

const int max_N = (int) 4e5 + 21;

#define lbt(x) ((x) & -(x))

int bit[max_N], n, m, rk[max_N], ans[max_N];

bool vis[max_N];

std::vector<int> vec[max_N];

void bit_add(int x, int y = 1) {
    for (; x <= n ; x += lbt(x)) bit[x] += y;
}

int bit_sum(int x) {
    int ret = 0;
    for (; x; x -= lbt(x)) ret += bit[x];
    return ret;
}

int bit_kth(int x) {
    int ret = 0;
    for (int i = (1 << 20); i; i >>= 1) {
        int tmp = ret + i;
        if (tmp <= n && x > bit[tmp]) {
            x -= bit[tmp];
            ret += i;
        }
    }
    return ret + 1;
}

void newGroup(int c) {
    vec[c].push_back(++m);
    bit_add(m);
}

int add(int l, int c, int a) {
    if (!vis[c]) {
        vis[c] = true;
        return newGroup(c), l;
    }

    int min = l - a - 1;
    int ming = bit_kth(min);

    auto it = std::lower_bound(vec[c].begin(), vec[c].end(), ming);
    if (it == vec[c].end()) return newGroup(c), l;

    int gp = *it;
    int res = std::max(min, bit_sum(gp - 1)) + 1;
    return bit_add(gp), res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, c, a; i <= n; ++i) {
        scanf("%d%d", &c, &a);
        rk[i] = add(i, c, a);
    }
    memset(bit + 1, 0, n * sizeof(int));
    for (int i = 1; i <= n; ++i) bit_add(i);
    for (int i = n; i; --i) {
        int res = bit_kth(rk[i]);
        ans[res] = i;
        bit_add(res, -1);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    return puts(""), 0;
}
