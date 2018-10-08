#include<bits/stdc++.h>

const int N = 30010;
const int moder = (int) 1e9 + 7;
typedef std::pair <int, int> pii;
typedef std::pair <int, pii> piii;

int dp[N], fa[N], sz[N];
piii p[N];
int inv[N];
int n, m;

void init(){
    inv[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = moder - 1ll * (moder / i) * inv[moder % i] % moder;
    }
}

int find(int u){
    return u == fa[u] ? u : (fa[u] = find(fa[u]));
}

void divide(int x){
    for (int i = 0; i + x <= n; ++ i){
        dp[i + x] -= dp[i];
        dp[i + x] += dp[i + x] < 0 ? moder: 0;
    }
}

void mult(int x){
    for (int i = n - x; i >= 0; -- i){
        dp[i + x] += dp[i];
        dp[i + x] -= dp[i + x] >= moder ? moder : 0;
    }
}

void unite(int u, int v){
    u = find(u), v = find(v);
    if (u == v) return;
    divide(sz[u]), divide(sz[v]);
    fa[u] = v;
    sz[v] += sz[u];
    mult(sz[v]);
}

int main(){
    init();
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v, w; i < m; ++ i){
        scanf("%d%d%d", &u, &v, &w);
        p[i] = {w, {u, v}};
    }
    std::sort(p, p + m, std::greater <piii>());
    for (int i = 0; i < n; ++ i){
        fa[i] = i;
        sz[i] = 1;
    }
    double ans = 1.0 * p[0].first / (n >> 1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++ i){
        dp[i] = 1ll * dp[i - 1] * (n - i + 1) % moder * inv[i] % moder;
    }
    int noww = p[0].first;
    for (int i = 0; ; ){
        while (i < m && p[i].first == noww){
            unite(p[i].second.first, p[i].second.second);
            ++ i;
        }
        int max = 0;
        for (int j = 0; j <= n; ++ j){
            if (dp[j]){
                max = std::max(max, std::min(j, n - j));
            }
        }
        if (i == m) break;
        if (!max) break;
        noww = p[i].first;
        ans = std::min(ans, 1.0 * noww / max);
    }
    printf("%.10f\n", ans);
}
