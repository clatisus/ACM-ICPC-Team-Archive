#include <bits/stdc++.h>

#define MAXN (300010)

int n, m, q;
int du[MAXN], f[MAXN], siz[MAXN], cnt[MAXN], cycle;
struct edge{
    int u, v, w;
    bool operator < (const edge &rhs) const {
        return w < rhs.w;
    }
}e[MAXN];
std::pair<int, int> t[MAXN];
std::pair<int, int> ans[MAXN];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void check(int x, int a) {
    if (cnt[x] == siz[x]) cycle += a;
}

void addDu(int u, int a) {
    if (++du[u] == 2) ++cnt[a];
    else if (du[u] == 3) --cnt[a];
}

void merge(int u, int v) {
    int a = find(u), b = find(v);
    if (a == b) {
        check(a, -1);
    } else {
        check(a, -1), check(b, -1);
        f[a] = b;
        siz[b] += siz[a];
        cnt[b] += cnt[a];
    }
    addDu(u, b), addDu(v, b);
    check(b, 1);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        ++ du[e[i].u];
        ++ du[e[i].v];
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%d", &t[i].first);
        t[i].second = i;
    }
    std::sort(e + 1, m + e + 1);
    std::sort(t + 1, q + t + 1);
    int du2 = 0;
    int nodes = n;
    for (int i = 1; i <= n; ++i) {
        if (du[i] == 2) ++ du2;
        if (du[i] == 0) -- nodes;
    }
    for (int i = 1, j = 1; i <= q; ++i) {
        while (j <= m && e[j].w < t[i].first) {
            if (du[e[j].u] == 2) -- du2;
            if (du[e[j].v] == 2) -- du2;
            if (-- du[e[j].u] == 0) -- nodes;
            if (-- du[e[j].v] == 0) -- nodes;
            if (du[e[j].u] == 2) ++ du2;
            if (du[e[j].v] == 2) ++ du2;
            ++ j;
        }
        ans[t[i].second] = {nodes - du2, m - j + 1 - du2};
    }
    for (int i = 1; i <= n; ++i) du[i] = 0, f[i] = i, siz[i] = 1;
    for (int i = q, j = m; i; --i) {
        while (j && e[j].w >= t[i].first) {
            merge(e[j].u, e[j].v);
            --j;
        }
        ans[t[i].second].first += cycle;
        ans[t[i].second].second += cycle;
    }

    for (int i = 1; i <= q; ++i) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}

