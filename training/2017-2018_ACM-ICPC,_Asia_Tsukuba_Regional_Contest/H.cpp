#include <bits/stdc++.h>

namespace maxFlow {
    using flowType = int;
    const flowType inf = 0x3f3f3f3f;
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

#define MAXN (410)

int n, m, maxd;
int l[MAXN], r[MAXN], p[MAXN];
int cnt[MAXN], out[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", l + i, r + i);
        maxd = std::max(maxd, l[i]);
        maxd = std::max(maxd, r[i]);
    }
    int ans1 = 0, ans2 = 0;
    // greedy get ans1
    std::multiset<int> set;
    for (int i = 1; i <= n; ++i) p[i] = i;
    std::sort(p + 1, n + p + 1, [&](int a, int b) {
    	return std::make_pair(l[a], std::make_pair(r[a], (a <= m))) < std::make_pair(l[b], std::make_pair(r[b], (b <= m)));
    });
    for (int i = 1, j = 1; i <= maxd; ++i) {
    	while (j <= n && l[p[j]] == i) set.insert(r[p[j++]]);
    	while (!set.empty() && *set.begin() < i) set.erase(set.begin());
    	if (!set.empty()) {
    		set.erase(set.begin());
    		++ans1;
    	}
    }
    printf("%d\n", ans1);

    // mincut get ans2
    int S = n + maxd + maxd + 1, T = S + 1;
    maxFlow::init(T);
    for (int i = 1; i <= m; ++i) maxFlow::addEdge(S, i, 1);
    for (int i = m + 1; i <= n; ++i) maxFlow::addEdge(i, T, 1);
    for (int i = 1; i <= m; ++i) {
        for (int j = l[i]; j <= r[i]; ++j) {
            maxFlow::addEdge(i, n + j, 1);
        }
    }
    for (int i = m + 1; i <= n; ++i) {
        for (int j = l[i]; j <= r[i]; ++j) {
            maxFlow::addEdge(n + maxd + j, i, 1);
        }
    }
    for (int i = 1; i <= maxd; ++i) maxFlow::addEdge(n + i, n + maxd + i, 1);
    ans2 = maxFlow::dinic(T, S, T);
    printf("%d\n", ans2);
    return 0;
}
