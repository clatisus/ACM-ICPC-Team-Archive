#include<bits/stdc++.h>

const int N = 710;
const int M = N << 1;

int mat[N][N];
std::bitset <N> dp[2];
int fa[M], sz[2][M];
bool vis[N];

int find(int u){
    return fa[u] == u ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v){
    u = find(u), v = find(v);
    if (u == v) return;
    fa[u] = v;
}

inline int sqr(int n){return n * (n - 1) / 2;}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < m; ++ i){
        scanf("%d%d", &u, &v);
        mat[u][v] = mat[v][u] = 1;
    }
    for (int i = 1; i < M; ++ i){
        fa[i] = i;
    }
    for (int i = 1; i <= n; ++ i){
        for (int j = i + 1; j <= n; ++ j){
            if (!mat[i][j]){
                if (find(i) == find(j)){
                    puts("-1");
                    return 0;
                }
                unite(i, j + n);
                unite(i + n, j);
            }
        }
    }
    for (int i = 1; i <= n; ++ i){
        ++ sz[0][find(i)];
    }
    for (int i = n + 1; i <= n << 1; ++ i){
        ++ sz[1][find(i)];
    }
    int now = 0;
    dp[now].set(0);
    for (int i = 1; i <= n << 1; ++ i){
        if (find(i) != i || vis[i]) continue;
        vis[i] = vis[find(i + n)] = true;
        dp[now ^ 1] = dp[now] << sz[0][i] | dp[now] << sz[1][i];
        now ^= 1;
    }
    int min = INT_MAX;
    for (int i = 1; i <= n; ++ i){
        if (!dp[now].test(i)) continue;
        min = std::min(min, sqr(i) + sqr(n - i));
    }
    printf("%d\n", min);
    return 0;
}
