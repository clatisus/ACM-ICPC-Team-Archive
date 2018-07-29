#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

int B, n, m, z[max_N], a[max_N];

void build(int id) {
    int l = id * B;
    int r = std::min(l + B, n);
    if (!l || r == n) return;
    for (int i = l; i < r; ++i) {
        a[i] = z[i];
    }
    std::sort(a + l, a + r);
}


void modify(int x, int y) {
    int id = x / B;
    int l = id * B;
    int r = std::min(l + B, n);
    if (l && r < n) {
        int pos = l;
        while (pos < r && a[pos] != z[x]) ++pos;
        a[pos] = y;
        while (pos > l && a[pos] < a[pos - 1]) {
            std::swap(a[pos], a[pos - 1]);
            --pos;
        }
        while (pos + 1 < r && a[pos] > a[pos + 1]) {
            std::swap(a[pos], a[pos + 1]);
            ++pos;
        }
    }
    z[x] = y;
}

int bruteForce(int l, int r, int x, bool tp) {
    int res = 0;
    for (int i = l; i < r; ++i) 
        if (tp && z[i] <= x) ++res;
        else if (!tp && z[i] < x) ++res;
    return res;
}

int query(int l, int r, int x, bool tp) {
    int lx = l / B, rx = r / B;

    if (lx == rx) {
        return bruteForce(l, r + 1, x, tp);
    }

    int res = 0;

    res += bruteForce(l, (lx + 1) * B, x, tp);
    res += bruteForce(rx * B, r + 1, x, tp);

    for (int i = lx + 1; i < rx; ++i) {
        int s = i * B, t = s + B;
        int tmp;
        if (tp) tmp = std::upper_bound(a + s, a + t, x) - a - s;
        else tmp = std::lower_bound(a + s, a + t, x) - a - s;
        res += tmp;
    }

    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", z + i);
    }
    
    B = std::sqrt(n * std::log(n)) + 1;

    for (int i = 1; i < (n / B); ++i) {
        build(i);
    }

    scanf("%d", &m);
    while (m--) {
        int x1, y1, x2, y2;
        char t[5];
        scanf("%s", t);
        if (*t == 'C') {
            scanf("%d%d", &x1, &y1);
            modify(x1 - 1, y1);
        } else {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            int big, little;

            if ((y1 + y2) & 1) {
                big = query(x1 - 1, x2 - 1, (y1 + y2) >> 1, true);
                little = (x2 - x1 + 1) - big;
            } else {
                big = query(x1 - 1, x2 - 1, (y1 + y2) >> 1, false);
                little = (x2 - x1 + 1) - query(x1 - 1, x2 - 1, (y1 + y2) >> 1, true);
            }

            if (big == little) puts("0");
            else puts(big > little ? "1" : "2");

//            printf("big = %d, little = %d\n", big, little);
        }
    }

    return 0;
}
