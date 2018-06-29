/*
题目大意：有一个n个节点的随机树，随机生成的方式为第i个点等概率选择一个编号小于i的节点作为父亲。
已知每个节点有个权值$a_i$，求在随机生成的树上随机选择一颗子树，子树中点的权值和的期望值是多少？
题解：按编号从大到小递推，记$f_i$为以$i$为根的子树权值和的期望值，则有$f_i=a_i+\sum_{j>i}\frac{f_j}{j-1}$. 
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
