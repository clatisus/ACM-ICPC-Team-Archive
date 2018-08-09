#include<bits/stdc++.h>
 
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
const int N = 100010;
 
int min[N];
std::vector <int> prime;
 
int main(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (int j = 0, k, sz = prime.size(); j < sz && prime[j] * i < N; ++ j){
            min[k = prime[j] * i] = prime[j];
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    int m;
    scanf("%d", &m);
    int max = 0, sit;
    for (auto u : prime){
        if (u == 2 || u > m) continue;
        int i;
        for (i = 2; i < u - 1; ++ i){
            if (powermod(i, u - 1 >> 1, u) != 1){
                break;
            }
        }
        if (max < i){
            max = i;
            sit = u;
        }
    }
    //printf("%d\n", max);
    printf("%d %lld %d %d\n", 1, 1ll * sit * (sit - 1) / 2, 2, sit);
    return 0;
}
