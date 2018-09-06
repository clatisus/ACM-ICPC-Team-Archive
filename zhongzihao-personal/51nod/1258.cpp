#include<bits/stdc++.h>

const int moder = 1e9 + 7;
const int N = 50010;
typedef long long ll;

int inv[N], invf[N];

void init(){
    inv[1] = invf[0] = invf[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = (moder - 1ll * (moder / i) * inv[moder % i] % moder) % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
}

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a %moder;
    }
    return ret;
}

int interpolation(std::vector <int> vec, int x){
    int n = vec.size() - 1;
    std::vector <int> pre(n + 1), suf(n + 1);
    pre[0] = suf[n] = 1;
    for (int i = 1; i <= n; ++ i){
        pre[i] = 1ll * pre[i - 1] * (x - i + 1) % moder;
        pre[i] += pre[i] < 0 ? moder : 0;
    }
    for (int i = n - 1; i >= 0; -- i){
        suf[i] = 1ll * suf[i + 1] * (x - i - 1) % moder;
        suf[i] += suf[i] < 0 ? moder : 0;
    }
    int ans = 0;
    for (int i = 0; i <= n; ++ i){
        ans = (ans + ((n - i) & 1 ? -1ll : 1ll) * vec[i] * pre[i] % moder * suf[i] % moder * invf[i] % moder * invf[n - i]) % moder;
    }
    ans += ans < 0 ? moder : 0;
    return ans;
}

int min[N];
int f[N];
int pre[N];

int main(){
    init();
    int test;
    scanf("%d", &test);
    while (test --){
        memset(min, 0, sizeof(min));
        memset(f, 0, sizeof(f));
        memset(pre, 0, sizeof(pre));
        std::vector <int> prime;
        ll n;
        int k;
        scanf("%lld%d", &n, &k);
        n %= moder;
        f[1] = pre[1] = 1;
        for (int i = 2; i <= k + 1; ++ i){
            if (!min[i]){
                min[i] = i;
                f[i] = powermod(i, k);
                prime.push_back(i);
            }
            for (int j = 0, u, sz = prime.size(); j < sz && i * prime[j] <= k + 1; ++ j){
                min[u = i * prime[j]] = prime[j];
                f[u] = 1ll * f[i] * f[prime[j]] % moder;
                if (i % prime[j] == 0){
                    break;
                }
            }
            pre[i] = pre[i - 1] + f[i];
            pre[i] -= pre[i] >= moder ? moder : 0;
        }
        std::vector <int> vec;
        for (int i = 0; i <= k + 1; ++ i){
            vec.push_back(pre[i]);
        }
        printf("%d\n", interpolation(vec, n));
    }
    return 0;
}
