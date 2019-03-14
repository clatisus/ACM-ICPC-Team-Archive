#include <bits/stdc++.h>

#define MAXN (1010)

int n;
char s[MAXN];
char t[MAXN];

struct node {
    // type = 0, char
    // type = 1, int
    int a, type;

    bool operator < (const node &rhs) const {
        if (type == rhs.type) return a < rhs.a;
        return type < rhs.type;
    }

    bool operator == (const node &rhs) const {
        return type == rhs.type && a == rhs.a;
    }

};

std::vector<node> ss, tt;

// return true if t < s
bool check() {
    tt.clear();
    for (int i = 0; t[i]; ++i) {
        if (isalpha(t[i])) {
            tt.push_back({t[i], 1});
        } else {
            int now = 0, j;
            for (j = i; isdigit(t[j]); ++j) {
                now = now * 10 + t[j] - '0';
            }
            i = j - 1;
            tt.push_back({now, 0});
        }
    }
    int lens = ss.size();
    int lent = tt.size();
    for (int i = 0; i < std::min(lens, lent); ++i) {
        if (ss[i] == tt[i]) continue;
        return tt[i] < ss[i];
    }
    if (lent < lens) return true;
    return false;
}

int main() {
    scanf("%d%s", &n, s);
    for (int i = 0; s[i]; ++i) {
        if (isalpha(s[i])) {
            ss.push_back({s[i], 1});
        } else {
            int now = 0, j;
            for (j = i; isdigit(s[j]); ++j) {
                now = now * 10 + s[j] - '0';
            }
            i = j - 1;
            ss.push_back({now, 0});
        }
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%s", t);
        if (check()) {
            puts("-");
        } else {
            puts("+");
        }
    }
    return 0;
}