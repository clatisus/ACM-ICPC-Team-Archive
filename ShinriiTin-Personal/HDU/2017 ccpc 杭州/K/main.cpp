/*
题目大意：给出长度为$n\le10^5$的数列a和b，定义函数$f(t)=\sum\lfloor\frac{t-b_i}{a_i}\rfloor$。
接下来$m\le10000$次操作，每次或者修改数列a或数列b的一个位置，或者询问最小的$t$使得$f(t)\ge k$.
任意时刻满足$1\le a_i\le1000,1\le b_i,k\le10^9$，且询问操作不超过$1000$次。 
题解：
首先需要二分答案，然后对于$\lfloor\frac{t-b}{a}\rfloor$：
令$t=t_1\times a + t_2$, $b=b_1\times a + b_2$，$0\le t_2, b_2 < a$，
则有$\lfloor\frac{t-b}{a}\rfloor = t_1 - b_1 + \lfloor\frac{t_2-b_2}{a}\rfloor$.
则对于每一种不同的$a_i$，维护一下$\sum b_1$和不同的$b_2$的后缀和。
计算$f(t)$的时间缩短为$O(A)$，$A$为$a$的值域大小。
修改的时候暴力修改，总的时间复杂度为$O((n+m)A+q\log{ans}A)，$q$为询问操作的次数。 
*/ 
#include <bits/stdc++.h>

using ll = long long;

const int max_N = (int) 1e5 + 21;
const int max_M = 1000 + 21;

int T, n, m, a[max_N], b[max_N];

ll sum[max_M];

int cnt[max_M][max_M];

void modify(int a, int b, int delta) {
    auto x = int(std::floor(1. * b / a));
    int y = b - x * a;
    sum[a] += x * delta;
    while (~y) cnt[a][y--] += delta;
}

bool check(ll t, int k) {
    ll res = 0;
    for(int a=1;a<=1000;++a){
        res += sum[a];
        res += (t/a)*cnt[a][0];
        res += cnt[a][a-(t%a)];
    }
    return res >= k;
}

void testCase() {
    for (int i = 1; i <= 1000; ++i) {
        sum[i] = 0;
        for (int j = 0; j < i; ++j) {
            cnt[i][j] = 0;
        }
    }
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) scanf("%d", b + i);
    for (int i = 1; i <= n; ++i) modify(a[i], -b[i], 1);
    while (m--) {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        if (opt != 3) {
            scanf("%d", &y);
            modify(a[x], -b[x], -1);
            if (opt == 1) a[x] = y;
            else b[x] = y;
            modify(a[x], -b[x], 1);
        } else {
            ll lo = 1, hi = ll(2e12);
            while (lo < hi) {
                ll mid = (lo + hi) >> 1;
                if (check(mid, x)) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            printf("%lld\n", lo);
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
