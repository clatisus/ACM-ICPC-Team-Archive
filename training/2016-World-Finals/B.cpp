//
// Created by zzh on 2019/3/20.
//

#include <bits/stdc++.h>

const int max_N = (int) 5e3 + 21;

const int dis_inf = 0x3f3f3f3f;

using LL = long long;

const LL dp_inf = 0x3f3f3f3f3f3f3f3fLL;

int n, b, s, r, dis[2][max_N], vis[max_N], cur;

std::vector<std::pair<int, int>> vec[2][max_N];

void DJ(int tp, int u) {
    std::priority_queue<std::pair<int, int>> pq;
    int *Dis = dis[tp];
    for (int i = 1; i <= n; ++i) {
        Dis[i] = dis_inf;
        vis[i] = 0;
    }
    pq.emplace(Dis[u] = 0, u);
    while (!pq.empty()) {
        u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &pr : vec[tp][u]) {
            int v = pr.first;
            int tmp = Dis[u] + pr.second;
            if (Dis[v] > tmp) {
                Dis[v] = tmp;
                pq.emplace(-Dis[v], v);
            }
        }
    }
}

LL a[max_N], dp[2][max_N];

inline LL cost(int l, int r) {
    return (a[r] - a[l]) * (r - l - 1);
}

inline LL calc(int i, int j) {
    return dp[cur ^ 1][j] + cost(j, i);
}

void solve(int l, int r, int ql, int qr) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    int qt = std::min(qr, mid - 1);
    for (int i = qt; i >= ql; --i) {
        if (calc(mid, i) < calc(mid, qt)) {
            qt = i;
        }
    }
    dp[cur][mid] = calc(mid, qt);
    solve(l, mid - 1, ql, qt);
    solve(mid + 1, r, qt, qr);
}

int main() {
    scanf("%d%d%d%d", &n, &b, &s, &r);
    for (int i = 1, u, v, w; i <= r; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        vec[0][u].emplace_back(v, w);
        vec[1][v].emplace_back(u, w);
    }
    DJ(0, b + 1);
    DJ(1, b + 1);
    for (int i = 1; i <= b; ++i) {
        a[i] = dis[0][i] + dis[1][i];
    }
    std::sort(a + 1, a + 1 + b);
    for (int i = 1; i <= b; ++i) {
        //printf("%lld ", a[i]);
        a[i] += a[i - 1];
    }
    //puts("");
    for (int i = 1; i <= b; ++i) {
        dp[cur][i] = cost(0, i);
    }
    for (int i = 2; i <= s; ++i) {
        cur ^= 1;
        for (int j = i; j <= b; ++j) {
            dp[cur][j] = dp_inf;
        }
        solve(i, b, i - 1, b - 1);
    }
    printf("%lld\n", dp[cur][b]);
}
/*
5 4 2 10
5 2 1
2 5 1
3 5 5
4 5 0
1 5 1
2 3 1
3 2 5
2 4 5
2 1 1
3 4 2

5 4 2 10
5 2 1
2 5 1
3 5 5
4 5 10
1 5 1
2 3 1
3 2 5
2 4 5
2 1 1
3 4 2
 */