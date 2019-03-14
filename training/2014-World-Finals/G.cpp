//O(n^4\log{n})
#include <bits/stdc++.h>

const int max_N = 500 + 21;
const int max_M = max_N * max_N;

int n, m, u[max_M], v[max_M], w[max_M], Q[max_M], h[max_M], tot;

int f[max_N], ans = INT_MAX;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    f[u] = v;
    return true;
}

#define pos(x) (x)
#define neg(x) ((x) + n)

int to[max_M], nxt[max_M], head[max_N], e_tot;

int dfn[max_N], low[max_N], cnt, sccno[max_N], scc_cnt;

int st[max_N], top;

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    st[++top] = u;
    for (int it = head[u]; it; it = nxt[it]) {
        int v = to[it];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (!sccno[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int v = 0;
        while (u != v) {
            v = st[top--];
            sccno[v] = scc_cnt;
        }
    }
}

inline void addEdge(int u, int v) {
    to[++e_tot] = v;
    nxt[e_tot] = head[u];
    head[u] = e_tot;
}

bool check(int s1, int s2) {
    for (int i = 1; i <= n * 2; ++i) {
        dfn[i] = low[i] = sccno[i] = head[i] = 0;
    }
    cnt = scc_cnt = top = e_tot = 0;
    for (int i = 1; i <= tot; ++i) {
        if (w[i] > h[s1]) {
            addEdge(pos(u[i]), neg(v[i]));
            addEdge(pos(v[i]), neg(u[i]));
        }
        if (w[i] > h[s2]) {
            addEdge(neg(u[i]), pos(v[i]));
            addEdge(neg(v[i]), pos(u[i]));
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i);
        if (sccno[pos(i)] == sccno[neg(i)]) {
            return false;
        }
    }
    return true;
}

void solve(int s1) {
    int l = 1, r = s1;
    while (r && h[s1] + h[r] >= ans) --r;
    if (!r || !check(s1, r)) return;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(s1, mid)) {
            ans = std::min(ans, h[s1] + h[mid]);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ++tot;
            scanf("%d", w + tot);
            u[tot] = i;
            v[tot] = j;
            Q[tot] = tot;
            h[tot] = w[tot];
        }
    }
    h[++tot] = 0;
    std::sort(h + 1, h + 1 + tot);
    m = int(std::unique(h + 1, h + 1 + tot) - h - 1);
    std::sort(Q + 1, Q + 1 + tot, [&](int x, int y) { return w[x] > w[y]; });
    for (int i = 1; i <= n; ++i) {
        f[pos(i)] = pos(i);
        f[neg(i)] = neg(i);
    }
    for (int s1 = m, k = 1; s1; --s1) {
        bool flag = false;
        while (k <= tot && w[Q[k]] >= h[s1]) {
            flag |= merge(pos(u[Q[k]]), neg(v[Q[k]]));
            flag |= merge(neg(u[Q[k]]), pos(v[Q[k]]));
            ++k;
        }
        if (flag) solve(s1);
        flag = true;
        for (int i = 1; i <= n; ++i) {
            if (find(pos(i)) == find(neg(i))) {
                flag = false;
                break;
            }
        }
        if (!flag) break;
    }
    printf("%d\n", ans);
}
