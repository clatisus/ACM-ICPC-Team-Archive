#include <bits/stdc++.h>

#define ll long long
#define MAXS (40)

ll pow3[MAXS];
std::pair<ll, ll> s, t;

void read(std::pair<ll, ll> &pos) {
    static char str[40];
    scanf("%s", str);
    pos = {0, 0};
    for (int i = 0; str[i]; ++i) {
        switch (str[i]) {
            case 'c': ++ pos.first; pos.second *= 3; break;
            case 'g': -- pos.first; pos.second /= 3; break;
            case 's':
                ++ pos.second;
                if (pos.second >= pow3[pos.first]) {
                    pos.second -= pow3[pos.first];
                }
                break;
            case 'a':
                -- pos.second;
                if (pos.second < 0) {
                    pos.second += pow3[pos.first];
                }
                break;
        }
    }
}

std::string calc(ll l, ll p1, ll p2) {
    std::string ret;
    if (p1 == p2) return ret;
    ll ans_a, ans_s;
    if (p1 > p2) {
        ans_a = p1 - p2;
        ans_s = p2 + pow3[l] - p1;
    } else {
        ans_s = p2 - p1;
        ans_a = p1 + pow3[l] - p2;
    }
    if (ans_a < ans_s) {
        for (int i = 0; i < ans_a; ++i) ret += "a";
    } else {
        for (int i = 0; i < ans_s; ++i) ret += "s";
    }
    return ret;
}

std::string go(std::pair<ll, ll> &pos, ll l) {
    std::string ret;
    if (pos.first == l) return ret;
    while (pos.first != l) {
        int t = pos.second % 3;
        if (t == 1) {
            ret += "a";
            -- pos.second;
        } else if (t == 2) {
            ret += "s";
            ++ pos.second;
            if (pos.second == pow3[pos.first]) pos.second = 0;
        }
        if (pos.first > l) {
            ret += "g";
            -- pos.first;
            pos.second /= 3;
        } else {
            ret += "c";
            ++ pos.first;
            pos.second *= 3;
        }
    }
    return ret;
}

std::string myreverse(std::string a) {
    std::reverse(a.begin(), a.end());
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] == 'c') a[i] = 'g';
        else if (a[i] == 'g') a[i] = 'c';
        else if (a[i] == 's') a[i] = 'a';
        else if (a[i] == 'a') a[i] = 's';
    }
    return a;
}

int main() {
    pow3[0] = 1ll;
    for (int i = 1; i <= 35; ++i) {
        pow3[i] = pow3[i - 1] * 3ll;
    }
    read(s);
    read(t);
    //printf("%lld %lld\n", s.first, s.second);
    //printf("%lld %lld\n", t.first, t.second);
    int lmt = std::max(s.first, t.first);
    int min = INT_MAX;
    std::string ans;
    for (int i = 0; i <= lmt; ++i) {
        auto p = s;
        auto q = t;
        std::string left = go(p, i);
        std::string right = go(q, i);

        ll a = p.second, b = q.second;
        if (a > b) std::swap(a, b);
        ll dis = std::min(b - a, a + pow3[i] - b);
        if (dis > min) continue;

        std::string mid = calc(i, p.second, q.second);
        if (left.length() + right.length() + mid.length() < min) {
            min = left.length() + right.length() + mid.length();
            ans = left + mid + myreverse(right);
        }
    }
    printf("%s\n", ans.c_str());
    return 0;
}
