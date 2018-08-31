#include <bits/stdc++.h>

int main() {
    int a, b, c;
    int d, e, f;
    while (~scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f)) {
        int ans = std::max(0, d - a);
        ans += std::max(0, e - b);
        ans += std::max(0, f - c);
        printf("%d\n", ans);
    }
    return 0;
}
