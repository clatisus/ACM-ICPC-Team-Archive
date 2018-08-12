#include <bits/stdc++.h>

#define MAXN (110)

int n;
std::pair<int, int> s[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &s[i].first);
        s[i].second = i;
    }
    std::sort(s, n + s);
    int sum = 0;
    for (int i = 0; i < n - 1; ++i) sum += s[i].first;
    if (sum < s[n - 1].first) {
        puts("impossible");
        return 0;
    }
    for (int i = n - 1; i >= 0; --i) printf("%d%c", s[i].second + 1, " \n"[i == 0]);
    return 0;
}

