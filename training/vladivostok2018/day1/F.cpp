#include <bits/stdc++.h>

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        int n, m;
        scanf("%d%d", &n, &m);
        std::map<int, int> map1, map2;
        std::set<int> set;
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d", &x);
            map1[x] ++;
            set.insert(x);
        }
        for (int i = 0; i < m; ++ i) {
            int x;
            scanf("%d", &x);
            map2[x] ++;
            set.insert(x);
        }
        int ans1 = 0, ans2 = 0;
        for (auto v : set) {
            if (map1.count(v) && map2.count(v)) ++ ans2;
            if (map1.count(v) || map2.count(v)) ++ ans1;
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}

