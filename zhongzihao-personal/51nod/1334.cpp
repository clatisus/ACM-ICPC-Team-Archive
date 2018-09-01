#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair <ll, int> pii;

const ll INF = 2e18;
const int N = 3010;

std::vector <int> pre[N];

ll mult(ll a, ll b){
    if (1.0 * a * b > 1.5 * INF){
        return INF;
    }
    return std::min(INF, a * b);
}

ll calc(ll n, int w){
    std::vector <pii> vec = {{1, 1}};
    ll ans = 0;
    while (!vec.empty()){
        std::vector <pii> tmp;
        for (auto u : vec){
            ll div = mult(u.first, w);
            if (div == INF){
                ans += n >= u.first;
            }
            else{
                ans += n / div + (n % div >= u.first);
            }
            for (auto v : pre[u.second]){
                ll x = mult(u.first, v);
                if (x <= n){
                    tmp.push_back({x, v});
                }
            }
        }
        tmp.swap(vec);
    }
    return ans;
}

void solve(){
    ll l, r;
    int w;
    scanf("%lld%lld%d", &l, &r, &w);
    for (int i = 1; i < w; ++ i){
        pre[i].clear();
        for (int j = 2; j < w; ++ j){
            if (i * j % w == j){
                pre[i].push_back(j);
            }
        }
    }
    printf("%lld\n", calc(r, w) - calc(l - 1, w));
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
