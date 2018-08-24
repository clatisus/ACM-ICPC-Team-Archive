#include<bits/stdc++.h>

const int N = 1000010;
const int M = 110;
const int INF = 0x7f7f7f7f;

int dp[N];
std::bitset <N> set[M];
int a[N], b[N];
int n;
int p, q;
char ans[N];

void solve(){
    memset(dp, 0x7f, sizeof(dp));
    for(int i = 0; i < M; ++ i){
        set[i].reset();
    }
    dp[0] = 0;
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < N; ++ j){
            dp[j] = dp[j];
        }
        for (int j = N - 1 - a[i]; j >= 0; -- j){
            if (dp[j] == INF) continue;
            if (dp[j + a[i]] > dp[j] + b[i]){
                dp[j + a[i]] = dp[j] + b[i];
                set[i + 1][j + a[i]] = 1;
            }
        }
    }
    for (int j = p; j < N; ++ j){
        if (dp[j] < q){
            for (int i = 0; i < n; ++ i){
                ans[i] = '0';
            }
            int x = n, y = j;
            while (x){
                if (set[x][y]){
                    ans[x - 1] = '1';
                    y -= a[x - 1];
                }
                -- x;
            }
            puts("NO");
            puts(ans);
            exit(0);
        }
    }
}

int main(){
    scanf("%d", &n);
    scanf("%d", &p);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    scanf("%d", &q);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &b[i]);
    }
    solve();
    std::swap(p, q);
    for (int i = 0; i < n; ++ i){
        std::swap(a[i], b[i]);
    }
    solve();
    puts("YES");
    return 0;
}
