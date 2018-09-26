#include<bits/stdc++.h>

const int N = 1000010;
const int moder = 1e9 + 7;
typedef long long ll;

int min[N];
std::vector <int> prime;
ll max[N];

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

ll calc(ll x, ll p){
    ll ret = 0;
    while (x){
        ret += x / p;
        x /= p;
    }
    return ret;
}

ll power[N];
int maxbit;

ll solve(ll x, int p){
    ll ret = 0;
    for (int i = maxbit; i >= 0; -- i){
        ret = ret * p;
        if (x < 0) continue;
        int tmp = x / power[i];
        if (x % power[i] >= power[i] - i){
            ++ tmp;
        }
        x -= tmp * power[i];
        ret += tmp;
    }
    return ret * p;
}

int main(){
    init();
    int n, k;
    scanf("%d%d", &n, &k);
    for (auto u : prime){
        power[0] = 1;
        for (int i = 1; i < N; ++ i){
            if (1.0 * power[i - 1] * u > 2e16){
                maxbit = i - 1;
                break;
            }
            power[i] = power[i - 1] * u + 1;
        }
        for (int i = u; i < N; i += u){
            max[i] = std::max(max[i], solve(calc(i, u) * k, u));
        }
    }
    ll mmax = 0;
    int ans = 0;
    for (int i = 2; i <= n; ++ i){
        mmax = std::max(mmax, max[i]);
        ans = (ans + mmax) % moder;
    }
    printf("%d\n", ans);
    return 0;
}
