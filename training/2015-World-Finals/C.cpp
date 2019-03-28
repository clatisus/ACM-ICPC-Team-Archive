//
// Created by zzh on 2019/3/16.
//

#include <bits/stdc++.h>

const int max_N = 666;

using LL = long long;

const LL offset = 0x3f3f3f3f;

namespace MCMF {
    const LL inf = 0x3f3f3f3f3f3f3f3fLL;

    int M, vis[max_N], pre[max_N], flow;

    LL dis[max_N], cost;

    struct edge {
        int v, c;
        LL w;

        edge(int v = 0, int c = 0, LL w = 0) :
            v(v), c(c), w(w) {}
    };

    std::vector<edge> e;
    std::vector<int> vec[max_N];

    bool spfa(int n, int s, int t) {
        static int Q[max_N];
        int head = 0, tail = 0;
        memset(dis + 1, 0x3f, n * sizeof(LL));
        memset(vis + 1, 0, n * sizeof(int));
        dis[s] = 0;
        vis[s] = 1;
        Q[tail++] = s;
        while (head != tail) {
            int u = Q[head++];
            vis[u] = 0;
            if (head == max_N) head = 0;
            for (auto it : vec[u]) {
                if (!e[it].c) continue;
                int v = e[it].v;
                auto tmp = dis[u] + e[it].w;
                if (tmp < dis[v]) {
                    pre[v] = it;
                    dis[v] = tmp;
                    if (!vis[v]) {
                        vis[v] = 1;
                        Q[tail++] = v;
                        if (tail == max_N) {
                            tail = 0;
                        }
                    }
                }
            }
        }
        return dis[t] < inf;
    }

    inline void addEdge(int u, int v, int c, int w) {
        e.emplace_back(v, c, w);
        vec[u].push_back(M++);
        e.emplace_back(u, 0, -w);
        vec[v].push_back(M++);
    }

    void minCost(int n, int s, int t) {
        while (spfa(n, s, t) && dis[t] < 0) {
            int adt = ~0U >> 1;
            for (int x = t; x != s; x = e[pre[x] ^ 1].v) {
                adt = std::min(adt, e[pre[x]].c);
            }
            flow += adt;
            cost += adt * dis[t];
            for (int x = t; x != s; x = e[pre[x] ^ 1].v) {
                e[pre[x]].c -= adt;
                e[pre[x] ^ 1].c += adt;
            }
        }
    }
}

int n, k;

#define N (2 * n + 3)
#define u(x) (x)
#define v(x) (u(x) + n)
#define SS (2 * n + 1)
#define S (2 * n + 2)
#define T (2 * n + 3)

int main() {
    scanf("%d%d", &n, &k);
    MCMF::addEdge(S, SS, k, 0);
    for (int i = 1; i <= n; ++i) {
        MCMF::addEdge(v(i), T, offset, 0);
        MCMF::addEdge(u(i), v(i), 1, -offset);
        MCMF::addEdge(u(i), v(i), offset, 0);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1, a; j <= n; ++j) {
            scanf("%d", &a);
            if (!i) {
                MCMF::addEdge(SS, u(j), offset, a);
            } else {
                MCMF::addEdge(v(i), u(j), offset, a);
            }
        }
    }
    MCMF::minCost(N, S, T);
    MCMF::cost += n * offset;
    printf("%lld\n", MCMF::cost);
}
/*
3 2
40 30 40
50 10
50

3 2
10 10 10
20 21
21
 */