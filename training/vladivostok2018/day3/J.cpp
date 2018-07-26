#include<bits/stdc++.h>

const int N = 500010;
typedef long long ll;

int min[N], mu[N], sum[N];
std::vector <int> prime;

int main(){
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
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        for (int j = i; j <= n; j += i){
            sum[j] += n / i * mu[i];
        }
    }
    sum[1] = n - 1;
    ll total = 0;
    for (int i = 1; i <= n; ++ i){
        total += 1ll * sum[i] * (n - 1 - sum[i]);
    }
    total = 1ll * n * (n - 1) * (n - 2) / 6 - total / 2;
    printf("%lld\n", total);
    return 0;
}
