#include <bits/stdc++.h>

int n;
std::string s[30];
char buf[100010];
using ll = long long;

int main() {
    scanf("%d", &n);
    std::unordered_map<std::string, std::vector<std::pair<std::string, bool>>> map;
    for (int i = 0; i < n; ++i) {
        scanf("%s", buf);
        s[i] = std::string(buf);
        if (!map.count(s[i])) {
            map[s[i]] = {};
        }
    }
    int m;
    scanf("%d", &m);
    while (m--) {
        scanf("%s", buf);
        std::string d(buf);
        scanf("%s", buf);
        std::string e(buf);
        scanf("%s", buf);
        std::string c(buf);
        if (!map.count(d)) continue;
        map[d].emplace_back(e, (c == "correct"));
    }
    ll ans = 1, tot = 1;
    std::string t;
    for (int i = 0; i < n; ++i) {
        int c = 0, nc = 0, all = 0;
        for (auto p : map[s[i]]) {
            if (p.second) {
                ++c;
            } else {
                ++nc;
            }
            ++all;
        }
        if (all == 1) {
            t += map[s[i]][0].first + " ";
        }
        tot *= all;
        ans *= c;
    }
    if (tot == 1) {
        printf("%s\n", t.c_str());
        puts(ans ? "correct" : "incorrect");
        return 0;
    }
    printf("%lld correct\n%lld incorrect\n", ans, tot - ans);
    return 0;
}
/*
7
als mollen mollen mollen mollen mollen mollen
4
als when correct
mollen moles correct
mollen destroy correct
mollen mills incorrect

 5
de zuigers zijn buiten werking
6
zijn are correct
banaan banana correct
de the correct
zuigers suckers incorrect
buiten out correct
werking working incorrect

 */