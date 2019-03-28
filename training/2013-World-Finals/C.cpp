//
// Created by zzh on 2019/3/7.
//

#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

const int inf = 0x3f3f3f3f;

int n, m, c, cnt[max_N], pos[max_N], vis[max_N];

int u[max_N], v[max_N], w[max_N];

namespace ShortestPath {
    std::vector<std::pair<int, int>> vec[max_N];

    int dis[max_N], vis[max_N];

    std::priority_queue<std::pair<int, int>> pq;

    void solve() {
        for (int i = 1; i <= m; ++i) {
            vec[u[i]].emplace_back(v[i], w[i]);
            vec[v[i]].emplace_back(u[i], w[i]);
        }
        for (int i = 1; i <= n; ++i) {
            dis[i] = inf;
        }
        pq.emplace(dis[1] = 0, 1);
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto &pr : vec[u]) {
                int v = pr.first;
                int tmp = dis[u] + pr.second;
                if (dis[v] > tmp) {
                    dis[v] = tmp;
                    pq.emplace(-dis[v], v);
                }
            }
        }
    }
}

namespace MaximumFlow {
    struct edge {
        int v, n, c;

        edge(int v = 0, int n = 0, int c = 0) : v(v), n(n), c(c) {}
    };

    std::vector<edge> e;

    int M, head[max_N], cur[max_N], dis[max_N];

    bool bfs(int n, int s, int t) {
        static int Q[max_N];
        int tail = 0;
        memset(dis + 1, -1, n * sizeof(int));
        dis[s] = 0;
        Q[tail++] = s;
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

    int dfs(int t, int u, int a) {
        if (u == t) return a;
        int ret = 0, tmp;
        for (int &it = cur[u]; ~it; it = e[it].n) {
            int v = e[it].v;
            if (!e[it].c || dis[u] + 1 != dis[v]) continue;
            tmp = dfs(t, v, std::min(a - ret, e[it].c));
            if (tmp) {
                e[it].c -= tmp;
                e[it ^ 1].c += tmp;
                if ((ret += tmp) == a)
                    break;
            }
        }
        if (!ret) dis[u] = -1;
        return ret;
    }

    inline void init(int n) {
        e.clear();
        memset(head + 1, -1, n * sizeof(int));
        M = 0;
    }

    inline void addEdge(int u, int v, int c) {
        e.emplace_back(v, head[u], c);
        head[u] = M++;
        e.emplace_back(u, head[v], 0);
        head[v] = M++;
    }

    int dinic(int n, int s, int t) {
        int ret = 0;
        while (bfs(n, s, t)) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            ret += dfs(t, s, inf);
        }
        return ret;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", u + i, v + i, w + i);
    }
    for (int i = 1; i <= c; ++i) {
        scanf("%d", pos + i);
    }
    ShortestPath::solve();
    int ans = 0;
    for (int i = 1; i <= c; ++i) {
        if (vis[i]) continue;
        int tot = 0;
#define S (n + 1)
#define T (S + 1)
#define N T
        MaximumFlow::init(N);
        for (int u = 1; u <= n; ++u) {
            cnt[u] = 0;
            for (auto &pr : ShortestPath::vec[u]) {
                int v = pr.first;
                int tmp = ShortestPath::dis[u] + pr.second;
                if (ShortestPath::dis[v] == tmp) {
                    MaximumFlow::addEdge(u, v, 1);
                }
            }
        }
        for (int j = i; j <= c; ++j) {
            if (ShortestPath::dis[pos[i]] == ShortestPath::dis[pos[j]]) {
                ++tot;
                ++cnt[pos[j]];
                vis[j] = 1;
            }
        }
        MaximumFlow::addEdge(S, 1, tot);
        for (int u = 1; u <= n; ++u) {
            if (cnt[u]) {
                MaximumFlow::addEdge(u, T, cnt[u]);
            }
        }
        ans += MaximumFlow::dinic(N, S, T);
    }
    printf("%d\n", ans);
}