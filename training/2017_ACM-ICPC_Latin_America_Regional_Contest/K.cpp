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

#define MAXN (30)

int r, c;
char s[MAXN][MAXN];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool in(int i, int j) {
    return 1 <= i && i <= r && 1 <= j && j <= c;
}

int id(int i, int j) { return (i - 1) * c + j; }

void testCase() {
    for (int i = 1; i <= r; ++i) {
        scanf("%s", s[i] + 1);
    }
    int S = r * c + 1, T = S + 1;
    maxFlow::init(T);
    int inw = 0;
    int out = 0;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            int w = s[i][j] == 'o' ? 1 : 2;
            if ((i + j) % 2) {
                inw += w;
                maxFlow::addEdge(S, id(i, j), w);
            } else {
                out += w;
                maxFlow::addEdge(id(i, j), T, w);
            }

            for (int k = 0; k < 4; ++k) {
                int x = i + dir[k][0];
                int y = j + dir[k][1];
                if (!in(x, y)) continue;
                if ((x + y) % 2) {
                    maxFlow::addEdge(id(x, y), id(i, j), 2);
                } else {
                    maxFlow::addEdge(id(i, j), id(x, y), 2);
                }
            }
        }
    }
    int flow = maxFlow::dinic(T, S, T);
    //printf("total = %d\n", total);
    //printf("flow = %d\n", flow);
    puts((inw == flow && out == flow) ? "Y" : "N");
}

int main() {
    while (~scanf("%d%d", &r, &c)) {
        testCase();
    }
    return 0;
}

