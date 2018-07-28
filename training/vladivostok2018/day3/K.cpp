#include<bits/stdc++.h>

typedef long long ll;

const int N = 60;

int min[N];
int mu[N];
std::vector <int> prime;

ll mult(ll a, ll b){
    if (1.0 * a * b > 1e18){
        return 1e18;
    }
    return a * b;
}

ll power(ll a, int exp){
    ll ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = mult(ret, a);
        }
        a = mult(a, a);
    }
    return ret;
}

ll root(ll a, int exp){
    ll l = 1, r = a;
    while (l < r){
        ll mid = l + r + 1 >> 1;
        if (power(mid, exp) > a){
            r = mid - 1;
        }
        else{
            l = mid;
        }
    }
    return l;

}

ll solve(ll n){
    ll ans = 0;
    for (int i = 2; i < N; ++ i){
        ans += -mu[i] * (root(n, i) - 1);
    }
    return ans;
}

ll solveminus(ll n){
    ll ans = 0;
    for (int i = 3; i < N; i += 2){
        ans += -mu[i] * (root(n, i) - 1);
    }
    return ans;
}

int main(){
    mu[1] = 1;
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0, k, sz = prime.size(); j < N && prime[j] * i < N; ++ j){
            min[k = i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                mu[k] = 0;
                break;
            }
            mu[k] = -mu[i];
        }
    }
    ll a, b;
    scanf("%lld%lld", &a, &b);
    ll ans;
    if (a >= 0){
        ans = solve(b) - solve(a - 1);
    }
    else if (a < 0 && b >= 0){
        ans = solveminus(-a) + solve(b);
    }
    else{
        ans = solveminus(-a) - solveminus((-b) - 1);
    }
    for (ll i = -1; i <= 1; ++ i){
        if (a <= i && i <= b){
            ++ ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}

