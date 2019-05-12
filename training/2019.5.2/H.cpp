//
// Created by nonsensetime on 19-5-2.
//

#include <bits/stdc++.h>

const int MIN = -32768;
const int MAX = 32767;

char s[100];

int main() {
    freopen("hard.in", "r", stdin);
    freopen("hard.out", "w", stdout);
    std::vector<std::pair<int, int>> vec;
    while (scanf("%s", s) != EOF) {
        scanf("%s", s);
        int left = MIN, right = MAX;
        if (s[0] == '>') scanf("%d", &left);
        else scanf("%d", &right);
        if (scanf("%s", s) == EOF || s[0] == '|') {
            if (left <= right) {
                vec.emplace_back(left, right);
            }
            continue;
        }
        scanf("%s", s);
        scanf("%s", s);
        scanf("%d", &right);
        if (left <= right) {
            vec.emplace_back(left, right);
        }
        if (scanf("%s", s) == EOF) break;
    }
    std::sort(vec.begin(), vec.end());
    std::vector<std::pair<int, int>> res;
    int n = vec.size();
    for (int i = 0, j; i < n; i = j) {
        int right = vec[i].second;
        for (j = i + 1; j < n && vec[j].first <= right + 1; ++j) {
            right = std::max(right, vec[j].second);
        }
        res.emplace_back(vec[i].first, right);
    }
    if (res.empty()) {
        puts("false");
        return 0;
    }
    if (res.size() == 1 && res[0].first == MIN && res[0].second == MAX) {
        puts("true");
        return 0;
    }
    n = res.size();
    for (int i = 0; i < n; ++i) {
        int left = res[i].first, right = res[i].second;
        if (left == MIN) {
            printf("x <= %d", right);
        } else if (right == MAX) {
            printf("x >= %d", left);
        } else {
            printf("x >= %d && x <= %d", left, right);
        }
        if (i != n - 1) puts(" ||");
        else puts("");
    }
    return 0;
}
/*
x >= 5 && x <= 10 ||
x >= 7 && x <= 20 ||
x <= 2 ||
x >= 21 && x <= 25 ||
x >= 8 && x <= 10 ||
x >= 100
 */