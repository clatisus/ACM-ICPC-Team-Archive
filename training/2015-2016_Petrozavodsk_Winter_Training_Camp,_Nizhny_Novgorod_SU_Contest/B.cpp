#include <bits/stdc++.h>

#define MAXN (100010)

int n, x;
std::set<int> set[2];

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        set[b].insert(a);
    }
    int dir = 0;
    int ans = 0;
    while (true) {
        if (dir == 0) {
            auto it = set[0].lower_bound(x);
            if (it == set[0].end()) it = set[0].begin();
            else -- it;
            if (it == set[0].end() || *it > x) {
                ++ans;
                dir = 1;
                x = 0;
            } else {
                int u = *it;
                set[0].erase(it);
                dir = 1;
                x = u;
                -- n;
            }
        } else {
            auto it = set[1].lower_bound(x);
            if (it == set[1].end()) {
                break;
            }
            int u = *it;
            set[1].erase(it);
            -- n;
            dir = 0;
            x = u;
        }
    }
    if (n == 0) printf("%d\n", ans);
    else printf("-1\n");
    return 0;
}
