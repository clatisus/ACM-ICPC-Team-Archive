#include<bits/stdc++.h>

typedef long long ll;
const ll N = 2000010;

ll fac[N], inv[N], invf[N];
ll cat[N];
ll moder;

ll comb(ll n, ll m){
    if (n >= N) return 0;
    return 1ll * fac[n] * invf[m] % moder * invf[n - m] % moder;
}

void init(ll N){
    fac[0] = invf[0] = 1;
    for (ll i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    for (int i = 1; i < N >> 1; ++ i){
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
    for (ll i = 0; i < N >> 1; ++ i){
        cat[i] = 1ll * comb(2 * i, i) * inv[i + 1] % moder;
    }
}

ll powermod(ll a, ll exp){
    ll ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

ll a[N], b[N];
ll coe[N];

void solve(){
    ll n, p, aa, bb;
    scanf("%lld%lld%lld%lld%lld", &n, &p, &b[0], &aa, &bb);
    moder = p;
    for (ll i = 1; i <= n << 1; ++ i){
        b[i] = (1ll * aa * b[i - 1] + bb) % moder;
        a[i] = (a[i - 1] + b[i] + 1) % moder;
    }
    init((n << 1) + 5);
    for (ll i = 0; i <= 2 * n + 5; ++ i){
        coe[i] = 0;
    }
    for (ll i = n; i > 0; -- i){
        coe[2 * i - 1] = (coe[2 * i + 1] + 1ll * cat[i - 1] * cat[n - i]) % moder;
    }
    for (ll i = 2; i <= n << 1; i += 2){
        coe[i] = coe[i + 1];
    }
    ll ans = 0;
    for (ll i = 1; i <= n << 1; ++ i){
       ans = (ans + (cat[n] - 2ll * coe[i]) * a[i]) % moder;
       //prllf("%lld%c", coe[i], " \n"[i == n << 1]);
    }
    ans = 1ll * ans * powermod(cat[n], moder - 2) % moder;
    ans += ans < 0 ? moder : 0;
    printf("%lld\n", ans);
}

int main(){
    ll test;
    scanf("%lld", &test);
    while (test --){
        solve();
    }
    return 0;
}

