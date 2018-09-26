#include <bits/stdc++.h>

#define MAXN (110)

int m, n, x;
int c[MAXN];

struct node {
    int first, second;
    bool operator < (const node &rhs) const {
        return first == rhs.first ? c[second] < c[rhs.second] : first < rhs.first;
    }
};

int main() {
    while (~scanf("%d%d%d", &m, &n, &x)) {
        std::multiset<node> set;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", c + i);
        }
        for (int i = 1; i <= n; ++i) {
            set.insert({0, i});
        }
        int ans1 = 0, ans2 = 0, ans3 = m;
        while (!set.empty() && set.begin()->first <= x) {
            auto u = *set.begin();
            set.erase(set.begin());
            if (u.first) ++ans1;
            if (m && u.first < x) {
                --m;
                ++ans2;
                set.insert({u.first + c[u.second], u.second});
            }
        }
        printf("%d %d\n", ans3 - ans2, ans2 - ans1);
    }
    return 0;
}

