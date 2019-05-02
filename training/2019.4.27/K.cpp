//
// Created by zzh on 2019/4/27.
//

#include <bits/stdc++.h>

using db = long double;

const int max_N = 5000;

int n, k, a[max_N], tot;

std::vector<int> vec[max_N << 1];

std::unordered_map<int, db> dp[max_N << 1];

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r

#define ALL(x) (x).begin(), (x).end()

#define win(p, q) (1. * a[p] / (a[p] + a[q]))

void build(int x, int l, int r) {
    if (l == r) {
        vec[x].push_back(++tot);
        if (l > k) {
            vec[x].push_back(++tot);
            int p = tot - 1, q = tot;
            dp[x][p] = win(p, q);
            dp[x][q] = win(q, p);
        } else {
            dp[x][tot] = 1.;
        }
    } else {
        build(lch), build(rch);
        vec[x].resize(vec[ls(x)].size() + vec[rs(x)].size());
        std::merge(ALL(vec[ls(x)]), ALL(vec[rs(x)]), vec[x].begin());
        for (auto &p : vec[ls(x)]) {
            for (auto &q : vec[rs(x)]) {
                db tmp = dp[ls(x)][p] * dp[rs(x)][q];
                dp[x][p] += tmp * win(p, q);
                dp[x][q] += tmp * win(q, p);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    std::sort(a + 2, a + 1 + n);
    int m = 1;
    while ((m << 1) <= n) {
        m <<= 1;
    }
    k = 2 * m - n;
    build(1, 1, m);
    printf("%.10f\n", (double) dp[1][1]);
}