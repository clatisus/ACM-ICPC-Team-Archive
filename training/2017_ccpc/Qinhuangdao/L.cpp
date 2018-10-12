#include <bits/stdc++.h>

#define MAXN (100010)

int n, m;
char s[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        scanf("%s", s + 1);
        int ans1 = 0, ans2 = 0;
        for (int i = m; i < n; ++i) {
            ans1 += s[i] == 'L';
        }
        for (int i = 2; i <= m; ++i) {
            ans2 += s[i] == 'R';
        }
        printf("%d\n", std::min(ans1, ans2));
    }
    return 0;
}
