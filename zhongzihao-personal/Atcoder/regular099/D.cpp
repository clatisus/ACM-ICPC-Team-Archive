#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair <ll, int> pli;

bool operator < (pli p1, pli p2){
    return p1.first * p2.second < p2.first * p1.second;
}

int sum(ll n){
    int ret = 0;
    while (n){
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

int main(){
    std::vector <ll> vec;
    for (int i = 0; i <= 13; ++ i){
        for (int j = 0; j < 1000; ++ j){
            ll x = j;
            for (int k = 0; k < i; ++ k){
                x = x * 10 + 9;
            }
            vec.push_back(x);
        }
    }
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    vec.erase(vec.begin());
    std::vector <pli> vec1;
    for (auto u : vec){
        vec1.push_back({u, sum(u)});
    }
    vec.clear();
    pli min;
    for (int i = vec1.size() - 1; i >= 0; -- i){
        if (i == vec1.size() - 1){
            min = vec1[i];
            vec.push_back(vec1[i].first);
            continue;
        }
        if (min < vec1[i]) continue;
        vec.push_back(vec1[i].first);
        min = std::min(min, vec1[i]);
    }
    std::reverse(vec.begin(), vec.end());
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++ i){
        printf("%lld\n", vec[i]);
    }
    return 0;
}
