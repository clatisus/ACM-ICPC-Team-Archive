#include<bits/stdc++.h>

const int N = 100010;
const int moder = 1e9 + 7;

std::vector <int> e[N];
bool vis[N];

int dfs(int u){
    if (vis[u]){
        return 0;
    }
    vis[u] = true;
    int sz = 1;
    for (auto v : e[u]){
        sz += dfs(v);
    }
    return sz;
}

int powermod(int a, int exp){
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
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int ans = 1, cnt = 0, cnt2 = 0;
    for (int i = 1; i <= n; ++ i){
        if (!vis[i]){
            int sz = dfs(i);
            if (sz >= 2){
                ++ cnt2;
            }
            ++ cnt;
        }
    }
    if (cnt2 >= 1){
        printf("%d\n", (powermod(2, cnt) + 1) % moder);
        return 0;
    }
    printf("%d\n", powermod(2, cnt));
    return 0;
}
