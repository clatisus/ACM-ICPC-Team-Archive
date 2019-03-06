//
// Created by zzh on 2019/3/5.
//

#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
    int c;
    while (!isdigit(c = getchar()));
    x = c - '0';
    while (isdigit(c = getchar())) {
        x = x * 10 + c - '0';
    }
}

using LL = long long;

const int max_N = (int) 1e5 + 21;

int T, n, siz[max_N], max[max_N], f[max_N], tag1[max_N], tag2[max_N];

std::vector<int> vec[max_N];

std::unordered_map<int, LL> dp1[max_N], dp2[max_N];

LL ans;

void dfs(int u, int p) {
    siz[u] = 1;
    max[u] = 0;
    for (auto &v : vec[u]) {
        if (v == p) continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[max[u]]) {
            max[u] = v;
        }
    }
    int &v = f[u];
    if (siz[u] == 1) {
        v = u;
        tag1[v] = tag2[v] = 0;
        dp1[v][0] = 1;
        dp2[v][0] = 0;
    } else {
        v = f[max[u]];
        ++tag1[v], --tag2[v];
        ++dp1[v][0 - tag1[v]];
        ans += dp2[v][0 - tag2[v]];
        for (auto &w : vec[u]) {
            if (w == p || w == max[u]) continue;
            int wjj = f[w];
            for (int i = 0; i <= siz[w]; ++i) {
                ans += dp1[v][i - tag1[v]] * dp2[wjj][i + 1 - tag2[wjj]];
                if (i) {
                    ans += dp2[v][i - tag2[v]] * dp1[wjj][i - 1 - tag1[wjj]];
                    dp2[v][i - tag2[v]] += dp1[v][i - tag1[v]] * dp1[wjj][i - 1 - tag1[wjj]];
                    dp1[v][i - tag1[v]] += dp1[wjj][i - 1 - tag1[wjj]];
                }
                dp2[v][i - tag2[v]] += dp2[wjj][i + 1 - tag2[wjj]];
            }
        }
    }
}

void testCase() {
    read(n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    ans = 0;
    dfs(1, 0);
    printf("%lld\n", ans);
    for (int i = 1; i <= n; ++i) {
        std::vector<int>().swap(vec[i]);
        std::unordered_map<int, LL>().swap(dp1[i]);
        std::unordered_map<int, LL>().swap(dp2[i]);
    }
}

int main() {
    read(T);
    while (T--) {
        testCase();
    }
}
/*
 2
4
1 2
1 3
1 4
8
1 2
1 3
1 4
2 5
2 6
3 7
4 8
 */