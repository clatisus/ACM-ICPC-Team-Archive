#include<bits/stdc++.h>

const int N = 1000010;
const int M = 10000010;
typedef long long ll;

int min[N];
std::vector <int> prime;

void init(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, sz = prime.size(); j < sz && i * prime[j] < N; ++ j){
            min[i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
        }
    }
}

int f[N];
int sqroot;
ll n;

inline int getsit(ll x){
    if (x > INT_MAX) return sqroot + n / x;
    return x * x > n ? sqroot + n / x : x;
}

void calcf(){
    sqroot = std::sqrt(n);
    std::vector <ll> vec;
    std::vector <int> id;
    for (ll i = 1, j; i <= n; i = j + 1){
        ll x = n / i;
        int sit = getsit(x);
        j = n / x;
        f[sit] = x;
        vec.push_back(x);
        id.push_back(sit);
    }
    for (int k = 0, szk = prime.size(); k < szk; ++ k){
        int p = prime[k];
        if (1ll * p * p > n) break;
        for (int i = 0, szi = vec.size(); i < szi; ++ i){
            ll x = vec[i];
            if (x < 1ll * p * p) break;
            int sit = getsit(x / p);
            f[id[i]] += -f[sit] + k + 1;
        } 
    }
}

ll sieve[M];

int main(){
    init();
    ll x;
    scanf("%lld", &x);
    ll left = std::max(2ll, (ll) (x * (std::log(x * std::log(x)) - 1) + x * (std::log(std::log(x)) - 2) / std::log(x) - 3e6)), right = left + 6e6;
    n = left - 1;
    calcf();
    ll y = f[getsit(n)] - 1;
    for (ll i = left; i <= right; ++ i){
        sieve[i - left] = i;
    }
    for (auto u : prime){
        for (ll i = (left + u - 1) / u * u; i <= right; i += u){
            if (sieve[i - left] == u) continue;
            while (sieve[i - left] % u == 0){
                sieve[i - left] /= u;
            }
        }
    }
    for (ll i = left; i <= right; ++ i){
        if (sieve[i - left] == i){
            ++ y;
            if (y == x){
                printf("%lld\n", i);
                return 0;
            }
        }
    }
    return 0;
}
