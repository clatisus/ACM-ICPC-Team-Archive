/*
题目大意：有$n\le10^5$个家庭，第$i$个家庭有$a_i$个男孩和$b_i$个女孩，$\sum a_i = \sum b_i \le10^5$。
问有多少种婚配方式不会出现同一个家庭的男孩和女孩结婚，对998244353取模。
题解：构造一种用于容斥的生成函数来计算，$f(x) = \sum h_n\times\frac{(-1)^n}{n!}x^n$。
对于每个家庭构造$f(x)$的一个因式$g_i(x) = \sum_{k=0}^{min(a_i,b_i} \binom{a_i}{k}\binom{b_i}{k}\times k!x^k$.
合并两个因式的时候用ntt，代价为$O((a+b)\log{a+b})$，使用优先队列每次合并两个最小的因式，总的时间复杂度为$O(n\log^2{n}$.
*/ 
#include <bits/stdc++.h>

const int max_N = (1 << 19);

const int P = 998244353;
const int G = 3;

using VI = std::vector<int>;

#define VI_SIZE(x) (int)((x).size())
#define VI_CLEAR(x) (VI().swap(x))

int T, n, m, rev[max_N], w[2][max_N], fac[max_N], _fac[max_N], inv[max_N];

int qpow(int x, int k) {
    int res = 1;
    while (k) {
        if (k & 1) {
            res = 1ll * res * x % P;
        }
        x = 1ll * x * x % P;
        k >>= 1;
    }
    return res;
}

void init() {
    inv[1] = 1;
    for (int i = 2; i < max_N; ++i) {
        inv[i] = 1ll * (P / i) * inv[P % i] % P;
        if (inv[i]) inv[i] = P - inv[i];
    }
    fac[0] = _fac[0] = 1;
    for (int i = 1; i < max_N; ++i) {
        fac[i] = 1ll * fac[i - 1] * i % P;
        _fac[i] = 1ll * _fac[i - 1] * inv[i] % P;
    }
    int g = qpow(G, (P - 1) / max_N);
    w[0][0] = w[1][0] = 1;
    for (int i = 1; i < max_N; ++i) {
        w[0][i] = 1ll * w[0][i - 1] * g % P;
    }
    for (int i = 1; i < max_N; ++i) {
        w[1][i] = w[0][max_N - i];
    }
}

void getRev(int n, int bit) {
    for (int i = 1; i < n; ++i) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1) {
            rev[i] |= 1 << (bit - 1);
        }
    }
}

void ntt(VI &a, int t) {
    int n = VI_SIZE(a);
    for (int i = 0; i < n; ++i)
        if (i < rev[i]) {
            std::swap(a[i], a[rev[i]]);
        }
    for (int k = 2; k <= n; k <<= 1)
        for (int i = 0; i < n; i += k)
            for (int j = 0; j < (k >> 1); ++j) {
                int tmp = 1ll * a[i + j + (k >> 1)] * w[t][max_N / k * j] % P;
                a[i + j + (k >> 1)] = (a[i + j] - tmp + P) % P;
                a[i + j] = (a[i + j] + tmp) % P;
            }
    if (t) {
        for (int i = 0; i < n; ++i) {
            a[i] = 1ll * a[i] * inv[n] % P;
        }
    }
}

int roundBit(int n) {
    int i = 0;
    while ((1 << i) < n) ++i;
    return i;
}

VI merge(VI &a, VI &b) {
    int bit = roundBit(VI_SIZE(a) + VI_SIZE(b) - 1);
    int n = 1 << bit;
    getRev(n, bit);
    a.resize(n, 0), ntt(a, 0);
    b.resize(n, 0), ntt(b, 0);
    VI res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = 1ll * a[i] * b[i] % P;
    }
    ntt(res, 1);
    VI_CLEAR(a), VI_CLEAR(b);
    while(n && !res[n-1]) --n;
    res.resize(n);
    return res;
}

VI f[max_N];

struct functor {
    bool operator()(int a, int b) {
        return f[a].size() > f[b].size();
    }
};

std::priority_queue<int, VI, functor> pq;

void testCase() {
    scanf("%d", &n);
    m = 0;
    for (int id = 0; id < n; ++id) {
        int a, b, k;
        scanf("%d%d", &a, &b);
        m += a;
        k = std::min(a, b);
        f[id] = VI(k + 1);
        for (int i = 0; i <= k; ++i) {
            f[id][i] = 1ll * fac[a] * fac[b] % P;
            f[id][i] = 1ll * f[id][i] * _fac[i] % P;
            f[id][i] = 1ll * f[id][i] * _fac[a - i] % P;
            f[id][i] = 1ll * f[id][i] * _fac[b - i] % P;
        }
        pq.push(id);
    }
    for (int id = n; id < n + n - 1; ++id) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        f[id] = merge(f[a], f[b]);
        pq.push(id);
    }
    int x = pq.top();
    pq.pop();
    int ans = 0;
    for (int i = 0; i < VI_SIZE(f[x]); ++i) {
        int tmp = 1ll * f[x][i] * fac[m - i] % P;
        if (i & 1) {
            ans = (ans - tmp + P) % P;
        } else {
            ans = (ans + tmp) % P;
        }
    }
    printf("%d\n", ans);
    VI_CLEAR(f[x]);
}

int main() {
    init();
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
