#include <bits/stdc++.h>

#define MAXN (10)

char a[MAXN], b[MAXN];

int main() {
    int ans1 = 0, ans2 = 0;
    scanf("%s%s", a, b);
    for (int i = 0; i < 6; ++i) {
        ans1 += a[i] < b[i];
        ans2 += a[i] > b[i];
    }
    printf("%d\n%d\n", ans1, ans2);
    return 0;
}
