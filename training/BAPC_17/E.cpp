#include <bits/stdc++.h>

const int max_N = 500 + 21;

namespace maxFlow {
    using flowType = int;
    const flowType inf = 0x3f3f3f3f; //a number larger than all flow

    struct edge {
        int v, n; //vertex, next
        flowType c; //capacity
    };

    std::vector<edge> e; //all edges
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

    /**
     * initialize
     * @param n vertexes number
     */
    void init(int n) {
        e.clear();
        memset(head + 1, -1, n * sizeof(int));
        M = 0;
    }

    /**
     * Add an edge from u to v
     * @param u from
     * @param v to
     * @param c capacity
     */
    void addEdge(int u, int v, flowType c) {
        e.push_back({v, head[u], c});
        head[u] = M++;
        e.push_back({u, head[v], 0});
        head[v] = M++;
    }

    /**
     * Computing max flow from s to t.
     * @param n vertexes number
     * @param s from
     * @param t to
     * @return max flow
     */
    flowType dinic(int n, int s, int t) {
        flowType ret = 0;
        while (bfs(n, s, t)) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            ret += dfs(t, s, inf);
        }
        return ret;
    }
};

int N, B, R;

std::pair<int, int> b[max_N], r[max_N];

int dis[max_N][max_N], _dis[max_N * max_N], tot;

#define sqr(x) ((x) * (x))

bool check(int mid) {
    int n = B + R + 2, s = n - 1, t = n;
    maxFlow::init(n);
    for (int i = 1; i <= B; ++i) maxFlow::addEdge(s, i, 1);
    for (int j = 1; j <= R; ++j) maxFlow::addEdge(B + j, t, 1);
    for (int i = 1; i <= B; ++i)
        for (int j = 1; j <= R; ++j) {
            if (dis[i][j] >= _dis[mid]) continue;
            maxFlow::addEdge(i, B + j, 1);
        }
    int indep = B + R - maxFlow::dinic(n, s, t);
    return indep >= N;
}

int main() {
    scanf("%d%d%d", &N, &B, &R);
    for (int i = 1; i <= B; ++i) {
        scanf("%d%d", &b[i].first, &b[i].second);
    }
    for (int i = 1; i <= R; ++i) {
        scanf("%d%d", &r[i].first, &r[i].second);
    }
    for (int i = 1; i <= B; ++i)
        for (int j = 1; j <= R; ++j) {
            dis[i][j] = sqr(b[i].first - r[j].first) + sqr(b[i].second - r[j].second);
            _dis[++tot] = dis[i][j];
        }
    std::sort(_dis + 1, _dis + 1 + tot);
    tot = std::unique(_dis + 1, _dis + 1 + tot) - (_dis + 1);
    int l = 1, r = tot;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (!check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%.15f\n", std::sqrt(_dis[l - 1]));
    return 0;
}
