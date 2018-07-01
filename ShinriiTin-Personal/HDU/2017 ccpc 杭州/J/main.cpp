/*
��Ŀ���⣺��һ������Ϊ$n\le10^5$�����У���ʼʱ����1��������$m\le10^5$�β�����ÿ�θ�һ�������������2����3������������������Լ����
��⣺��¼һ��ÿ��λ��2��3�ĸ������ֱ�ȡmin���ɡ� 
*/
#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;
const int mod = 998244353;

int T, n, m, cnt[2][max_N];

void testCase() {
    scanf("%d%d", &n, &m);
    memset(cnt[0], 0, sizeof(int) * (n + 1));
    memset(cnt[1], 0, sizeof(int) * (n + 1));
    while (m--) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        ++cnt[x - 2][l];
        --cnt[x - 2][r + 1];
    }
    int tmp1 = INT_MAX, tmp2 = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        cnt[0][i] += cnt[0][i - 1];
        cnt[1][i] += cnt[1][i - 1];
        tmp1 = std::min(tmp1, cnt[0][i]);
        tmp2 = std::min(tmp2, cnt[1][i]);
    }
    int ans = 1;
    while (tmp1--) ans = (ans << 1) % mod;
    while (tmp2--) ans = int((3ll * ans) % mod);
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
