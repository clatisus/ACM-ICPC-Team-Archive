#include <bits/stdc++.h>

#define ALL(x) (x).begin(), (x).end()

const int max_N = 11;
const int max_S = 59049;

using LL = long long;

int n, a, b, q, bit[1 << max_N];

unsigned short trans[max_S][1 << max_N];

LL dp[max_N][max_S];

std::vector<int> subset[1 << max_N];

inline int transS(int *p, int mask) {
    int S = 0;
    for (int i = n - 1; ~i; --i) {
        int tmp;
        if ((mask >> i) & 1) tmp = 1;
        else tmp = !p[i] ? 0 : 2;
        (S *= 3) += tmp;
    }
    return S;
}

inline int getMask(int s, int *p) {
    int mask = 0;
    for (int i = 0; i < n; ++i) {
        p[i] = s % 3, s /= 3;
        if (p[i] < 2) mask |= (1 << i);
    }
    return mask;
}

LL calc(int i, int s) {
    if (~dp[i][s]) return dp[i][s];
    LL &ret = dp[i][s];
    int p[max_N], mask = getMask(s, p);
    if (i == n) {
        for (int j = 0; j < n; ++j)
            if (!p[j]) return ret = 0;
        return ret = 1;
    }
    ret = 0;
    for (auto mask1 : subset[mask]) {
        int ss = trans[s][mask1];
        ret += calc(i + 1, ss);
    }
    return ret;
}

int ans[max_N];

char str[1 << max_N][15];

void kth(LL k) {
    int s = 0, p[max_N], mask;
    if (calc(0, 0) < k) {
        puts("No such matrix.");
        return;
    }
    for (int i = 1; i <= n; ++i) {
        LL sum = 0;
        mask = getMask(s, p);
        for (auto mask1 : subset[mask]) {
            int ss = trans[s][mask1];
            LL tmp = sum + calc(i, ss);
            if (k <= tmp) {
                s = ss;
                k -= sum;
                ans[i] = mask1;
                break;
            }
            sum = tmp;
        }
    }
    for (int i = 1; i <= n; ++i) puts(str[ans[i]]);
}

int main() {
    scanf("%d%d%d%d", &n, &a, &b, &q);
    for (int s = 1; s < (1 << n); ++s) {
        bit[s] = bit[s - (s & -s)] + 1;
        for (int ss = s; ss; (--ss) &= s)
            if (a <= bit[ss] && bit[ss] <= b) {
                subset[s].push_back(ss);
            }
        std::reverse(ALL(subset[s]));
        for (int j = 0; j < n; ++j) {
            str[s][n - j - 1] = ((s >> j) & 1) ? '1' : '0';
        }
        str[s][n] = '\0';
    }
    int S = 1, p[max_N], mask;
    for (int i = 0; i < n; ++i) S *= 3;
    for (int s = 0; s < S; ++s) {
        mask = getMask(s, p);
        for (auto mask1 : subset[mask]) {
            trans[s][mask1] = transS(p, mask1);
        }
    }
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= q; ++i) {
        LL k;
        scanf("%lld", &k);
        kth(k);
        if (i < q) puts("");
    }
    return 0;
}
/*
10 1 10 1
10000000000000000
*/
