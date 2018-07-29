#include <bits/stdc++.h>

const int max_N = 300 + 21;
const int max_L = 16;

using ll = long long;
using pair = std::pair<int, int>;
using vector = std::vector<pair>;

const ll inf = 1ll << 40;

int n, m, l, s, t, j[max_N], e[max_N], cnt[1 << max_L];

ll dis[max_N][max_N], dp[17][1 << max_L];

vector vec[max_N];

int main() {
    scanf("%d%d%d%d%d", &n, &m, &l, &s, &t);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            dis[i][j] = dis[j][i] = inf;
        }
    }
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        dis[a][b] = dis[b][a] = c;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                ll tmp = dis[i][k] + dis[k][j];
                dis[i][j] = std::min(tmp, dis[i][j]);
            }
        }
    }
    j[0] = s, e[0] = 0;
    for (int i = 1; i <= l; ++i) {
        scanf("%d%d", j + i, e + i);
    }
    int max_s = 1 << l;
    for (int i = 0; i <= l; ++i)
        for (int set = 0; set < max_s; ++set) {
            dp[i][set] = inf;
        }
    dp[0][0] = 0;
    for (int i = 1; i < max_s; ++ i) {
        cnt[i] = cnt[i - (i & -i)] + 1;
    }
    for (int set = 0; set < max_s; ++set) {
        for (int x = 0; x <= l; ++x) {
            if (dp[x][set] == inf) continue;
            for (int y = 0; y <= l; ++y) {
                int nset = set;
                if (y) nset |= 1 << (y - 1);
                ll tmp = dp[x][set] + dis[j[x]][j[y]] + e[y];
                dp[y][nset] = std::min(tmp, dp[y][nset]);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < max_s; ++i) {
        if (dp[0][i] <= t) {
            ans = std::max(ans, cnt[i]);
        }
    }
    printf("%d\n", ans);
    return 0;
}

