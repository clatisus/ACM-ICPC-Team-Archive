#include <bits/stdc++.h>
 
#define ll long long
#define i128 __int128
#define lmt (43046721) // 3 ^ 16
 
std::map<std::vector<int>, std::string> f[5];
std::map<std::vector<ll>, std::string> zero5;
 
bool solve(ll a, ll b, ll c) {
    if (a <= lmt && b <= lmt && c <= lmt) {
        auto p = std::vector<int>{(int)a, (int)b, (int)c};
        for (int i = 0; i <= 4; ++i) {
            if (f[i].count(p)) {
                printf("%s\n", f[i][p].c_str());
                return true;
            }
        }
    }
    if (zero5.count(std::vector<ll>{a, b, c})) {
        printf("%s\n", zero5[std::vector<ll>{a, b, c}].c_str());
        return true;
    }
    /*
    (p + q)    p       0    = aa
       0    (q + r)    q    = bb
       r       0    (p + r) = cc
    */
    for (auto x : f[4]) {
        auto v = x.first;
        if (!v[0] || !v[1] || !v[2]) continue;
        i128 p = v[0], q = v[1], r = v[2];
        i128 aa = a, bb = b, cc = c;
        i128 d = p * q * r + (p + q) * (p + r) * (q + r);
         
        assert(d != 0);
         
        i128 y0 = aa * (q + r) * (p + r) + cc * p * q - bb * p * (p + r);
        i128 y1 = bb * (p + q) * (p + r) + aa * q * r - cc * q * (p + q);
        i128 y2 = cc * (q + r) * (p + q) + bb * p * r - aa * r * (q + r);
        if (y0 % d || y1 % d || y2 % d) continue;
        y0 /= d; y1 /= d; y2 /= d;
        if (y0 < 0 || y1 < 0 || y2 < 0 || y0 >= lmt || y1 >= lmt || y2 >= lmt) continue;
        auto pp = std::vector<int>{(int)y0, (int)y1, (int)y2};
        if (f[4].count(pp)) {
            printf("%s%s\n", x.second.c_str(), f[4][pp].c_str());
            return true;
        }
    }
    return false;
}
 
int main() {
    f[0][std::vector<int>{1, 1, 1}] = "?";
    f[0][std::vector<int>{1, 0, 0}] = "R";
    f[0][std::vector<int>{0, 1, 0}] = "S";
    f[0][std::vector<int>{0, 0, 1}] = "P";
    for (int i = 0; i < 4; ++i) {
        for (auto p : f[i]) for (auto q : f[i]) {
            auto x = p.first, y = q.first;
            f[i + 1][std::vector<int>{
                x[0] * y[0] + x[0] * y[1] + x[1] * y[0],
                x[1] * y[1] + x[1] * y[2] + x[2] * y[1],
                x[2] * y[2] + x[2] * y[0] + x[0] * y[2]
            }] = p.second + q.second;
        }
    }
     
    std::vector<std::pair<std::vector<ll>, std::string> > zero;
    for (auto p : f[4]) {
        auto pp = p.first;
        if (!pp[0] || !pp[1] || !pp[2]) {
            zero.push_back({std::vector<ll>{(ll)pp[0], (ll)pp[1], (ll)pp[2]}, p.second});
        }
    }
    for (int i = 0, sz = zero.size(); i < sz; ++i) {
        for (int j = i; j < sz; ++j) {
            auto x = zero[i].first, y = zero[j].first;
            zero5[std::vector<ll>{
                x[0] * y[0] + x[0] * y[1] + x[1] * y[0],
                x[1] * y[1] + x[1] * y[2] + x[2] * y[1],
                x[2] * y[2] + x[2] * y[0] + x[0] * y[2]
            }] = zero[i].second + zero[j].second;
        }
    }
     
    int T;
    scanf("%d", &T);
    while (T --) {
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        if (!solve(a, b, c)) {
            puts("Impossible");
        }
    }
    return 0;
}
