#include<bits/stdc++.h>

const int N = 1000010;
const int moder = (int) 1e9 + 7;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int fib[N];
int cnt[N];
int min[N], mu[N];
std::vector <int> prime;

void init(){
    fib[1] = 1;
    for (int i = 2; i < N; ++ i){
        fib[i] = fib[i - 1] + fib[i - 2];
        fib[i] -= fib[i] >= moder ? moder : 0;
    }
    mu[1] = 1;
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0, k, sz = prime.size(); j < sz && i * prime[j] < N; ++ j){
            min[k = i * prime[j]] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
            mu[k] = -mu[i];
        }
    }
}

int main(){
    init();
    int n;
    scanf("%d", &n);
    for (int i = 0, x; i < n; ++ i){
        scanf("%d", &x);
        ++ cnt[x];
    }
    for (int i = 1; i < N; ++ i){
        for (int j = i << 1; j < N; j += i){
            cnt[i] += cnt[j];
        }
    }
    int ans = 1;
    for (int i = 1; i < N; ++ i){
        int inv = powermod(fib[i], moder - 2);
        for (int j = i; j < N; j += i){
            if (!cnt[j] || !mu[j / i]) continue;
            ans = 1ll * ans * (mu[j / i] == 1 ? fib[i] : inv) % moder;
        }
    }
    printf("%d\n", ans);
    return 0;
}
