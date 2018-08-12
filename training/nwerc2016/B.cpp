#include <bits/stdc++.h>

inline void read(int &x) {
    char c; while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); (x *= 10) += (c - '0'));
}

const int max_N = (int) 1e5 + 21;

int n, m, dfn[max_N], low[max_N], cnt;

int sccno[max_N], scc_cnt, st[max_N], top;

std::vector<int> vec[max_N], scc[max_N];

std::unordered_map<int, int> len[max_N];
std::unordered_set<int> set[max_N];

int deg[max_N], dp[max_N];

#define SZ(x) int((x).size())

void scc_init(std::vector<int> &scc, int sccid) {
    static int dis[6][1 << 6], length[6][6];

    for (auto u : scc)
        for (auto v : vec[u]) {
            if (sccno[v] != sccid) continue;
            set[u].insert(v);
        }

    int n = SZ(scc);

    memset(length, 0, sizeof(length));

    for (int s = 0; s < n; ++s) {
        memset(dis, 0, sizeof(dis));
        dis[s][1 << s] = 1;
        for (int Set = (1 << s); Set < (1 << n); ++Set) {
            if (!((Set >> s) & 1)) continue;
            for (int u = 0; u < n; ++u) {
                if (!dis[u][Set]) continue;

                length[s][u] = std::max(length[s][u], dis[u][Set]);

                for (int v = 0; v < n; ++v) {
                    if ((Set >> v) & 1) continue;
                    if (!set[scc[u]].count(scc[v])) continue;
                    dis[v][Set | (1 << v)] = dis[u][Set] + 1;
                }
            }
        }
    }

    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v) {
            len[scc[u]][scc[v]] = length[u][v];
        }
}

void dfs(int u) {
    st[++top] = u;
    dfn[u] = low[u] = ++cnt;

    for (auto v : vec[u]) {
        if (!dfn[v]) {
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        } else if (!sccno[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }

    if (dfn[u] != low[u]) return;

    sccno[u] = ++scc_cnt;
    while (st[top] != u) {
        scc[scc_cnt].push_back(st[top]);
        sccno[st[top--]] = scc_cnt;
    }
    scc[scc_cnt].push_back(u);
    --top;

    assert(SZ(scc[scc_cnt]) <= 5);

    scc_init(scc[scc_cnt], scc_cnt);
}

int Q[max_N], tail, ans;

int main() {
    read(n), read(m);
    for (int i = 1, u, v; i <= m; ++i) {
        read(u), read(v);
        vec[u].push_back(v);
    }

    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) dfs(i);

    //debug1
    //for (int i = 1; i <= n; ++i) printf("sccno[%d] = %d\n", i, sccno[i]);

    for (int u = 1; u <= n; ++u)
        for (auto v : vec[u]) {
            if (sccno[u] == sccno[v]) continue;
            ++deg[sccno[v]];
        }

    for (int i = 1; i <= scc_cnt; ++i) {
        if (!deg[i]) Q[++tail] = i;
    }

    for (int i = 1; i <= tail; ++i) {
        int uscc = Q[i];

        for (auto u : scc[uscc])
            for (auto v : scc[uscc]) {
                ans = std::max(ans, dp[u] + len[u][v]);
            }

        for (auto u : scc[uscc]) {
            for (auto v : vec[u]) {
                if (uscc == sccno[v]) continue;
                for (auto uu : scc[uscc]) {
                    dp[v] = std::max(dp[v], dp[uu] + len[uu][u]);
                }
                if (!--deg[sccno[v]]) {
                    Q[++tail] = sccno[v];
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}

/**
11 14
1 2
2 3
3 4
4 2
4 5
5 6
6 7
7 5
3 8
8 9
7 9
9 10
10 11
11 9

5 5
1 2
2 3
3 4
4 5
5 1

7 8
1 2
2 3
3 4
4 5
5 1
2 6
6 7
7 6

12 12
1 2
2 3
3 4
4 5
5 6
6 7
7 5
5 8
8 9
9 10
10 11
11 12
*/
