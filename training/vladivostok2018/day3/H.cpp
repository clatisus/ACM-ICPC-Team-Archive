#include<bits/stdc++.h>

const int N = 400010;
const int moder = 1e8 + 7;

int min[N];
int mu[N];
std::vector <int> prime;
int a[N], dif[N];

bool loop(int p, int len){
    if (p % len) return false;
    for (int i = len; i < p; ++ i){
        if (dif[i] != dif[i - len]){
            return false;
        }
    }
    return true;
}

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

void init(){
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
}

void solve(int s, int p){
    for (int i = 0; i < p; ++ i){
        scanf("%d", &a[i]);
    }
    std::sort(a, a + p);
    for (int i = 0; i < p - 1; ++ i){
        dif[i] = a[i + 1] - a[i];
    }
    dif[p - 1] = a[0] - a[p - 1] + 360000;
    std::map <int, int> Hash;
    int x = p;
    while (x > 1){
        ++ Hash[min[x]];
        x /= min[x];
    }
    int peri = 1;
    for (auto u : Hash){
        //printf("%d %d\n", u.first, u.second);
        for (int i = 0; i < u.second; ++ i){
            if (loop(p, p / (peri * u.first))){
                peri *= u.first;
            }
            else{
                break;
            }
        }
    }
    int num = peri, ans = 0;
    for (int i = p / peri; i <= p; i += p / peri){
        ans = ans + powermod(s, std::__gcd(i, p));
        ans -= ans >= moder ? moder : 0;
    }
    ans = 1ll * ans * powermod(num, moder - 2) % moder;
    printf("%d\n", ans);
}

int main(){
    init();
    int s, p;
    while (scanf("%d%d", &s, &p), s != -1 || p != -1){
        solve(s, p);
    }
    return 0;
}

/*
   2 4
   0
   90000
   180000
   270000

   100 5
   0
   45000
   90000
   180000
   270000

   -1 -1
   */

