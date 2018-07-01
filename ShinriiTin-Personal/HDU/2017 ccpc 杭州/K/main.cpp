/*
��Ŀ���⣺��������Ϊ$n\le10^5$������a��b�����庯��$f(t)=\sum\lfloor\frac{t-b_i}{a_i}\rfloor$��
������$m\le10000$�β�����ÿ�λ����޸�����a������b��һ��λ�ã�����ѯ����С��$t$ʹ��$f(t)\ge k$.
����ʱ������$1\le a_i\le1000,1\le b_i,k\le10^9$����ѯ�ʲ���������$1000$�Ρ� 
��⣺
������Ҫ���ִ𰸣�Ȼ�����$\lfloor\frac{t-b}{a}\rfloor$��
��$t=t_1\times a + t_2$, $b=b_1\times a + b_2$��$0\le t_2, b_2 < a$��
����$\lfloor\frac{t-b}{a}\rfloor = t_1 - b_1 + \lfloor\frac{t_2-b_2}{a}\rfloor$.
�����ÿһ�ֲ�ͬ��$a_i$��ά��һ��$\sum b_1$�Ͳ�ͬ��$b_2$�ĺ�׺�͡�
����$f(t)$��ʱ������Ϊ$O(A)$��$A$Ϊ$a$��ֵ���С��
�޸ĵ�ʱ�����޸ģ��ܵ�ʱ�临�Ӷ�Ϊ$O((n+m)A+q\log{ans}A)��$q$Ϊѯ�ʲ����Ĵ����� 
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
