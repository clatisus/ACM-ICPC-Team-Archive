#include <bits/stdc++.h>

char s[20];
std::map<std::string, int> map;

int getans(std::string s) {
    if (map.count(s)) return map[s];
    int n = s.length();
    int &now = map[s];
    now = 0;
    for (int i = 0, j; i < n; i = j){
       for (j = i; s[j] == s[i]; ++j);
       std::string t = s.substr(0, i) + s.substr(j, n - j);
       now = std::max(now, (j - i == 3 ? 1 : 0) + getans(t));
    }
    return now;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        std::string str(s);
        printf("%d\n", getans(s));
    }
    return 0;
}

