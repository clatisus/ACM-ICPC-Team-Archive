#include <bits/stdc++.h>

const int MAXN = 110;
const int MAXM = 10010;

int n, m;
int vis[MAXN][MAXN];
int used[MAXN];
int du[MAXN];
std::vector<std::vector<int>> graph;
std::vector<std::pair<int, int>> out;

void dfs(int u, std::vector<int> &vec) {
    used[u] = true;
    vec.push_back(u);
    for (int v = 0; v < n; ++v) {
        if (!vis[u][v] || used[v]) continue;
        dfs(v, vec);
    }
}

void dfs_tree(int u) {
    used[u] = true;
    for (int v = 0; v < n; ++v) {
        if (vis[u][v] || used[v]) continue;
        dfs_tree(v);
        if (du[v]) {
            vis[u][v] = vis[v][u] = 2;
            du[v] ^= 1;
            du[u] ^= 1;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        vis[u][v] = vis[v][u] = 1;
        du[u] ^= 1;
        du[v] ^= 1;
    }
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        dfs_tree(i);
        if (du[i]) {
            puts("-1");
            return 0;
        }
    }

    memset(used, 0, sizeof(used));
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        graph.push_back({});
        dfs(i, graph.back());
    }
    if (graph.size() == 1) {
        ;
    } else if (graph.size() >= 3) {
        std::vector<int> node;
        for (auto v : graph) {
            node.push_back(v[0]);
        }
        for (int i = 0; i < node.size(); ++i) {
            int j = i == node.size() - 1 ? 0 : i + 1;
            vis[node[i]][node[j]] = vis[node[j]][node[i]] = 2;
        }
    } else {
        if (graph[0].size() >= 2 && graph[1].size() >= 2) {
            int u1 = graph[0][0], v1 = graph[0][1];
            int u2 = graph[1][0], v2 = graph[1][1];
            vis[u1][u2] = vis[u2][u1] = 2;
            vis[u1][v2] = vis[v2][u1] = 2;
            vis[v1][u2] = vis[u2][v1] = 2;
            vis[v1][v2] = vis[v2][v1] = 2;
        } else {
            if (graph[1].size() == 1) std::swap(graph[0], graph[1]);
            bool flag = false;
            int p = graph[0][0];
            for (int i = 0, sz = (int)graph[1].size(); i < sz; ++i) {
                int u = graph[1][i];
                for (int j = i + 1; j < sz; ++j) {
                    int v = graph[1][j];
                    if (!vis[u][v]) {
                        vis[p][u] = vis[u][p] = 2;
                        vis[p][v] = vis[v][p] = 2;
                        vis[u][v] = vis[v][u] = 2;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            if (!flag) {
                for (int i = 0, sz = (int)graph[1].size(); i < sz; ++i) {
                    int u = graph[1][i];
                    for (int j = i + 1; j < sz; ++j) {
                        int v = graph[1][j];
                        if (vis[u][v] == 2) {
                            vis[u][v] = vis[v][u] = 0;
                            vis[p][u] = vis[u][p] = 2;
                            vis[p][v] = vis[v][p] = 2;
                            flag = true;
                            break;
                        }
                    }
                    if (flag) break;
                }
                if (!flag) {
                    puts("-1");
                    return 0;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (vis[i][j] == 2) {
                out.emplace_back(i, j);
            }
        }
    }
    printf("%d\n", (int)out.size());
    for (auto p : out) {
        printf("%d %d\n", p.first + 1, p.second + 1);
    }
    return 0;
}
