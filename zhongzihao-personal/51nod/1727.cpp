#include<bits/stdc++.h>

const int N = 1000010;
const int M = 100;
typedef long long ll;
const ll moder = (ll) 1e10 + 61;

int min[N];
std::vector <int> prime;

ll comb[M][M];

void init(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, sz = prime.size(); j < sz && prime[j] * i < N; ++ j){
            min[i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    for (int i = 0; i < M; ++ i){
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j){
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % moder;
        }
    }
}

ll c[M], d[M];

ll solve(){
    ll n;
    scanf("%lld", &n);
    if (n == 1){
        return 1;
    }
    memset(c, 0, sizeof(c));
    memset(d, 0, sizeof(d));
    std::map <ll, int> Hash;
    for (auto u : prime){
        if (n % u == 0){
            while (n % u == 0){
                ++ Hash[u];
                n /= u;
            }
        }
    }
    if (n > 1){
        Hash[n] = 1;
    }
    int sum = 0;
    for (auto u : Hash){
        sum += u.second;
    }
    for (int i = 1; i <= sum; ++ i){
        d[i] = 1;
        for (auto u : Hash){
            d[i] = (__int128) d[i] * comb[u.second + i - 1][i - 1] % moder;
        }
    }
    for (int i = 1; i <= sum; ++ i){
        for (int j = 1; j <= i; ++ j){
            c[i] = (c[i] + (__int128) (i - j & 1 ? -1 : 1) * comb[i][j] * d[j]) % moder;
        }
        c[i] += c[i] < 0 ? moder : 0;
    }
    ll ans = 0;
    for (int i = 1; i <= sum; ++ i){
        ans = (ans + (__int128) c[i] * (c[i] + c[i + 1])) % moder;
    }
    return (ans + ans) % moder;
}

int main(){
    init();
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
