/*
��Ŀ���⣺����һ��$n\le3000$���ڵ��������$i$���ڵ���һ��Ȩֵ$a_i$������$i\in[1,m]$��$m\le10^5$�����Ƿ����һ��Ȩֵ��Ϊ$i$����ͨ�顣
��⣺���ȵ���������ѡ���ĵ���ͨ�飬��bitset����ܵ�Ȩֵ�ͣ�ע��һ����������ѡ����Ļ�����ѡ��ǰ����㣬������ܲ�����ͨ�顣
ʱ�临�Ӷ�$O(n\log{n}m/32)$���ռ临�Ӷ�$O(nm/32)$. 
*/
#include <bits/stdc++.h>

const int max_N = 3000 + 21;
const int max_M = (int) 1e5 + 21;

int T, n, m, a[max_N];

std::vector<int> vec[max_N];

bool vis[max_N];

int siz[max_N], max[max_N], rt;

using BS = std::bitset<max_M>;

BS zero, ans;

char ansS[max_M];

void findRoot(int x, int p, int sum) {
    siz[x] = 1, max[x] = 0;
    for (auto &y:vec[x])
        if (!vis[y] && y != p) {
            findRoot(y, x, sum);
            siz[x] += siz[y];
            max[x] = std::max(max[x], siz[y]);
        }
    max[x] = std::max(max[x], sum - siz[x]);
    if (max[rt] > max[x]) rt = x;
}

int getSize(int x, int p) {
    int res = 1;
    for (auto &y:vec[x])
        if (!vis[y] && y != p) {
            res += getSize(y, x);
        }
    return res;
}

BS calc(const BS &u, int x, int p) {
    BS res = u;
    res <<= a[x];
    for (auto &y:vec[x])
        if (!vis[y] && y != p) {
            res |= calc(res, y, x);
        }
    res |= u;
    return res;
}

void solve(int x) {
    vis[x] = true;
    ans |= calc(zero, x, 0);
    for (auto &y:vec[x])
        if (!vis[y]) {
            rt = 0;
            findRoot(y, x, getSize(y, x));
            solve(rt);
        }
}

void testCase() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        std::vector<int>().swap(vec[i]);
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    max[rt = 0] = n + 1;
    findRoot(1, 0, n);
    ans.reset();
    solve(rt);
    for (size_t i = 1; i <= m; ++i) {
        ansS[i - 1] = ans.test(i) ? '1' : '0';
    }
    ansS[m] = '\0';
    puts(ansS);
}

int main() {
    zero.set(0);
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
