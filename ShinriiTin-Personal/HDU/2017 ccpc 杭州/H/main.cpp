/*
��Ŀ���⣺�������ýڵ�����Ϊ$n\le10000$����������Ϊ1�Žڵ㡣
����$m\le10000$���������ͼG��ÿ���߶����������е�����һ���ڵ�һһ��Ӧ��
����$i\in[1,n]$�������ֻ�õ�һ������$i$�����ڵ����ϵĽڵ��Ӧ�����бߣ�
���ϵڶ�������$i$�����ڵ����ϵĽڵ��Ӧ�����бߣ���ͼG����ͨ���������
��⣺��������ʹ��Ī���㷨��
����Ҫʹ�ò��鼯������ά����ͨ������������֤�����Ĳ���λ��ʱ���ߵ����
���������ֿ飬��¼ÿ���lca��Ȼ��ѯ�ʰ����������ڿ��lca��dfn����
����ÿ�λش�ѯ�ʵ�ʱ�򣬶��ȴ������lca���������ӵ���ǰѯ�ʵķ�Χ���ش���ٻ��˵�lca��
��Ϊÿ��Ĵ�С��$O(\sqrt{n})$����ģ���˿���ת����$O(n\sqrt{n})$�β��鼯������
- ����һ�ε�ѯ����ǰһ��ѯ���ڵ�һ�����п���ͬ�����ڶ������п鲻ͬ��ʱ���������������lca��lca������ӵ��¿��lca
- ����һ�ε�ѯ����ǰһ��ѯ���ڵ�һ�����п鲻ͬ��ʱ���Ƚ��ڶ������еĲ������˵�������������ķ����ƶ���һ���lca��
��Ϊ��һ�����п鷢���仯�Ĵ���Ϊ$O(\sqrt{n})$���ڶ������ʱ�临�ӶȲ�����$O(n\sqrt{n})$�β��鼯������
����һ���������ʱ�临�Ӷ���Ī���㷨��֪��$O(n\sqrt{n})$���ϲ��鼯���β������Ӷȡ�
��Ϊ���鼯Ҫ�������������ʹ�ð��Ⱥϲ��ķ������ܵ�ʱ�临�Ӷ�ΪO(n\sqrt{n}\log{n})$.
*/ 
#include <bits/stdc++.h>

using VI = std::vector<int>;
#define VI_CLEAR(x) (VI().swap(x))

using PII = std::pair<int, int>;

const int max_N = 20000 + 21;

int T, n, m, f[max_N], siz[max_N], block;

int find(int x) {
    int r = x;
    while (r != f[r]) r = f[r];
    return r;
}

#define rootA (1)
#define rootB (n+1)

VI vec[max_N];

PII edge[max_N], opt[max_N];

void initTree(int rt) {
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &edge[i + rt].first, &edge[i + rt].second);
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        u += rt - 1, v += rt - 1;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
}

int p[max_N], dep[max_N], dfn[max_N], cnt, st[max_N], top;

int q[max_N], ans[max_N], globalAns;

int blockHead[max_N], blockSize[max_N];

void dfs1(int x) {
    st[++top] = x;
    dfn[x] = ++cnt;
    for (auto &y:vec[x])
        if (y != p[x]) {
            p[y] = x;
            dep[y] = dep[x] + 1;
            dfs1(y);
            blockSize[x] += blockSize[y];
            if (blockSize[x] >= block) {
                while (st[top] != x) {
                    blockHead[st[top--]] = x;
                }
                blockSize[x] = 0;
            }
        }
    ++blockSize[x];
}

void dfs2(int x, int c) {
    if (blockHead[x]) {
        c = blockHead[x];
    } else {
        blockHead[x] = c;
    }
    for (auto &y:vec[x])
        if (y != p[x]) {
            dfs2(y, c);
        }
}

void getBlocks(int rt) {
    top = 0;
    p[rt] = dep[rt] = 0;
    dfs1(rt);
    dfs2(rt, rt);
}

struct functor {
    bool operator()(int x, int y) {
        if (blockHead[x] != blockHead[y]) {
            return dfn[blockHead[x]] < dfn[blockHead[y]];
        }
        return dfn[blockHead[x + n]] < dfn[blockHead[y + n]];
    }
};

PII merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return {0, 0};
    if (siz[x] > siz[y]) std::swap(x, y);
    --globalAns;
    f[x] = y, siz[y] += siz[x];
    return {x, y};
}

void split(int x, int y) {
    if (!x)return;
    ++globalAns;
    f[x] = x, siz[y] -= siz[x];
}

void add(int u, int x) {
    if (u == x) return;
    add(u, p[x]);
    opt[x] = merge(edge[x].first, edge[x].second);
}

void del(int u, int x) {
    while (u != x) {
        split(opt[x].first, opt[x].second);
        x = p[x];
    }
}

int lca(int x, int y) {
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    while (dep[x] != dep[y]) {
        y = p[y];
    }
    while (x != y) {
        x = p[x];
        y = p[y];
    }
    return x;
}

void testCase() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        f[i] = i;
        siz[i] = 1;
    }
    initTree(rootA), initTree(rootB);
    block = int(sqrt(n));
    getBlocks(rootA), getBlocks(rootB);
    for (int i = 1; i <= n; ++i) q[i] = i;
    std::sort(q + 2, q + 1 + n, functor());
    assert(q[1] == 1);
    globalAns = m;
    opt[rootA] = merge(edge[rootA].first, edge[rootA].second);
    opt[rootB] = merge(edge[rootB].first, edge[rootB].second);
    ans[1] = globalAns;
    for (int i = 2; i <= n; ++i) {
        int x = q[i], y = q[i - 1];
        if (blockHead[x] != blockHead[y]) {
            del(rootB, blockHead[y + n]);
            int u = lca(blockHead[x], blockHead[y]);
            del(u, blockHead[y]);
            add(u, blockHead[x]);
            add(rootB, blockHead[x + n]);
        } else if (blockHead[x + n] != blockHead[y + n]) {
            int u = lca(blockHead[x + n], blockHead[y + n]);
            del(u, blockHead[y + n]);
            add(u, blockHead[x + n]);
        }
        add(blockHead[x], x);
        add(blockHead[x + n], x + n);
        ans[x] = globalAns;
        del(blockHead[x + n], x + n);
        del(blockHead[x], x);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", ans[i]);
    }
    for (int i = 1; i <= (n << 1); ++i) {
        opt[i] = {0, 0};
        dfn[i] = blockHead[i] = blockSize[i] = 0;
        VI_CLEAR(vec[i]);
    }
    cnt = 0;
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
