#include <bits/stdc++.h>

namespace MCMF {
    const int max_N = 300; //vertexes number
    const int inf = 0x3f3f3f3f; //a number larger than all dis

    int M, dis[max_N], vis[max_N], pre[max_N], flow, cost, cnt[max_N];
    bool flag;

    struct edge {
        int v, c, w;
    };

    std::vector<edge> e;
    std::vector<int> vec[max_N];

    bool spfa(int n, int s, int t) {
        static int Q[max_N];
        int head = 0, tail = 0;
        memset(dis + 1, 0x3f, n * sizeof(int));
        memset(vis + 1, 0, n * sizeof(int));
        memset(cnt + 1, 0, n * sizeof(int));
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
                        if (++ cnt[v] > n) {
                            flag = true;
                            return false;
                        }
                        if (tail == max_N) tail = 0;
                    }
                }
            }
        }
        return dis[t] < inf;
    }

    void addEdge(int u, int v, int c, int w) {
        e.push_back({v, c, w});
        vec[u].push_back(M++);
        e.push_back({u, 0, -w});
        vec[v].push_back(M++);
    }

    void minCost(int n, int s, int t) {
         while (spfa(n, s, t)) {
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

    void clear(int n) {
        e.clear();
        for (int i = 1; i <= n; ++i) {
            std::vector<int>().swap(vec[i]);
        }
        flag = false;
        M = flow = cost = 0;
    }
};

#define MAXN (310)

int n, m, L, U;
int szR[MAXN], szC[MAXN];
int dis[MAXN][MAXN];

void testCase() {
    static int Case = 0;
    scanf("%d%d%d%d", &n, &m, &L, &U);
    int S = n + m + 1, T = S + 1;
    MCMF::clear(T);

    int sum = 0;
    for (int i = 1; i <= n; ++i) szR[i] = m;
    for (int i = 1; i <= m; ++i) szC[i] = n;
    for (int i = 1; i <= n; ++i) {
        static char s[30];
        int x;
        for (int j = 1; j <= m; ++j) {
            scanf("%s", s);
            if (s[0] == 'X') {
                -- szR[i];
                -- szC[j];
            } else {
                sscanf(s, "%d", &x);
                MCMF::addEdge(n + j, i, MCMF::inf, U - x);
                MCMF::addEdge(i, n + j, MCMF::inf, x - L);
                sum += x;
            }
        }
    }
    for (int i = 1; i <= n; ++i) MCMF::addEdge(i, T, szR[i], 0);
    for (int i = 1; i <= m; ++i) MCMF::addEdge(S, n + i, szC[i], 0);
    MCMF::minCost(T, S, T);
    if (MCMF::flag) {
        printf("Case %d: Impossible\n", ++ Case);
        return;
    }
    printf("Case %d: %d\n", ++ Case, MCMF::cost + sum);
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n + m; ++i) {
        dis[0][i] = dis[i][i] = 0;
        for (auto it : MCMF::vec[i]) {
            if (it & 1) continue;
            int j = MCMF::e[it].v, w = MCMF::e[it].w, c = MCMF::e[it].c;
            if (dis[i][j] > w) dis[i][j] = w;
            if (c != MCMF::inf) {
                if (dis[j][i] > -w) dis[j][i] = -w;
            }
        }
    }
    for (int k = 0; k <= n + m; ++k) {
        for (int i = 0; i <= n + m; ++i) {
            for (int j = 0; j <= n + m; ++j) {
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    int min = dis[0][1];
    for (int i = 2; i <= n + m; ++i) min = std::min(min, dis[0][i]);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", dis[0][i] - min, " \n"[i == n]);
    }
    for (int i = 1; i <= m; ++i) {
        printf("%d%c", dis[0][i + n] - min, " \n"[i == m]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T --) {
        testCase();
    }
    return 0;
}
