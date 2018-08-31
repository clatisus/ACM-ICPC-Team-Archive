#include<bits/stdc++.h>

const int N = 10000001;

int min[N];
std::vector <int> prime;

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

int powermod(int a, int exp, int moder){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int main(){
    init();
    int q, n;
    scanf("%d%d", &q, &n);
    std::vector <int> nprime, ans;
    int x = n;
    for (int i = 2; i * i <= x; ++ i){
        if (x % i == 0){
            while (x % i == 0){
                x /= i;
            }
            nprime.push_back(i);
        }
    }
    if (x > 1){
        nprime.push_back(x);
    }
    for (auto u : prime){
        if (powermod(q, n, u) == 1){
            bool flag = true;
            for (auto v : nprime){
                if (powermod(q, n / v, u) == 1){
                    flag = false;
                    break;
                }
            }
            if (flag){
                ans.push_back(u);
            }
        }
    }
    printf("%d\n", (int) ans.size());
    for (auto u : ans){
        printf("%d\n", u);
    }
    return 0;
}
