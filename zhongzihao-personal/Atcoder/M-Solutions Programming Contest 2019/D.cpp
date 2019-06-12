#include <bits/stdc++.h>

const int N = 10010;
typedef std::pair<int, int> pii;

std::set<int> e[N];
int ans[N];
int c[N];
std::vector<pii> edges;

int main() {
    int n;
    scanf("%d", &n);
    std::set<pii> set;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].insert(v);
        e[v].insert(u);
        edges.push_back({u, v});
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= n; ++i) {
        set.insert({e[i].size(), i});
    }
    std::sort(c, c + n);
    for (int i = 0; i < n; ++i) {
        auto u = set.begin();
        int x = u->second;
        set.erase(u);
        ans[x] = c[i];
        for (auto v : e[x]) {
            set.erase({e[v].size(), v});
            e[v].erase(x);
            set.insert({e[v].size(), v});
        }
    }
    int sum = 0;
    for (auto u : edges) {
        sum += std::min(ans[u.first], ans[u.second]);
    }
    printf("%d\n", sum);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}
