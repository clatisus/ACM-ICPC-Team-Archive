//
// Created by zzh on 2019/3/5.
//

#include <bits/stdc++.h>

using LL = long long;

const int max_N = 20;

int T, n, a[max_N];

LL sum[1 << max_N];

void testCase() {
    scanf("%d", &n);
    std::multiset<LL> set;
    for (int i = 1, x; i < (1 << n); ++i) {
        scanf("%d", &x);
        set.insert(x);
    }
    sum[0] = 0;
    for (int i = 0; i < n; ++i) {
        a[i] = *set.begin();
        for (int j = 0; j < (1 << i); ++j) {
            auto it = set.find(sum[j | (1 << i)] = sum[j] + a[i]);
            if (it == set.end()) {
                puts("NO");
                return;
            }
            set.erase(it);
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d%c", a[i], " \n"[i + 1 == n]);
    }
    //fflush(stdout);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
}
/*
1
3
1 2 3 3 4 5 6
 */