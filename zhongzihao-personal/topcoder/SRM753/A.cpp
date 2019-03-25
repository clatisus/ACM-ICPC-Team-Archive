#include <bits/stdc++.h>

const int N = 1000010;
const int M = N << 1;
typedef std::pair <int, bool> pib;

std::vector <pib> e[N];

int dfn[N], low[N], cnt;
bool vis[N];
int dp[N][2];

void dfs(int x, int p) {
    low[x] = dfn[x] = ++cnt;
    int ch = 0;
    for (auto &y : e[x]){
        int v = y.first;
        if (v == p)continue;
        if (!dfn[v]) {
            ++ch, dfs(v, x);
            low[x] = std::min(low[x], low[v]);
            if (dfn[x] < low[v]){
                y.second = true;
            }
        } else if (dfn[v] < dfn[x]) {
            low[x] = std::min(low[x], dfn[v]);
        }
    }
}

void calc(int u, int fa){
    vis[u] = true;
    int sum0 = 0, sum1 = 0;
    for (auto v : e[u]){
        if (!v.second){
            continue;
        }
        if (v.first == fa){
            continue;
        }
        calc(v.first, u);
        sum0 += dp[v.first][0];
        sum1 += std::max(dp[v.first][0], dp[v.first][1]);
    }
    dp[u][1] = sum0 + 1;
    dp[u][0] = sum1;
}

class MaxCutFree {
public:
    int solve(int n, std::vector <int> a, std::vector <int> b) {
        int m = a.size();
        for (int i = 0; i < m; ++ i) {
            e[a[i]].push_back({b[i], false});
            e[b[i]].push_back({a[i], false});
        }
        for (int i = 0; i < n; ++ i){
            if (!dfn[i]){
                dfs(i, -1);
            }
        }
        for (int i = 0; i < n; ++ i){
            for (auto u : e[i]){
                if (u.second){
                    for (auto &v : e[u.first]){
                        if (v.first == i) {
                            v.second = true;
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++ i){
            if (!vis[i]){
                calc(i, -1);
                ans += std::max(dp[i][0], dp[i][1]);
            }
        }
        return ans;
    }
};

int main(){
    MaxCutFree m;
    printf("%d\n", m.solve(4, {0, 0, 0, 1, 1, 2}, {1, 2, 3, 2, 3, 3}));
}
