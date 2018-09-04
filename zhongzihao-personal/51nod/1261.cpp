#include<bits/stdc++.h>

typedef long long ll;
const int N = 4510;
const int moder = 1e9 + 7;
typedef std::pair <int, int> pii;

int powermod(ll a, ll exp, int moder){
    int ret = 1;
    a %= moder;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int inv[N];

int comb(ll n, int m){
    n %= moder;
    int ret = 1;
    for (int i = 0; i < m; ++ i){
        ret = 1ll * ret * (n - i) % moder * inv[i + 1] % moder;
    }
    return ret;
}

ll cnt[N];
int dp[2][N][10];

int main(){
    for (int i = 1; i < N; ++ i){
        inv[i] = powermod(i, moder - 2, moder);
    }
    ll n;
    int k;
    scanf("%lld%d", &n, &k);
    int mod = 9 * k;
    int remain = 9 - powermod(10, n, mod);
    remain += remain < 0 ? mod : 0;
    int begin = -1, period = -1, now = 1 % mod;
    std::set <pii> set;
    for (int i = 0; i <= n; ++ i){
        auto u = set.lower_bound({now, INT_MIN});
        if (u != set.end() && u -> first == now){
            begin = i;
            period = i - u -> second;
            break;
        }
        set.insert({now, i});
        ++ cnt[now];
        now = 10 * now % mod;
    }
    if (begin != -1){
        n -= begin;
        for (auto u : set){
            if (u.second >= begin - period){
                u.second -= begin - period;
                cnt[u.first] += n / period + (n % period >= u.second);
            }
        }
    }
    now = 0;
    dp[0][0][0] = 1;
    for (int i = 0; i < N; ++ i){
        if (!cnt[i]) continue;
        memset(dp[now ^ 1], 0, sizeof(dp[now]));
        for (int j = 0; j < mod; ++ j){
            for (int k = 0; k <= 8; ++ k){
                if (!dp[now][j][k]) continue;
                for (int u = 0; u + k <= 8; ++ u){
                    int &v = dp[now ^ 1][(j + i * u) % mod][u + k];
                    v = (v + 1ll * dp[now][j][k] * comb(cnt[i] + u - 1, u)) % moder;
                }
            }
        }
        now ^= 1;
    }
    printf("%d\n", dp[now][remain][8]);
    return 0;
}
