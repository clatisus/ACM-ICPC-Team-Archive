/*
��Ŀ���⣺��һ��n���ڵ���������������ɵķ�ʽΪ��i����ȸ���ѡ��һ�����С��i�Ľڵ���Ϊ���ס�
��֪ÿ���ڵ��и�Ȩֵ$a_i$������������ɵ��������ѡ��һ�������������е��Ȩֵ�͵�����ֵ�Ƕ��٣�
��⣺����ŴӴ�С���ƣ���$f_i$Ϊ��$i$Ϊ��������Ȩֵ�͵�����ֵ������$f_i=a_i+\sum_{j>i}\frac{f_j}{j-1}$. 
*/
#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int mod = 998244353;

int T, n, a[max_N], inv[max_N];

void init() {
    inv[1] = 1;
    for (int i = 2; i < max_N; ++i) {
        inv[i] = 1ll * (mod / i) * inv[mod % i] % mod;
        if (inv[i]) inv[i] = mod - inv[i];
    }
}

void testCase() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    int tmp = 0, ans = 0;
    for (int i = n; i; --i) {
        int tmep = (tmp + a[i]) % mod;
        ans = (ans + tmep) % mod;
        tmp = (1ll * tmep * inv[i - 1] + tmp) % mod;
    }
    ans = 1ll * ans * inv[n] % mod;
    printf("%d\n", ans);
}

int main() {
    init();
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
