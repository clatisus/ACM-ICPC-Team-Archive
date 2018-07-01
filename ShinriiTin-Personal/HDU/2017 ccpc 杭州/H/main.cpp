/*
题目大意：给出两棵节点数都为$n\le10000$的树，根都为1号节点。
对于$m\le10000$个点的无向图G，每条边都与两棵树中的其中一个节点一一对应。
对于$i\in[1,n]$，问如果只用第一棵树中$i$到根节点链上的节点对应的所有边，
加上第二棵树中$i$到根节点链上的节点对应的所有边，求图G中连通块的数量。
题解：考虑离线使用莫队算法。
则需要使用并查集撤消来维护连通块数量，并保证撤消的操作位于时间线的最后。
将两棵树分块，记录每块的lca，然后将询问按两个点所在块的lca的dfn排序。
我们每次回答询问的时候，都先从两块的lca出发，增加到当前询问的范围，回答后再回退到lca。
因为每块的大小是$O(\sqrt{n})$级别的，因此块内转移是$O(n\sqrt{n})$次并查集操作。
- 当这一次的询问与前一次询问在第一棵树中块相同，但第二棵树中块不同的时候：则撤消回这两块的lca的lca，再添加到新块的lca
- 当这一次的询问与前一次询问在第一棵树中块不同的时候：先将第二棵树中的操作回退到根，再用上面的方法移动第一块的lca。
因为第一棵树中块发生变化的次数为$O(\sqrt{n})$，第二种情况时间复杂度不超过$O(n\sqrt{n})$次并查集操作。
而第一种情况的总时间复杂度由莫队算法可知是$O(n\sqrt{n})$乘上并查集单次操作复杂度。
因为并查集要撤消，因此我们使用按秩合并的方法，总的时间复杂度为O(n\sqrt{n}\log{n})$.
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
