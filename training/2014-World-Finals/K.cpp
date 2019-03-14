//
// Created by zzh on 2019/3/12.
//

#include <bits/stdc++.h>

const int max_N = (int) 2e6 + 21;
const int log_N = 22;

int n, k, cur, nxt[log_N][max_N], dep[max_N], ans = INT_MAX;

std::vector<std::pair<int, int>> seg;

int query(int x) {
    int y = x;
    for (int i = log_N - 1; ~i; --i) {
        if (nxt[i][x] && nxt[i][x] < y + n) {
            x = nxt[i][x];
        }
    }
    if (!nxt[0][x]) {
        return INT_MAX;
    }
    return dep[y] - dep[nxt[0][x]];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, a, b; i <= k; ++i) {
        scanf("%d%d", &a, &b);
        if (a <= b) {
            seg.emplace_back(a, b);
            seg.emplace_back(a + n, b + n);
        } else {
            seg.emplace_back(a, b + n);
        }
    }
    std::sort(seg.begin(), seg.end());
    auto sz = seg.size();
    for (int i = 1, j = 0; i <= n * 2; ++i) {
        while (j < sz && seg[j].first <= i) {
            cur = std::max(cur, seg[j++].second);
        }
        if (cur >= i) {
            nxt[0][i] = cur + 1;
        }
    }
    for (int i = 2 * n; i; --i) {
        dep[i] = dep[nxt[0][i]] + 1;
        for (int j = 1; j < log_N; ++j) {
            nxt[j][i] = nxt[j - 1][nxt[j - 1][i]];
        }
        ans = std::min(ans, query(i));
    }
    if (ans == INT_MAX) {
        puts("impossible");
    } else {
        printf("%d\n", ans);
    }
}