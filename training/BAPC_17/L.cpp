#include <bits/stdc++.h>

#define MAXN (100010)

int n;
std::unordered_map<std::string, int> map;
const double lmt = log(10.0);
char sa[20], sb[20];
double dp[MAXN];
bool vis[MAXN];

int getid(std::string s) {
    static int tot = 0;
    if (map.count(s)) return map[s];
    return map[s] = ++ tot;
}

int main() {
    scanf("%d", &n);
    int x = getid("pink");
    int blue = getid("blue");
    vis[x] = true;
    for (int i = 1; i <= n; ++i) {
        double R;
        scanf("%s%s%lf", sa, sb, &R);
        std::string a(sa);
        std::string b(sb);
        int aa = getid(a), bb = getid(b);
        if (!vis[bb]) continue;
        if (!vis[aa]) {
            vis[aa] = true;
            dp[aa] = dp[bb] + log(R);
        } else {
            dp[aa] = std::max(dp[aa], dp[bb] + log(R));
        }
        if (aa == blue && dp[aa] > lmt) dp[aa] = lmt;
    }
    x = getid("blue");
    double ans = 0;
    if (vis[x]) {
        ans = exp(dp[x]);
    }
    printf("%.15f\n", ans);
    return 0;
}

