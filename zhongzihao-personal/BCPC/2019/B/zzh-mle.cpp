#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

typedef long long ll;
const int N = 5010;
const ll INF = 2e18;

ll dp[N][N], cnt[N];
ll power[N];
int s[N], c[N];
int ans[N];

ll add(ll a, ll b){
    return std::min(INF, a + b);
}

ll mult(ll a, ll b){
    if (!a || !b) return 0;
    return INF / a >= b ? a * b : INF;
}

void solve(){
    int n, sigma;
    ll k;
    scanf("%d%d%lld", &n, &sigma, &k);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &s[i]);
        c[i - 1] = s[i];
    }
    std::sort(c, c + n);
    int ccnt = std::unique(c, c + n) - c;
    for (int i = 1; i <= n; ++ i){
        s[i] = std::lower_bound(c, c + ccnt, s[i]) - c + 1;
    }
    for (int i = 0; i <= n; ++ i){
        dp[0][i] = 1;
    }
    for (int i = 0; i < n; ++ i){
        memset(cnt, 0, sizeof(cnt));
        for (int j = 1; j <= n; ++ j){
            cnt[s[j]] = add(cnt[s[j]], mult(power[n - j], dp[i][j - 1]));
        }
        cnt[0] = dp[i][n];
        if (!i) -- cnt[0];
        for (int j = 0; ; ++ j){
            if (k <= cnt[j]){
                ans[i] = j;
                break;
            }
            k -= cnt[j];
        }
        if (!ans[i]) break;
        for (int j = 1; j <= n; ++ j){
            dp[i + 1][j] = add(dp[i + 1][j - 1],  s[j] == ans[i] ? dp[i][j - 1] : 0);
        }
    }
    ans[n] = 0;
    std::vector <int> output;
    for (int i = 0; ; ++ i){
        if (!ans[i]) break;
        output.push_back(ans[i]);
    }
    for (int i = 0, sz = output.size(); i < sz; ++ i){
        printf("%d%c", c[output[i] - 1], " \n"[i == sz - 1]);
    }
}

int main() {
    power[0] = 1;
    for (int i = 1; i < N; ++ i){
        power[i] = add(power[i - 1], power[i - 1]);
    }
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
