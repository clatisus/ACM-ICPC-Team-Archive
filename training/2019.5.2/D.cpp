#include <bits/stdc++.h>

const int max_N = 5010;
using ll = long long;

namespace MCMF {
    const ll inf = 0x3f3f3f3f3f3f3f3fll; //a number larger than all dis

    int M, vis[max_N], pre[max_N], flow;
    ll dis[max_N], cost;

    struct edge {
        int v, c;
        ll w; //vertex, capacity, weight
    };

    std::vector<edge> e; //all edges
    std::vector<int> vec[max_N]; //edge indexes for each vertex

    bool spfa(int n, int s, int t) {
        static int Q[max_N];
        int head = 0, tail = 0;
        memset(dis + 1, 0x3f, n * sizeof(ll));
        memset(vis + 1, 0, n * sizeof(int));
        dis[s] = 0, vis[s] = 1, Q[tail++] = s;
        while (head != tail) {
            int u = Q[head++];
            vis[u] = 0;
            if (head == max_N) head = 0;
            for (auto it : vec[u]) {
                if (!e[it].c) continue;
                int v = e[it].v;
                auto tmp = dis[u] + e[it].w;
                if (tmp < dis[v]) {
                    pre[v] = it, dis[v] = tmp;
                    if (!vis[v]) {
                        vis[v] = 1, Q[tail++] = v;
                        if (tail == max_N) tail = 0;
                    }
                }
            }
        }
        return dis[t] < inf;
    }

    int addEdge(int u, int v, int c, ll w) {
        int ret = M;
        e.push_back({v, c, w});
        vec[u].push_back(M++);
        e.push_back({u, 0, -w});
        vec[v].push_back(M++);
        return ret;
    }

    ll minCost(int n, int s, int t) {
        while (spfa(n, s, t)) { //for max flow
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
        return cost;
    }
};

int n, k, l, r;
int s[max_N], e[max_N], x[max_N];
char str[max_N];

int main() {
    freopen("delight.in", "r", stdin);
    freopen("delight.out", "w", stdout);
    ll ans = 0;
    scanf("%d%d%d%d", &n, &k, &l, &r);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", s + i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", e + i);
        ans += e[i];
        str[i - 1] = 'E';
    }
    r = k - r;

    int S = (n - k + 1) * 2 + 1 + 1, T = S + 1;
    // add edge x1, x2, ..., xn
    for (int i = 1; i <= n; ++i) {
        x[i] = MCMF::addEdge(
                std::max(1, (i - k) * 2 + 1),
                std::min(S - 1, 2 * i + 1),
                1,
                e[i] - s[i]
        );
    }
    // add edge yi
    for (int i = 1; i <= n - k + 1; ++i) {
        MCMF::addEdge(2 * i, 2 * i - 1, 1e9, 0);
    }
    // add edge zi
    for (int i = 1; i <= n - k + 1; ++i) {
        MCMF::addEdge(2 * i, 2 * i + 1, 1e9, 0);
    }
    // add right const (r - l)
    for (int i = 2; i <= S - 1; i += 2) {
        MCMF::addEdge(S, i, r - l, 0);
    }
    // add left const (r - l)
    for (int i = 3; i < S - 1; i += 2) {
        MCMF::addEdge(i, T, r - l, 0);
    }
    // add right l
    MCMF::addEdge(S, 1, l, 0);
    // add left r
    MCMF::addEdge(S - 1, T, r, 0);

    ans -= MCMF::minCost(T, S, T);
    for (int i = 1; i <= n; ++i) {
        if (MCMF::e[x[i]].c == 0) {
            str[i - 1] = 'S';
        }
    }
    printf("%lld\n%s\n", ans, str);
    return 0;
}
/*
10 4 1 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
 */