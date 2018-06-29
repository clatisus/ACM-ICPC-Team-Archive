/*
题目大意：给出n的质因子分解，求$\sum_{d|n}\phi(d)\times\frac{n}{d}$.
题解：等价于求$f(n)=\sum_{i=1}^{n}gcd(i,n)$，这玩意儿是积性函数，$f(p^r)=[(p-1)r+p]p^{r-1}$.
*/
#include <bits/stdc++.h>

const int mod = 998244353;

int qpow(int x, int k) {
    int res = 1;
    for (; k; x = 1ll * x * x % mod, k >>= 1)
        if (k & 1)res = 1ll * res * x % mod;
    return res;
}

int f(int p, int r) {
    int res = (1ll * r * (p - 1) + p) % mod;
    return 1ll * res * qpow(p, r - 1) % mod;
}

int T, m, p, r, ans;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &m);
        ans = 1;
        while (m--) {
            scanf("%d%d", &p, &r);
            ans = 1ll * ans * f(p, r) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}
