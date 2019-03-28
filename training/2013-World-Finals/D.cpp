#include <bits/stdc++.h>

typedef unsigned long long ull;

const ull INF = 1ull << 63;
const int N = 200;

ull multi(ull a, ull b){
    return a <= INF / b ? a * b : INF;
}

ull power(ull a, ull exp){
    ull ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = multi(ret, a);
        }
        a = multi(a, a);
    }
    return ret;
}

std::vector <int> prime;
int min[N];
std::map <ull, ull> ans;
int cnt[N];
int fac[N][N];

void dfs(std::vector <int>::iterator it, ull value, int sum, int pre){
    ull mult = 1;
    for (auto u : prime){
        int time = fac[sum][u] - cnt[u];
        for (int i = 0; i < time; ++ i) {
            mult = multi(mult, u);
        }
    }
    if (mult < INF){
        if (ans.count(mult)){
            ans[mult] = std::min(ans[mult], value);
        }
        else{
            ans[mult] = value;
        }
    }
    for (int i = 1; i <= pre; ++ i){
        value = multi(value, *it);
        if (value == INF){
            break;
        }
        for (auto u : prime){
            cnt[u] += fac[i][u];
        }
        auto u = it;
        dfs(++ u, value, sum + i, i);
        for (auto u : prime){
            cnt[u] -= fac[i][u];
        }
    }
}

int main(){
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
        }
        for (auto u : prime){
            if (i * u >= N) break;
            min[i * u] = u;
            if (i % u == 0){
                break;
            }
        }
    }
    for (int i = 0; i < N; ++ i){
        for (auto u : prime){
            int x = i;
            while (x){
                fac[i][u] += x / u;
                x /= u;
            }
        }
    }
    dfs(prime.begin(), 1, 0, INT_MAX);
    ans[1] = 2;
    ull x;
    while (scanf("%llu", &x) != EOF) {
        printf("%llu %llu\n", x, ans[x]);
    }
    return 0;
}
