#include <bits/stdc++.h>

#define MAXN (300010)

int k, n, m;
int t[MAXN];

int main() {
    scanf("%d%d%d", &k, &n, &m);
    for (int i = 1; i <= k; ++i) {
        scanf("%d", t + i);
    }
    t[0] = 1;
    for (int i = 1; i <= k; ++i) {
        if (t[i] == -1) {
            t[i] = t[i - 1];
        }
        if (t[i] < t[i - 1]) {
            printf("-1\n");
            return 0;
        }
    }
    if (k > n) {
        printf("-1\n");
        return 0;
    }
    std::vector<int> vec;
    int remain = n - k, now = t[1], sit = 1;
    while (remain) {
        ++ now;
        if (now > m) {
            printf("-1\n");
            return 0;
        }
        while (sit <= k && t[sit] < now) ++ sit;
        int num = std::min(remain, sit - 1);
        for (int i = 1; i <= num; ++i) vec.push_back(now);
        remain -= num;
    }
    std::reverse(vec.begin(), vec.end());
    for (auto v : vec) {
        printf("%d ", v);
    }
    for (int i = 1; i <= k; ++i) {
        printf("%d%c", t[i], " \n"[i == k]);
    }
    return 0;
}
