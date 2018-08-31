#include <bits/stdc++.h>

#define MAXN (100010)

int n, m;
std::vector<std::pair<int, int>> par[MAXN], per[MAXN];
std::vector<std::pair<int, int>> vec;
int tag[MAXN]; // 1 h, 2 v
bool vis[MAXN];
bool edge[MAXN];
std::set<int> set;

void dfs(int u) {
    vis[u] = true;
    for (auto p : par[u]) {
        if (!tag[p.first]) tag[p.first] = tag[u], edge[p.second] = true;
        else if (tag[p.first] != tag[u]) {
            puts("inconsistent");
            exit(0);
        } else if (!edge[p.second]) {
            set.insert(p.second);
        }
        if (!vis[p.first]) dfs(p.first);
    }
    for (auto p : per[u]) {
        if (!tag[p.first]) tag[p.first] = 3 - tag[u], edge[p.second] = true;
        else if (tag[p.first] != 3 - tag[u]) {
            puts("inconsistent");
            exit(0);
        } else if (!edge[p.second]) {
            set.insert(p.second);
        }
        if (!vis[p.first]) dfs(p.first);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        static char opt[10];
        int u, v;
        scanf("%s%d", opt, &u);
        if (opt[0] == 'h') {
            vec.push_back({u, i});
        } else if (opt[0] == 'v') {
            vec.push_back({-u, i});
        } else if (opt[0] == 'p') {
            scanf("%d", &v);
            if (opt[1] == 'a') {
                par[u].push_back({v, i});
                par[v].push_back({u, i});
            } else {
                per[u].push_back({v, i});
                per[v].push_back({u, i});
            }
        }
    }
    for (auto p : vec) {
        if (p.first < 0) {
        // v
            if (tag[-p.first] == 1) {
                puts("inconsistent");
                return 0;
            } else if (tag[-p.first] == 2) {
                set.insert(p.second);
            } else {
                tag[-p.first] = 2;
            }
        } else {
            if (tag[p.first] == 2) {
                puts("inconsistent");
                return 0;
            } else if (tag[p.first] == 1) {
                set.insert(p.second);
            } else {
                tag[p.first] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i] && tag[i]) {
            dfs(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i] && !tag[i]) {
            tag[i] = 1;
            dfs(i);
        }
    }
    puts("consistent");
    printf("%d\n", (int) set.size());
    for (auto u : set) printf("%d ", u);
    printf("\n");
    return 0;
}
