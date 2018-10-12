#include <bits/stdc++.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a < b) std::swap(a, b);
        printf("%d\n", 2 * a + b);
    }
    return 0;
}
