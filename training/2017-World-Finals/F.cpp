#include<bits/stdc++.h>

const int N = 270;
typedef long long ll;
inline int sqr(int x){return x * x;}

ll dp[N][N];
ll cnt[N];
ll pre[N][N], suf[N][N];

void update(ll &a, ll b){
    if (a == -1 || a > b){
        a = b;
    }
}

ll calc(int l, int r){
    int mid = (l + r) >> 1;
    return suf[r - 1][mid + 1] + pre[l + 1][mid];
}

int main(){
    int d, k;
    scanf("%d%d", &d, &k);
    for (int i = 0; i < d; ++ i){
        int x, y;
        scanf("%d%d", &x, &y);
        cnt[x] += y;
    }
    for (int i = 0; i < N; ++ i){
        for (int j = i; j < N; ++ j){
            pre[i][j] = (j == i ? 0ll : pre[i][j - 1]) + 1ll * sqr(j - i + 1) * cnt[j];
        }
    }
    for (int i = 0; i < N; ++ i){
        for (int j = i; j >= 0; -- j){
            suf[i][j] = (j == i ? 0ll : suf[i][j + 1]) + 1ll * sqr(i - j + 1) * cnt[j];
        }
    }
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < N; ++ i){
        dp[1][i] = 0;
        for (int j = 0; j < i; ++ j){
            dp[1][i] += cnt[j] * sqr(i - j);
        }
    }
    for (int i = 2; i <= k; ++ i){
        for (int j = 0; j < N; ++ j){
            for (int u = 0; u < j; ++ u){
                if (dp[i - 1][u] == -1){
                    continue;
                }
                update(dp[i][j], dp[i - 1][u] + calc(u, j));
            }
        }
    }
    ll ans = LLONG_MAX;
    for (int i = 0; i < N; ++ i){
        if (dp[k][i] == -1){
            continue;
        }
        ll sum = dp[k][i];
        for (int j = i + 1; j < N; ++ j){
            sum += cnt[j] * sqr(j - i);
        }
        ans = std::min(ans, sum);
    }
    printf("%lld\n", ans);
    return 0;
}
