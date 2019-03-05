#include <bits/stdc++.h>

const int MAXN = 110;
const int MAXM = 10010;

int n, m, tot;
int vis[MAXN][MAXN];
int used[MAXN];
int x[MAXM], y[MAXM], du[MAXN];
std::vector<std::vector<int>> graph;
std::vector<std::pair<int, int>> out;

// [0, m) coe, m is b
std::bitset<MAXM> gauss(std::vector<std::bitset<MAXM>> &set, int m, bool &flag){
    int n = (int)set.size(), rank = 0;
    for (int i = 0; i < m; ++ i){
        for (int j = rank; j < n; ++ j){
            if (set[j][i]){
                std::swap(set[j], set[rank]);
                break;
            }
        }
        if (!set[rank][i]) continue;
        for (int j = 0; j < n; ++ j){
            if (j == rank) continue;
            if (set[j][i]){
                set[j] ^= set[rank];
            }
        }
        ++rank;
    }
    for (int i = rank; i < n; ++ i){
        if (set[i][m]){
            flag = false;
            return {};
        }
    }
    std::bitset<MAXM> ans;
    for (int i = rank - 1; ~i; --i){
        int sit = (int)set[i]._Find_first();
        ans[sit] = set[i][m];
    }
    return ans;
}

void dfs(int u, std::vector<int> &vec) {
    used[u] = true;
    vec.push_back(u);
    for (int v = 0; v < n; ++v) {
        if (!vis[u][v] || used[v]) continue;
        dfs(v, vec);
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
    std::vector<std::bitset<MAXM>> vec;
    vec.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (vis[i][j]) continue;
            x[tot] = i;
            y[tot] = j;
            vec[i].set(tot);
            vec[j].set(tot);
            tot++;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (du[i]) {
            vec[i].set(tot);
        }
    }
    bool flag = true;
    std::bitset<MAXM> ans = gauss(vec, tot, flag);
    if (!flag) {
        puts("-1");
        return 0;
    }
    for (int i = 0; i < tot; ++i) {
        if (!ans.test(i)) continue;
        vis[x[i]][y[i]] = vis[y[i]][x[i]] = 2;
        //printf("x = %d, y = %d\n", x[i] + 1, y[i] + 1);
    }
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
