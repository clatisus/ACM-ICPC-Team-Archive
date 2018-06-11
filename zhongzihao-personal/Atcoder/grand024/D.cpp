#include<bits/stdc++.h>

const int N = 110;
typedef long long ll;
typedef std::pair <int, ll> pil;

std::vector <int> e[N];
int dep[N];

void dfs(int u, int dep, int fa){
    ::dep[dep] = std::max(::dep[dep], (int) e[u].size() - (fa ? 1 : 0));
    for (auto v : e[u]){
        if (v == fa) continue;
        dfs(v, dep + 1, u);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    if (n == 2){
        puts("1 2");
        return 0;
    }
    for (int i = 0, u, v; i < n - 1; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    pil ans = {INT_MAX, 0};
    for (int i = 1; i <= n; ++ i){
        int max = 0;
        ll prod = 1;
        memset(dep, 0, sizeof(dep));
        dfs(i, 0, 0);
        for (int j = 0; j < N; ++ j){
            if (dep[j]){
                max = j;
                prod *= dep[j];
            }
        }
        ans = std::min(ans, {max + 2, prod});
    }
    for (int i = 1; i <= n; ++ i){
        for (auto u : e[i]){
            memset(dep, 0, sizeof(dep));
            if (i < u) continue;
            int max = 0;
            ll prod = 1;
            dfs(i, 0, u);
            dfs(u, 0, i);
            for (int j = 0; j < N; ++ j){
                if (dep[j]){
                    max = j;
                    prod *= dep[j];
                }
            }
            ans = std::min(ans, {max + 2, prod * 2});
        }
    }
    printf("%d %lld\n", ans.first, ans.second);
    return 0;
}
