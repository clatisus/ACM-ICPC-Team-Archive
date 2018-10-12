#include<bits/stdc++.h>

const int N = 1000010;

std::vector <int> e[N];
int max[N], dis[N], dp[N];
int n, k;

void dfs(int u, int fa){
    int fmax = -1, smax = -1;
    for (auto v : e[u]){
        if (v == fa) continue;
        dfs(v, u);
        max[u] = std::max(max[u], max[v] + 1);
        dis[u] = std::max(dis[u], dis[v]);
        if (fmax <= max[v]){
            smax = fmax;
            fmax = max[v];
        }
        else if (smax < max[v]){
            smax = max[v];
        }
    }
    if (smax != -1){
        dis[u] = std::max(dis[u], fmax + smax + 2);
    }
}

void solve(int u, int fa){
    bool leaf = true;
    for (auto v : e[u]){
        if (v == fa) continue;
        leaf = false;
        solve(v, u);
        dp[u] += dp[v];
    }
    if (leaf){
        dp[u] = 1;
        return;
    }
    for (auto v : e[u]){
        if (v == fa) continue;
        if (dis[v] > k){
            return;
        }
    }
    int cnt = 0, maxmin = 0, minmax = INT_MAX;
    for (auto v : e[u]){
        if (v == fa) continue;
        if (max[v] + 1 <= k >> 1){
            maxmin = std::max(maxmin, max[v] + 1);
        }
        else{
            ++ cnt;
            minmax = std::min(minmax, max[v] + 1);
        }
    }
    if (minmax != INT_MAX && (maxmin + minmax <= k || !maxmin)){
        -- cnt;
    }
    dp[u] = std::min(dp[u], cnt + 1);
}

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0, u, v; i < n - 1; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; ++ i){
        if (e[i].size() >= 2){
            dfs(i, 0);
            solve(i, 0);
            printf("%d\n", dp[i]);
            return 0;
        }
    }
    return 0;
}
