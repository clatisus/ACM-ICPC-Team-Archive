#include<bits/stdc++.h>

const int N = 50;
typedef long long ll;
typedef std::pair <std::string, std::string> pss;

char s[N];
std::map <pss, ll> Hash[N];

int main(){
    int n;
    scanf("%d%s", &n, s + 1);
    Hash[0][{"", ""}] = 1;
    for (int i = 1; i <= n << 1; ++ i){
        for (auto &u : Hash[i - 1]){
            auto &s1 = u.first.first;
            auto &s2 = u.first.second;
            if (s1.size() < n && (s1.size() + s2.size() < n || s2[n - s1.size() - 1] == s[i])){
                Hash[i][{s1 + s[i], s2}] += u.second;
            }
            if (s2.size() < n && (s1.size() + s2.size() < n || s1[n - s2.size() - 1] == s[i])){
                Hash[i][{s1, s2 + s[i]}] += u.second;
            }
        }
    }
    ll ans = 0;
    for (auto u : Hash[n << 1]){
        ans += u.second;
    }
    printf("%lld\n", ans);
    return 0;
}
