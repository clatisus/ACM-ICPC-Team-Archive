#include <bits/stdc++.h>

const int max_N = 1000 + 21;

int l, r, n, a[max_N];

bool broken[max_N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        char s[20], *t;
        scanf("%s", s);
        if (*s == 'x') {
            broken[i] = true;
        } else {
            a[i] = strtol(s, &t, 10);
        }
    }
    for (int i = 1; i < n; ++i)
        if (broken[i] && broken[i + 1]) {
            puts("none");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        if (!broken[i]) {
            if (i & 1) {
                if (i > 1 && !broken[i - 1] && a[i] >= a[i - 1]) {
                    puts("none");
                    return 0;
                }
                if (i < n && !broken[i + 1] && a[i] >= a[i + 1]) {
                    puts("none");
                    return 0;
                }
            } else {
                if (i > 1 && !broken[i - 1] && a[i] <= a[i - 1]) {
                    puts("none");
                    return 0;
                }
                if (i < n && !broken[i + 1] && a[i] <= a[i + 1]) {
                    puts("none");
                    return 0;
                }
            }
        }
    l = INT_MIN, r = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        if (broken[i]) {
            if (~i & 1) {
                if (i > 1) {
                    l = std::max(l, a[i - 1] + 1);
                }
                if (i < n) {
                    l = std::max(l, a[i + 1] + 1);
                }
            } else {
                if (i > 1) {
                    r = std::min(r, a[i - 1] - 1);
                }
                if (i < n) {
                    r = std::min(r, a[i + 1] - 1);
                }
            }
        }
    }

    if (l > r) puts("none");
    else if (l == r) printf("%d\n", l);
    else puts("ambiguous");

    return 0;
}
