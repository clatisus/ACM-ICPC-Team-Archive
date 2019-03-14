#include <bits/stdc++.h>

const int MAXN = 4010;

int n, m, k;
char s[MAXN], t[MAXN];
int cnt[MAXN], tot;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        scanf("%s%s", s, t);
        int ans = 0;
        for (int i = -m + 1; i < n; ++i) {
            tot = 0;
            for (int j = i < 0 ? -i : 0; j < m && i + j < n; ++j) {
                cnt[tot++] = s[i + j] == t[j] ? 0 : 1;
            }
            int now = 0;
            for (int r = 0, l = 0; r < tot; ++r) {
                now += cnt[r];
                while (now > k && l <= r) {
                    now -= cnt[l++];
                }
                ans = std::max(ans, r - l + 1);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
 1
12 13 2
hakunamatata
hienakulameta
 */