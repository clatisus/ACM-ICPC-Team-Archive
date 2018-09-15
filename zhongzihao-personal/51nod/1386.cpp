#include<bits/stdc++.h>

const int SMALL = 31;
const int N = 1 << 11;
const int INF = 0x7f7f7f7f;

int min[N];
std::vector <int> prime;
int bit[N], big[N], id[N];
int dp[2][N];
std::vector <int> vec[N];

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
    int smallcnt = 0;
    for (auto u : prime){
        if (u > SMALL){
            break;
        }
        id[u] = smallcnt ++;
    }
    for (int i = 2; i < N; ++ i){
        int x = i;
        while (x > 1){
            int tmp = min[x];
            if (tmp > SMALL){
                big[i] = tmp;
            }
            else{
                bit[i] |= 1 << id[tmp];
            }
            while (x % tmp == 0){
                x /= tmp;
            }
        }
    }
}

int solve(){
    memset(dp, 0x7f, sizeof(dp));
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < N; ++ i){
        vec[i].clear();
    }
    for (int i = 1; i <= n; ++ i){
        if (i == k){
            continue;
        }
        if (big[i]){
            vec[big[i]].push_back(i);
        }
    }
    dp[0][0] = 0;
    int now = 0;
    for (int i = 0; i < N; ++ i){
        memset(dp[now ^ 1], 0x7f, sizeof(dp[now]));
        if (vec[i].empty()) continue;
        for (int j = N - 1; j >= 0; -- j){
            if (dp[now][j] == INF) continue;
            for (auto u : vec[i]){
                if (j & bit[u]) continue;
                int &v = dp[now ^ 1][j | bit[u]];
                v = std::min(v, dp[now][j] + 1);
            }
        }
        now ^= 1;
    }
    for (int i = 2; i <= n; ++ i){
        if (i == k || big[i]){
            continue;
        }
        for (int j = N - 1; j >= 0; -- j){
            if (dp[now][j] == INF || j & bit[i]) continue;
            int &u = dp[now][j | bit[i]];
            u = std::min(u, dp[now][j] + 1);
        }
    }
    int smallcnt = 0;
    for (auto u : prime){
        if (u > n || u > SMALL){
            break;
        }
        ++ smallcnt;
    }
    return dp[now][(1 << smallcnt) - 1] + (k != 1);
}

int main(){
    init();
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
