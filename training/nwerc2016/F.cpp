#include <bits/stdc++.h>

inline void read(int &x) {
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); (x *= 10) += (c - '0'));
}

const int max_N = (int) 1e6 + 21;

int n, w[2][max_N];

inline int check(int d, int x) {
    static int a[max_N], m;
    m = 0;
    for (int i = 1; i <= n; ++i) {
        if (w[d][i] <= x) continue;
        a[++m] = w[d][i];
    }
    if (m & 1) return false;
    for (int i = 1; i * 2 <= m; ++i) {
        if (a[i * 2 - 1] != a[i * 2]) return false;
    }
    return true;
}

int main() {
    read(n);
    for (int d = 0; d < 2; ++d)
        for (int i = 1; i <= n; ++i) read(w[d][i]);
    int l = 0, r = (int) 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(0, mid) && check(1, mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}

