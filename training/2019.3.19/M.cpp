#include<bits/stdc++.h>

const int N = 1 << 17;
typedef std::pair <int, int> pii;
const int moder = (int) 1e9 + 7;

std::vector <int> vec[N];
int ans = 0;

void solve(std::vector <pii> vec, int bit){
    if (bit == -1){
        return;
    }
    bool haszero = false, hasone = false, haseither = false;
    for (auto u : vec){
        if (u.second >> bit & 1){
            haseither = true;
        }
        else{
            if (u.first >> bit & 1){
                hasone = true;
            }
            else{
                haszero = true;
            }
        }
    }
    if (haseither){
        if (haszero && hasone){
            ans = 0;
            return;
        }
        if (!haszero && !hasone){
            ans <<= 1;
            ans -= ans >= moder ? moder : 0;
        }
        solve(vec, bit - 1);
    } else{
        if (!hasone || !haszero){
            ans = 0;
            return;
        }
        std::vector <pii> one, zero;
        for (auto u : vec){
            if (u.first >> bit & 1){
                one.push_back(u);
            }
            else{
                zero.push_back(u);
            }
        }
        solve(one, bit - 1);
        solve(zero, bit - 1);
    }
}

int main(){
    int n, m;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < 1 << m; ++ i){
        int x;
        scanf("%d", &x);
        vec[x].push_back(i);
    }
    std::vector <pii> vvec;
    for (int i = 1; i <= n; ++ i){
        int min = INT_MAX, max = 0;
        for (auto u : vec[i]){
            min &= u;
            max |= u;
        }
        if (vec[i].size() != 1 << (__builtin_popcount(min ^ max))){
            puts("0");
            return 0;
        }
        vvec.push_back({min, max ^ min});
    }
    ans = 1;
    solve(vvec, m - 1);
    printf("%d\n", ans);
    return 0;
}
