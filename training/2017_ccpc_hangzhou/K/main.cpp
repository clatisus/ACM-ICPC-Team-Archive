#include<bits/stdc++.h>

typedef long long ll;

const int N = 100010;
const int M = 1010;

inline ll lowbit(ll n){return n & (-n);}

int c[M][M], total[M];
ll a[N], b[N];
ll quot;

void divide(ll a, ll b, ll &quot, ll &mod){
    quot = a / b;
    mod = a % b;
    if (a < 0 && mod){
        mod += b;
        -- quot;
    }
}

void add(int sit, int value){
    ll _quot, mod;
    divide(b[sit], a[sit], _quot, mod);
    for (++ mod; mod < M; mod += lowbit(mod)){
        c[a[sit]][mod] += value;
    }
    quot += _quot * value;
    total[a[sit]] += value;
}

int query(int sit1, int sit2){
    int ret = 0;
    for ( ; sit2; sit2 -= lowbit(sit2)){
        ret += c[sit1][sit2];
    }
    return ret;
}

ll calc(ll t){
    ll sum = quot;
    for (int i = 1; i < M; ++ i){
        sum += (t / i) * total[i];
        sum += total[i] - query(i, i - t % i);
    }
    return sum;
}

void solve(){
    memset(c, 0, sizeof(c));
    memset(total, 0, sizeof(total));
    quot = 0;
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i){
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; ++ i){
        scanf("%lld", &b[i]);
        b[i] = -b[i];
        add(i, 1);
    }
    while (m --){
        int type;
        scanf("%d", &type);
        if (type == 3){
            int k;
            scanf("%d", &k);
            ll left = 0, right = 1.1e12;
            while (left < right){
                ll mid = left + right >> 1;
                if (calc(mid) >= k){
                    right = mid;
                }
                else{
                    left = mid + 1;
                }
            }
            printf("%lld\n", left);
        }
        else{
            int x, y;
            scanf("%d%d", &x, &y);
            -- x;
            add(x, -1);
            if (type == 1){
                a[x] = y;
            }
            else{
                b[x] = -y;
            }
            add(x, 1);
        }
    }
}

int main(){
    //freopen("input.txt", "r", stdin);
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

