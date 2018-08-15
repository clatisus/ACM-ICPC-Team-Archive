#include <bits/stdc++.h>

#define ll long long

namespace maxFlow {
    using flowType = ll;
    const flowType inf = 0x3f3f3f3f3f3f3f3fll;
    const int max_N = 2333;

    struct edge {
        int v, n;
        flowType c;
    };

    std::vector<edge> e;
    int M, head[max_N], cur[max_N], dis[max_N];

    bool bfs(int n, int s, int t) {
        static int Q[max_N];
        int tail = 0;
        memset(dis + 1, -1, n * sizeof(int));
        dis[s] = 0, Q[tail++] = s;
        for (int i = 0; i < tail; ++i) {
            int u = Q[i];
            for (int it = head[u]; ~it; it = e[it].n) {
                if (!e[it].c) continue;
                int v = e[it].v;
                if (dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    Q[tail++] = v;
                }
            }
        }
        return dis[t] != -1;
    }

    flowType dfs(int t, int u, flowType a) {
        if (u == t) return a;
        flowType ret = 0, tmp;
        for (int &it = cur[u]; ~it; it = e[it].n) {
            int v = e[it].v;
            if (!e[it].c || dis[u] + 1 != dis[v]) continue;
            tmp = dfs(t, v, std::min(a - ret, e[it].c));
            if (tmp) {
                e[it].c -= tmp, e[it ^ 1].c += tmp;
                if ((ret += tmp) == a) break;
            }
        }
        if (!ret) dis[u] = -1;
        return ret;
    }

    void init(int n) {
        e.clear();
        memset(head + 1, -1, n * sizeof(int));
        M = 0;
    }

    void addEdge(int u, int v, flowType c) {
        e.push_back({v, head[u], c});
        head[u] = M++;
        e.push_back({u, head[v], 0});
        head[v] = M++;
    }

    flowType dinic(int n, int s, int t) {
        flowType ret = 0;
        while (bfs(n, s, t)) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            ret += dfs(t, s, inf);
        }
        return ret;
    }
};

#define MAXN (1010)

int n, q, s;
int to[MAXN];
ll suma[MAXN];

int id(int i, int j) { return (i - 1) * n + j; }
int rid(int i, int j) { return id(i, j) + q * n; }

int main() {
    scanf("%d%d%d", &n, &q, &s);
    int S = 2 * q * n + n + 1, T = S + 1;
    maxFlow::init(T);
    for (int i = 1; i <= s; ++i) scanf("%d", to + i);
    for (int i = 1; i <= q; ++i) {
        int c;
        scanf("%d", &c);
        for (int j = 1; j <= n; ++j) {
            maxFlow::addEdge(id(i, j), rid(i, j), c);
            maxFlow::addEdge(rid(i, j), 2 * q * n + j, maxFlow::inf);
            if (j < n) {
                maxFlow::addEdge(rid(i, j), id(i, j + 1), maxFlow::inf);
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int d;
        scanf("%d", &d);
        maxFlow::addEdge(2 * q * n + i, T, d);
        for (int j = 1; j <= q; ++j) suma[j] = 0;
        for (int j = 1; j <= s; ++j) {
            int x;
            scanf("%d", &x);
            suma[to[j]] += x;
        }
        for (int j = 1; j <= q; ++j) {
            ans += suma[j];
            maxFlow::addEdge(S, id(j, i), suma[j]);
        }
    }
    puts(maxFlow::dinic(T, S, T) == ans ? "possible" : "impossible");
    return 0;
}
