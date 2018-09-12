#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair <int, int> pii;

int main(){
    ll n;
    scanf("%lld", &n);
    std::vector <int> prime = {11, 13, 17, 19, 23};
    int lcm = 11 * 13 * 17 * 19 * 23;
    const int N = 5;
    std::set <int> set[N];
    for (int i = 0; i < N; ++ i){
        int p = prime[i];
        for (int j = 0; j < p; ++ j){
            for (int k = 0; k < p; ++ k){
                if ((j * j + k * k) % p == n % p){
                    set[i].insert(j);
                    set[i].insert(k);
                }
            }
        }
    }
    std::vector <int> possible;
    for (int i = 0; i < lcm; ++ i){
        bool flag = true;
        for (int j = 0; j < N; ++ j){
            if (!set[j].count(i % prime[j])){
                flag = false;
                break;
            }
        }
        if (flag){
            possible.push_back(i);
        }
    }
    std::vector <pii> ans;
    for (int i = 0; 1ll * i * i <= n - 1ll * i * i; i += lcm){
        for (auto u : possible){
            int x = i + u;
            ll y = n - 1ll * x * x;
            if (y < 1ll * x * x) break;
            int z = std::sqrt(y);
            while (1ll * z * z < y){
                ++ z;
            }
            if (1ll * z * z == y && x <= z){
                ans.push_back({x, z});
            }
        }
    }
    if (ans.empty()){
        puts("No Solution");
        return 0;
    }
    for (auto u : ans){
        printf("%d %d\n", u.first, u.second);
    }
    return 0;
}
