#include <bits/stdc++.h>

const int max_N = (int) 1.2e6 + 21;
const int sigma = 26 + 10 + 4;

inline int id(char c) {
    if (islower(c)) {
        return c - 'a';
    }
    if (c == '*') return 26;
    if (c == '#') return 27;
    if (c == '-') return 28;
    if (c == '.') return 29;
    if (isdigit(c)) {
        return 30 + c - '0';
    }
    return -1;
}

int rt[3], tot, ch[max_N][sigma], sum[max_N], siz[max_N];

// 0 -> lower, 1 -> *, 2 -> #

inline int new_node() {
    int u = ++tot;
    memset(ch[u], 0, sizeof(ch[u]));
    sum[u] = siz[u] = 0;
    return u;
}

inline void init() {
    tot = 0;
    for (int i = 0; i < 3; ++i) {
        rt[i] = new_node();
    }
}

inline bool valid_domain(std::string &s) {
    int sz = s.length();
    for (int i = 0; i < sz; ++i) {
        int c = id(s[i]);
        switch (c) {
            case 26:
            case 27:
                if (i || (i + 1 < sz && s[i + 1] != '.')) {
                    return false; // 4.
                }
                break;
            case 28:
                if (!i || i + 1 == sz || !islower(s[i - 1]) || !islower(s[i + 1])) {
                    return false; // 5.
                }
                break;
            case 29:
                if (!i || i + 1 == sz) {
                    return false; // 2.
                }
                if (s[i] == s[i - 1]) {
                    return false; // 3.
                }
                break;
            case -1:
                return false; // 1.
        }
    }
    return true;
}

inline bool valid_vpn(std::string &s) {
    int sz = s.length();
    if (!islower(s[0])) return false; // 2.
    for (int i = 0; i < sz; ++i) {
        if (s[i] == '-') {
            if (!i || i + 1 == sz || !islower(s[i - 1]) || !islower(s[i + 1])) {
                return false; // 3.
            }
        } else {
            if (!islower(s[i]) && !isdigit(s[i])) {
                return false; // 1.
            }
        }
    }
    return true;
}

int valid;

// 以 s 为前缀的个数
// tp == true : 等于 s 的个数
inline int find1(int u, std::string &s, int n, bool tp = false) {
    for (int i = 0; i < n; ++i) {
        int c = id(s[i]);
        if (!ch[u][c]) return 0;
        u = ch[u][c];
    }
    return tp ? siz[u] : sum[u];
}

// s 的前缀加一个通配符的个数
inline int find2(int u, std::string &s, int n) {
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        int c = id(s[i]);
        ret += siz[ch[u][26]];
        ret += siz[ch[u][27]];
        if (!ch[u][c]) return ret;
        u = ch[u][c];
    }
    ret += siz[ch[u][26]];
    ret += siz[ch[u][27]];
    return ret;
}

inline void insert(int u, std::string &s, int n) {
    for (int i = 0; i < n; ++i) {
        ++sum[u];
        int c = id(s[i]);
        if (!ch[u][c]) {
            ch[u][c] = new_node();
        }
        u = ch[u][c];
    }
    ++sum[u];
    ++siz[u];
}

inline void check_conflict(std::string &s) {
    // printf("check %s\n", s.c_str());
    auto t = s;
    std::reverse(t.begin(), t.end());
    int sz = t.length();
    if (s[0] == '*') {
        if (find1(rt[0], t, sz - 1)) return; // 1.
        if (find1(rt[1], t, sz - 1) || find2(rt[1], t, sz - 1)) return; // 1.
        if (find1(rt[2], t, sz - 1)) return; // 2.
        ++valid;
        insert(rt[1], t, sz);
    } else if (s[0] == '#') {
        if (find2(rt[1], t, sz - 1)) return; // 2.
        if (find1(rt[2], t, sz - 1) || find2(rt[2], t, sz - 1)) return; // 1.
        ++valid;
        insert(rt[2], t, sz);
    } else {
        if (find1(rt[0], t, sz, true)) return; // 1.
        if (find2(rt[1], t, sz)) return; // 1.
        ++valid;
        insert(rt[0], t, sz);
    }
    // printf("valid : %s\n", s.c_str());
}

int n, m;

std::string domain, vpn;

inline void query(std::string &s) {
    auto t = s;
    std::reverse(t.begin(), t.end());
    int sz = t.length(), ret = 0;
    if (s[0] == '*') {
        ret += find2(rt[1], t, sz - 1);
        if (!ret) {
            ret += find2(rt[2], t, sz - 1);
        }
        ret += find1(rt[1], t, sz - 1) - find1(rt[1], t, sz, true);
        t[sz - 1] = '#';
        ret += find1(rt[2], t, sz - 1) - find1(rt[2], t, sz, true);
        ret += find1(rt[0], t, sz - 1) - find1(rt[0], t, sz - 1, true);
    } else {
        ret += find1(rt[0], t, sz, true);
        s += '*';
        ret += find2(rt[1], t, sz) - find1(rt[1], t, sz + 1, true);
        if (!ret) {
            s[sz] = '#';
            ret += find2(rt[2], t, sz) - find1(rt[2], t, sz + 1, true);
        }
    }
    printf("%d\n", ret);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        for (int i = 1; i <= n; ++i) {
            std::cin >> domain >> vpn;
            if (!valid_domain(domain)) continue;
            if (!valid_vpn(vpn)) continue;
            check_conflict(domain);
        }
        // printf("valid %d\n", valid);
        printf("%d\n", n - valid);
        valid = 0;
        scanf("%d", &m);
        while (m--) {
            std::cin >> domain;
            query(domain);
        }
    }
    return 0;
}

/*
poj.org vpn-china
www.pku.edu.cn vpn-pku1
mail.pku.edu.cn vpn-pku1
*.test.pku.edu.cn vpn-pku2
*.test2.pku.edu.cn vpn-pku2
#.pku.edu.cn vpn-pku0
*/
