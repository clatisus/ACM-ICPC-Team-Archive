#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long
#define sqr(x) ((x) * (x))

int n, p;
std::vector<std::pair<int, int>> vec[MAXN];

ll dp[MAXN], d[MAXN];
int que[MAXN];

ll gety(int a, int b) {
    return (dp[a] + sqr(d[a])) - (dp[b] + sqr(d[b]));
}

ll getx(int a, int b) {
    return 2 * (d[a] - d[b]);
}

void dfs(int u, int fa, int head, int tail) {
    int l = head, r = tail - 2;
    while (l < r) {
        int m = (l + r) >> 1;
        if (gety(que[m + 1], que[m]) <= d[u] * getx(que[m + 1], que[m])) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    if (l + 1 < tail && gety(que[l + 1], que[l]) <= d[u] * getx(que[l + 1], que[l])) {
        ++l;
    }
    head = l;

    dp[u] = dp[que[head]] + sqr(d[u] - d[que[head]]) + p;

    l = head + 2, r = tail;
    while (l < r) {
        int m = (l + r) >> 1;
        if (gety(que[m - 1], que[m - 2]) * getx(u, que[m - 1]) >= gety(u, que[m - 1]) * getx(que[m - 1], que[m - 2])) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    if (l - 1 > head && gety(que[l - 1], que[l - 2]) * getx(u, que[l - 1]) >= gety(u, que[l - 1]) * getx(que[l - 1], que[l - 2])) {
        --l;
    }
    tail = l;

    int sit = tail, value = que[tail];
    que[tail++] = u;

    for (auto &p : vec[u]) {
        int v = p.first, w = p.second;
        if (v == fa) continue;
        d[v] = d[u] + w;
        dfs(v, u, head, tail);
    }
    
    que[sit] = value;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &p);
        for (int i = 1; i < n; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            vec[u].push_back({v, w});
            vec[v].push_back({u, w});
        }

        dp[1] = -p;
        d[1] = 0;
        que[0] = 1;
        for (auto &p : vec[1]) {
            int v = p.first, w = p.second;
            d[v] = d[1] + w;
            dfs(v, 1, 0, 1);
        }

        ll ans = 0;
        for (int i = 2; i <= n; ++i) {
            ans = std::max(ans, dp[i]);
        }
        printf("%lld\n", ans);

        for (int i = 1; i <= n; ++i) {
            std::vector<std::pair<int, int>>().swap(vec[i]);
        }
    }
    return 0;
}
