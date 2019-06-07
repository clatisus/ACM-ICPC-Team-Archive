#include <bits/stdc++.h>

const int N = 64;
typedef unsigned long long ull;

ull comb[N][N];

struct poly {
    ull a[N];

    poly() { memset(a, 0, sizeof(a)); }

    ull &operator[](const int &sit) { return a[sit]; }

    poly operator*(const poly &p) const {
        poly ret;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; i + j < N; ++j) {
                ret[i + j] += a[i] * p.a[j];
            }
        }
        return ret;
    }

    poly shift(const ull &amt) const {
        poly ret;
        for (int i = 0; i < N; ++i) {
            ull now = a[i];
            for (int j = i; j >= 0; --j) {
                ret[j] += comb[i][j] * now;
                now *= amt;
            }
        }
        return ret;
    }

    ull value(const ull &x) const {
        ull ret = 0;
        for (int i = N - 1; i >= 0; --i) {
            ret = ret * x + a[i];
        }
        return ret;
    }
};

poly p[N];
int digit[N];

ull calc(ull n) {
    ull ans = 1;
    if (n & 1) {
        ans = n;
        --n;
    }
    n = (n - 1) >> 1;
    ++n;
    int dcnt = 0;
    for (; n; n >>= 1) {
        digit[dcnt++] = n & 1;
    }
    std::reverse(digit, digit + dcnt);
    ull now = 0;
    for (int i = 0; i < dcnt; ++i) {
        if (digit[i]) {
            ans *= p[dcnt - i - 1].value(now);
        }
        now |= (ull) digit[i] << (dcnt - i - 1);
    }
    return ans;
}

ull solve(ull n) {
    ull ans = 1;
    while (n > 1) {
        ans *= calc(n);
        n = (n + 1) >> 1;
    }
    return ans;
}

int main() {
    for (int i = 0; i < N; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    p[0][0] = 1, p[0][1] = 2;
    for (int i = 1; i < N; ++i) {
        p[i] = p[i - 1] * p[i - 1].shift(1ull << (i - 1));
    }
    ull n;
    scanf("%llu", &n);
    printf("%llu\n", solve(n));
    return 0;
}
