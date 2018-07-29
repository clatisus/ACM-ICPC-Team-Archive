#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long

int n, m;
int a[MAXN];
std::vector<std::pair<int, int> > vec[MAXN];
int du[MAXN];
std::vector<std::pair<int, int> > bb[MAXN];
std::vector<int> bv[MAXN];
bool inans[MAXN];
bool isbig[MAXN];
int ans = 0;

int main() {
    scanf("%d%d", &n, &m);
    int SQRT = int(sqrt(m)) + 1;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= m; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back({v, i});
        vec[v].push_back({u, i});
        if (a[u] != a[v]) ++ ans, inans[i] = true;
        ++ du[u];
        ++ du[v];
    }
    for (int i = 1; i <= n; ++ i) {
        if (du[i] >= SQRT) {
            isbig[i] = true;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        if (isbig[i]) {
            bv[i].resize(MAXN);
            for (auto p : vec[i]) {
                int j = p.first;
                if (isbig[j]) {
                    bb[i].push_back(p);
                } else {
                    ++ bv[i][a[j]];
                }
            }
        }
    }

    int q;
    scanf("%d", &q);
    while (q --) {
        int u, c;
        scanf("%d%d", &u, &c);
        if (c == a[u]) {
            printf("%d\n", ans);
            continue;
        }
        if (isbig[u]) {
            for (auto p : bb[u]) {
                int v = p.first, k = p.second;
                if (c == a[v]) {
                    if (inans[k]) {
                        inans[k] = false;
                        -- ans;
                    }
                } else {
                    if (!inans[k]) {
                        inans[k] = true;
                        ++ ans;
                    }
                }
            }
            ans -= bv[u][c];
            ans += bv[u][a[u]];
        } else {
            for (auto p : vec[u]) {
                int v = p.first;
                if (isbig[v]) {
                    if (a[u] != a[v]) -- ans;
                    -- bv[v][a[u]];
                    ++ bv[v][c];
                    if (c != a[v]) ++ ans;
                    continue;
                }
                int k = p.second;
                if (c == a[v]) {
                    if (inans[k]) {
                        inans[k] = false;
                        -- ans;
                    }
                } else {
                    if (!inans[k]) {
                        inans[k] = true;
                        ++ ans;
                    }
                }
            }
        }
        a[u] = c;
        printf("%d\n", ans);
    }
    return 0;
}
/*
4 5
1 2 3 4
1 2
2 3
3 4
4 1
1 3
5
1 5
3 2
4 4
1 4
2 3
*/

