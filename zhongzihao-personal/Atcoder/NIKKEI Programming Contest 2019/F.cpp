#include<bits/stdc++.h>

const int N = 200010;
typedef long long ll;
typedef std::pair <ll, ll> pii;

struct jewel{
    ll value, id;
    bool ispair;
    
    bool operator < (const jewel &j)const{
        if (value != j.value){
            return value > j.value;
        }
        return ispair > j.ispair;
    }
};

std::vector <int> vec[N];

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0, c, v; i < n; ++ i){
        scanf("%d%d", &c, &v);
        vec[c].push_back(v);
    }
    std::vector <jewel> jewels;
    std::multiset <pii> singin, singout, doubin, doubout, tripout;
    for (int i = 1; i <= k; ++ i){
        std::sort(vec[i].begin(), vec[i].end(), std::greater <int>());
        ll x = vec[i][0] + vec[i][1];
        jewels.push_back({x, i, true});
        doubout.insert({x << 1, i});
        if ((int) vec[i].size() >= 3){
            tripout.insert({(x + vec[i][2]) << 1, i});
        }
        for (int j = 2, sz = vec[i].size(); j < sz; ++ j){
            jewels.push_back({vec[i][j] << 1, i, false});
        }
    }
    std::sort(jewels.begin(), jewels.end());
    puts("-1");
    long long ans = 0;
    for (int i = 2, j = 0, cnt = 0; i <= n; ++ i){
        ll value = jewels[j].value, id = jewels[j].id;
        int num = jewels[j].ispair ? 2 : 1;
        if (cnt + num <= i){
            cnt += num;
            ans += num * value;
            if (num == 1){
                auto u = singout.find({value, id});
                singin.insert(*u);
                singout.erase(u);
            }
            else{
                auto u = doubout.find({value << 1, id});
                doubin.insert(*u);
                doubout.erase(u);
                if ((int) vec[id].size() >= 3){
                    u = tripout.find({((ll) vec[id][0] + vec[id][1] + vec[id][2]) * 2, id});
                    tripout.erase(u);
                }
                for (int j = 2, sz = vec[id].size(); j < sz; ++ j){
                    singout.insert({vec[id][j] << 1, id});
                }
            }
            ++ j;
        }
        if (cnt == i){
            printf("%lld\n", ans >> 1);
            continue;
        }
        ll max = LLONG_MIN;
        if (!singout.empty()){
            max = std::max(max, (-- singout.end()) -> first);
        }
        if (!singin.empty() && !doubout.empty()){
            ll x = singin.begin() -> first;
            ll y = (-- doubout.end()) -> first;
            max = std::max(max, y - x);
        }
        if (!doubin.empty() && !tripout.empty()){
            ll x = doubin.begin() -> first;
            ll y = (-- tripout.end()) -> first;
            max = std::max(max, y - x);
        }
        if (max == LLONG_MIN){
            puts("-1");
            continue;
        }
        printf("%lld\n", (ans + max) >> 1);
    }
    return 0;
}
