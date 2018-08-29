#include <bits/stdc++.h>

struct P {
    int x, y;

    explicit P(int x = 0, int y = 0) : x(x), y(y) {}

    P sub(const P &p) const { return P(x - p.x, y - p.y); }
    int det(const P &p) const { return x * p.y - y * p.x; }
}p[20];
int n, ans;
int match[20];

void check() {
    std::vector<P> vec;
    for (int i = 1; i <= n; ++i) {
        if (i < match[i]) {
            vec.push_back(p[match[i]].sub(p[i]));
        }
    }
    int m = (int) vec.size();
    int tmp = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (vec[i].det(vec[j]) == 0) ++tmp;
        }
    }
    ans = std::max(ans, tmp);
}

void dfs(int u, int depth) {
    for (int i = 1; i <= n; ++i) {
        if (!match[i] && i != u) {
            match[u] = i;
            match[i] = u;
            if (depth == n) {
                check();
            }
            for (int j = 1; j <= n; ++j) {
                if (!match[j]) {
                    dfs(j, depth + 2);
                    break;
                }
            }
            match[u] = match[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    dfs(1, 2);
    printf("%d\n", ans);
    return 0;
}

