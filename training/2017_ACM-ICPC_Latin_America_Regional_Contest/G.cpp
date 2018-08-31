#include<bits/stdc++.h>

const int N = 400010;
const int moder = 1e9 + 7;

int dp[N][4];
std::vector <int> e[N];
int f[N];
int n;

void dfs(int u){
    if (e[u].empty()){
        dp[u][0] = dp[u][3] = 1;
        return;
    }
    for (auto v : e[u]){
        dfs(v);
    }
    for (int i = 0; i < 4; ++ i){
        int xstuck = i & 1, xnormal = i >> 1;
        for (int j = 0; j < 4; ++ j){
            int ystuck = j & 1, ynormal = j >> 1;
            int retstuck, retnormal;
            if (f[u] == 0){
                retstuck = 0;
            }
            else if (f[u] == 1){
                retstuck = 1;
            }
            else{
                retstuck = !(xstuck & ystuck);
            }
            retnormal = !(xnormal & ynormal);
            int &v = dp[u][retnormal << 1 | retstuck];
            v = (v + 1ll * dp[e[u][0]][i] * dp[e[u][1]][j]) % moder;
        }
    }
}

void solve(){
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < N; ++ i){
        e[i].clear();
    }
    int leaf = n + 1;
    for(int i = 1; i <= n; ++ i){
        int x, y;
        scanf("%d%d%d", &x, &y, &f[i]);
        if (!x){
            x = leaf ++;
        }
        if (!y){
            y = leaf ++;
        }
        e[i].push_back(x);
        e[i].push_back(y);
    }
    dfs(1);
    int ans = (dp[1][1] + dp[1][2]) % moder;
    printf("%d\n", ans);
}

int main(){
    while (scanf("%d", &n) != EOF){
        solve();
    }
    return 0;
}

