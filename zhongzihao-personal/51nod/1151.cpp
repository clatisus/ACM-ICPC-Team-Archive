#include<bits/stdc++.h>

const int N = 1010;
typedef long long ll;
typedef __int128 i128;
typedef std::pair <ll, ll> pii;

ll moder;
ll s[N][N];
ll inv[N];
int invcnt[N];
ll power[N];
ll poly[N];
ll inter[N];

ll eucinv(ll a, ll moder){
    ll b = moder, s = 1, t = 0;
    while (b){
        ll tmp = a, q = a / b;
        a = b, b = tmp % a;
        tmp = s;
        s = t;
        t = tmp - s * q;
    }
    if (a > 1) return -1;
    return s < 0 ? s + moder : s;
}

void initpower(int p, int e){
    power[0] = 1;
    for (int i = 1; i <= e; ++ i){
        power[i] = power[i - 1] * p;
    }
}

void inits(int p, int e){
    s[0][0] = 1;
    for (int i = 1; i <= p; ++ i){
        for (int j = 1, sz = std::min(p, e); j <= sz; ++ j){
            s[i][j] = j > i ? 0 : ((i128) (i - 1) * s[i - 1][j] + s[i - 1][j - 1]) % moder;
        }
    }
}

void initinv(int p, int e){
    inv[0] = 1;
    for (int i = 1, sz = std::max(2 * e - 2, p - 1); i <= sz; ++ i){
        ll x = i;
        invcnt[i] = 0;
        while (x % p == 0){
            ++ invcnt[i];
            x /= p;
        }
        invcnt[i] += invcnt[i - 1];
        inv[i] = (i128) inv[i - 1] * eucinv(x, moder) % moder;
    }
}

ll calcinter(ll u, int v, int p, int e){
    ll ans = 0, now = 1, mult = (i128) u * p % moder;
    for (int i = 0, sz = std::min(v, e - 1); i <= sz; ++ i){
        ans = (ans + (i128) now * s[v + 1][i + 1]) % moder;
        now = (i128) now * mult % moder;
    }
    return ans;
}

void initpoly(int p, int e){
    poly[0] = 1;
    for (int i = 1; i <= 2 * e - 2; ++ i){
        poly[i] = (i128) poly[i - 1] * calcinter(i - 1, p - 1, p, e) % moder * inv[p - 1] % moder;
    }
    for (int i = 0; i <= 2 * e - 2; ++ i){
        inter[i] = (i128) poly[i] * inv[i] % moder * inv[2 * e - 2 - i] % moder;
    }
}

ll powermod(ll a, ll exp){
    ll ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = (i128) ret * a % moder;
        }
        a = (i128) a * a % moder;
    }
    return ret;
}

pii solve(ll n, int p, int e){
    initpower(p, e);
    moder = power[e];
    inits(p, e);
    initinv(p, e);
    initpoly(p, e);
    int max = e + invcnt[2 * e - 2];
    ll ans = 1, cnt = 0;
    while (n){
        ll u = n / p, v = n % p;
        n = u;
        cnt += u;
        ans = (i128) ans * calcinter(u, v, p, e) % moder;
        int sz = 2 * e - 2;
        if (u <= sz){
            ans = (i128) ans * poly[u] % moder;
            continue;
        }
        std::vector <pii> pre(sz + 1), suf(sz + 1);
        pre[0] = suf[sz] = {1, 0};
        for (int i = 1; i <= sz; ++ i){
            ll x = u - i + 1;
            while (x % p == 0 && pre[i].second < max){
                ++ pre[i].second;
                x /= p;
            }
            pre[i].second += pre[i - 1].second;
            pre[i].first = (i128) pre[i - 1].first * x % moder;
        }
        for (int i = sz - 1; i >= 0; -- i){
            ll x = u - i - 1;
            while (x % p == 0 && suf[i].second < max){
                ++ suf[i].second;
                x /= p;
            }
            suf[i].second += suf[i + 1].second;
            suf[i].first = (i128) suf[i + 1].first * x % moder;
        }
        ll sum = 0;
        for (int i = 0; i <= sz; ++ i){
            int cnt = pre[i].second + suf[i].second - invcnt[i] - invcnt[sz - i];
            if (cnt >= e) continue;
            ll tmp = power[cnt];
            //<==>(2 * e - 2 - i & 1 ? -1ll: 1ll)
            sum = (sum + (i128) (i & 1 ? -1: 1) * tmp * pre[i].first % moder * suf[i].first % moder * inter[i]) % moder;
        }
        sum += sum < 0 ? moder : 0;
        ans = (i128) ans * sum % moder;
    }
    ans = (i128) ans * powermod(s[p][1], cnt) % moder;
    return {ans, cnt};
}

int main(){
    ll n;
    scanf("%lld", &n);
    pii five = solve(n, 5, 18);
    ll mod5 = moder;
    pii two = solve(n, 2, 18);
    ll mod2 = moder;
    two.second -= five.second;
    two.first = (i128) two.first * powermod(eucinv(5, moder), five.second) % moder * (two.second >= 18 ? 0 : power[two.second]) % moder;
    moder = mod5;
    five.first = (i128) five.first * powermod(eucinv(2, moder), five.second) % moder;
    moder = mod5 * mod2;
    ll ans = ((i128) two.first * mod5 % moder * eucinv(mod5, mod2) + (i128) five.first * mod2 % moder * eucinv(mod2, mod5)) % moder;
    printf("%lld\n", ans);
    return 0;
}
