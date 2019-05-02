#include <bits/stdc++.h>

const int MAXN = 510;

int n, c;
int d[MAXN], s[MAXN], id[MAXN];
int dp[MAXN][MAXN], pre[MAXN][MAXN];

bool update(int &a, int b) {
    if (a == -1 || a < b) {
        a = b;
        return true;
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", d + i, s + i);
        d[i] = std::max(d[i], s[i]);
        id[i] = i;
    }

    std::sort(id + 1, n + id + 1, [&](const int &i, const int &j) {
        return s[i] - d[i] < s[j] - d[j];
    });

    memset(dp, -1, sizeof(dp));
    dp[0][0] = c;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = c;
        for (int j = 1; j <= i; ++j) {
            if (dp[i - 1][j] != -1) {
                if (update(dp[i][j], dp[i - 1][j])) {
                    pre[i][j] = false;
                }
            }
            if (dp[i - 1][j - 1] != -1 && dp[i - 1][j - 1] >= d[id[i]]) {
                if (update(dp[i][j], dp[i - 1][j - 1] - s[id[i]])) {
                    pre[i][j] = true;
                }
            }
        }
    }
    int ans = 0;
    for (int i = n; ~i; --i) {
        if (dp[n][i] != -1) {
            ans = i;
            break;
        }
    }
    printf("%d\n", ans);
    std::vector<int> wjj;
    for (int i = n; i >= 1; --i) {
        if (pre[i][ans]) {
            wjj.push_back(id[i]);
            --ans;
        }
    }
    std::reverse(wjj.begin(), wjj.end());
    for (int i = 0; i < wjj.size(); ++i) {
        printf("%d%c", wjj[i], " \n"[i == wjj.size() - 1]);
    }
    return 0;
}