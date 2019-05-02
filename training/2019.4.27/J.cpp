#include <bits/stdc++.h>

const int MAXN = 1000010;

char s[MAXN];

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    std::set<int> set;
    set.insert(0);
    set.insert(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '0') {
            set.insert(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '2') {
            auto r = set.lower_bound(i);
            auto l = r;
            --l;
            int x = *l + *r - i;
            if (1 <= *l) set.erase(l);
            if (*r <= n) set.erase(r);
            set.insert(*l + *r - i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        s[i] = '1';
    }
    for (auto u : set) {
        s[u] = '0';
    }
    s[n + 1] = 0;
    printf("%s\n", s + 1);
    return 0;
}