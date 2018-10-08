#include <bits/stdc++.h>

#define MAXN (300010)
#define ll long long

int n, k;
ll b[MAXN];
ll tower[MAXN];

bool check(int m) {
    if (n < m) return false;
    for (int i = 1; i <= m; ++i) {
        tower[i] = b[i];
    }
    int level = 2, i = m + 1, j = 1;
    while (level <= k && i <= n) {
        if (b[i] >= tower[j] * 2) {
            tower[j++] = b[i];
        }
        ++i;
        if (j == m + 1) {
            ++level;
            j = 1;
        }
    }
    return level == k + 1;
}

void testCase(int cs) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", b + i);
    }
    std::sort(b + 1, n + b + 1);
    //check(2);
    int l = 0, r = n / k, ans = 0;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    printf("Case #%d: %d\n", cs, ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int _ = 1; _ <= T; ++_) {
        testCase(_);
    }
    return 0;
}
/*
3
4 2
1 2 3 4
6 3
1 1 2 2 4 4
6 3
1 1 2 2 3 4
*/

