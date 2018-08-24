#include <bits/stdc++.h>

#define MAXN (2010)

const double eps = 1e-6;

inline int dcmp(double p) { return (p > eps) - (p < -eps); }

int n;
struct P {
    int x, y;
    explicit P(int x = 0, int y = 0) : x(x), y(y) {}

    P sub(const P &p) const { return P(x - p.x, y - p.y); }

    int det(const P &p) const { return x * p.y - y * p.x; }

    int abs2() const { return x * x + y * y; }

    int sign() const {
        return y ? y < 0 : x < 0;
    }

    bool operator < (const P &p) const {
        return x == p.x ? y < p.y : x < p.x;
    }

    bool operator == (const P &p) const {
        return x == p.x && y == p.y;
    }

}seg[MAXN][2];

int id[MAXN][2], f[MAXN];
std::vector<P> ps;
std::vector<std::pair<int, std::pair<int, int>>> edge;
std::vector<int> add[MAXN], del[MAXN];

int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }

P p;
P v;
double len;

double getdis(int x) {
    P u = p.sub(seg[x][0]), w = seg[x][1].sub(seg[x][0]);
    return len * w.det(u) / v.det(w);
};

struct segment {
    bool operator () (const int &x, const int &y) {
        double dx = getdis(x);
        double dy = getdis(y);
        if (dcmp(dx - dy)) return dcmp(dx - dy) < 0;
        return x < y;
    }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            scanf("%d%d", &seg[i][j].x, &seg[i][j].y);
            ps.push_back(seg[i][j]);
        }
    }
    std::sort(ps.begin(), ps.end());
    ps.erase(std::unique(ps.begin(), ps.end()), ps.end());
    for (int i = 1; i <= n; ++i) {
        id[i][0] = std::lower_bound(ps.begin(), ps.end(), seg[i][0]) - ps.begin();
        id[i][1] = std::lower_bound(ps.begin(), ps.end(), seg[i][1]) - ps.begin();
        edge.push_back({0, {id[i][0], id[i][1]}});

    }

    int m = ps.size();
    for (int i = 0; i < m; ++i) {
        std::vector<std::pair<P, int>> vec;
        for (int j = 0; j < m; ++j) if (i != j) {
            vec.push_back({ps[j].sub(ps[i]), j});
        }
        std::sort(vec.begin(), vec.end(), [&](const std::pair<P, int> &A, const std::pair<P, int> &B) {
            const P &a = A.first;
            const P &b = B.first;
            return a.sign() == b.sign() ? a.det(b) > 0 : a.sign() < b.sign();
        });

        p = ps[i];
        v = P(1, 0);
        len = 1.0;
        std::set<int, segment> set;

        for (int j = 0; j < m; ++j) {
            std::vector<int>().swap(add[j]);
            std::vector<int>().swap(del[j]);
        }
        for (int j = 1; j <= n; ++j) {
            int &x = id[j][0], &y = id[j][1];
            if (x == i || y == i) continue;
            if (ps[x].sub(p).det(ps[y].sub(p)) < 0) {
                std::swap(x, y);
                std::swap(seg[j][0], seg[j][1]);
            }
            if (ps[y].y >= p.y && ps[x].y < p.y) {
                set.insert(j);
            }
            add[x].push_back(j);
            del[y].push_back(j);
        }

        for (auto u : vec) {
            v = u.first;
            len = std::sqrt(v.abs2());
            int x = u.second;

            for (auto k : del[x]) set.erase(k);

            bool flag = false;
            if (!set.empty()) {
                auto k = *set.begin();
                if (seg[k][1].sub(seg[k][0]).det(ps[x].sub(seg[k][0])) > 0) {
                    flag = true;
                }
            } else {
                flag = true;
            }
            if (flag) {
                edge.push_back({v.abs2(), {i, x}});
            }

            for (auto k : add[x]) set.insert(k);
        }
    }

    double ans = 0;
    std::sort(edge.begin(), edge.end());
    for (int i = 0; i < m; ++i) f[i] = i;
    for (auto e : edge) {
        int w = e.first;
        int u = e.second.first;
        int v = e.second.second;
        u = find(u);
        v = find(v);
        if (u == v) continue;
        f[u] = v;
        ans += std::sqrt(w);
    }
    printf("%.10f\n", ans);
    return 0;
}
