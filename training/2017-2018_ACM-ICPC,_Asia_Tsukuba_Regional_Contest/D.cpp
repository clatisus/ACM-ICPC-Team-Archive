#include <bits/stdc++.h>

#define ALL(x) (x).begin(), (x).end()

using LL = long long;

const int max_N = (int) 1e5 + 21;

struct P {
    int x, y;

    explicit P(int x = 0, int y = 0) : x(x), y(y) {}

    inline P add(const P &p) const { return P(x + p.x, y + p.y); }

    inline P sub(const P &p) const { return P(x - p.x, y - p.y); }

    inline LL dot(const P &p) const { return 1ll * x * p.x + 1ll * y * p.y; }

    inline LL det(const P &p) const { return 1ll * x * p.y - 1ll * y * p.x; }

    inline LL abs2() { return dot(*this); }

    inline double abs() { return std::sqrt(abs2()); }

    bool operator<(const P &p) const { return x != p.x ? x < p.x : y < p.y; }

    bool operator==(const P &p) const { return x == p.x && y == p.y; }
} p[max_N], o;

bool origin[max_N], added[max_N];

int n, st[max_N], top, Q[max_N], tot;

double ans;

std::vector<int> vec[3];

void initConvex() {
    std::sort(p + 1, p + 1 + n);
    top = 0;
    auto check = [&](int i) -> bool {
        return p[i].sub(p[st[top - 1]]).det(p[st[top]].sub(p[st[top - 1]])) >= 0;
    };
    for (int i = 1; i <= n; ++i) {
        while (top > 1 && check(i)) --top;
        st[++top] = i;
    }
    o = p[st[1]].add(p[st[top]]);
    o.x >>= 1, o.y >>= 1;
    for (int i = n - 1, tmp = top; i; --i) {
        while (top > tmp && check(i)) --top;
        st[++top] = i;
    }
    if (top > 1) --top;
    for (int i = 1; i <= top; ++i) origin[st[i]] = true;
}

std::priority_queue<std::pair<double, int>> pq;

void solve(int id, double delta, std::vector<int> &v, bool tp) {
    static int st[2][max_N], Q[max_N];
    int top = 0;
    auto check = [&](int i) -> bool {
        return p[i].sub(p[st[tp][top - 1]]).det(p[st[tp][top]].sub(p[st[tp][top - 1]])) >= 0;
    };
    for (auto i : v) {
        while (top > 1 && check(i)) --top;
        st[tp][++top] = i;
    }
    for (int i = 1; i < top; ++i) {
        delta += p[st[tp][i]].sub(p[st[tp][i + 1]]).abs();
    }
    ans = std::max(ans, -delta);
    if (tp) {
        pq.push({delta, id});
        // printf("%.10f\n", delta);
        if (pq.size() > 4) pq.pop();
        for (int i = 1; i <= top; ++i) added[st[tp][i]] = true;
        int tot = 0;
        for (auto i = 0; i < v.size(); ++i) {
            int x = v[i];
            if (added[x]) {
                Q[++tot] = i;
                // printf("added(%d, %d)\n", p[x].x, p[x].y);
            }
        }
        for (int i = 2; i < tot; ++i) {
            std::vector<int> vv;
            for (int j = Q[i - 1]; j <= Q[i + 1]; ++j) {
                if (j == Q[i]) continue;
                vv.push_back(v[j]);
            }
            double delta1 = delta;
            delta1 -= p[v[Q[i]]].sub(p[v[Q[i - 1]]]).abs();
            delta1 -= p[v[Q[i]]].sub(p[v[Q[i + 1]]]).abs();
            solve(0, delta1, vv, false);
        }
        for (int i = 1; i <= top; ++i) added[st[tp][i]] = false;
    }
}

void pickUp(int id, std::vector<int> &v) {
    if (id == tot) {
        for (auto i = Q[tot] + 1; i < vec[2].size(); ++i) {
            v.push_back(vec[2][i]);
        }
        for (int i = 1; i < Q[1]; ++i) {
            v.push_back(vec[2][i]);
        }
    } else {
        for (int i = Q[id] + 1; i < Q[id + 1]; ++i) {
            v.push_back(vec[2][i]);
        }
    }
}

bool adjacent(int i, int j) {
    if (i == j) return true;
    if (i > j) std::swap(i, j);
    return i + 1 == j || (i == 1 && j == tot);
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        P v = p[i].sub(o);
        int d = v.y > 0 || (!v.y && v.x > 0);
        vec[d].push_back(i);
    }
    for (int d = 0; d < 2; ++d) {
        std::sort(ALL(vec[d]), [&](int x, int y) {
            return p[x].sub(o).det(p[y].sub(o)) > 0;
        });
        for (auto x : vec[d]) vec[2].push_back(x);
    }
    for (auto i = 0; i < vec[2].size(); ++i) {
        int x = vec[2][i];
        if (origin[x]) Q[++tot] = i;
        // printf("sort(%d, %d)\n", p[x].x, p[x].y);
    }
    for (int i = 1; i <= tot; ++i) {
        int prev = i == 1 ? tot : i - 1;
        int next = i == tot ? 1 : i + 1;
        std::vector<int> v;
        v.push_back(vec[2][Q[prev]]);
        pickUp(prev, v), pickUp(i, v);
        v.push_back(vec[2][Q[next]]);
        double delta = 0;
        delta -= p[vec[2][Q[i]]].sub(p[vec[2][Q[prev]]]).abs();
        delta -= p[vec[2][Q[i]]].sub(p[vec[2][Q[next]]]).abs();
        // printf("delta(%d, %d) = ", p[vec[2][Q[i]]].x, p[vec[2][Q[i]]].y);
        solve(i, delta, v, true);
    }
    
    std::vector<std::pair<double, int>> best4;
    while (!pq.empty()) {
        best4.push_back(pq.top());
        pq.pop();
    }
    for (auto a : best4)
        for (auto b : best4) {
            if (adjacent(a.second, b.second)) continue;
            // printf("nonadjacent(%d, %d) = %.10f, %.10f\n", a.second, b.second, a.first, b.first);
            ans = std::max(ans, -(a.first + b.first));
        }
    
    for (int i = 1; i <= tot; ++i) {
        int prev = i == 1 ? tot : i - 1;
        int next = i == tot ? 1 : i + 1;
        int nnext = next == tot ? 1 : next + 1;
        std::vector<int> v;
        v.push_back(vec[2][Q[prev]]);
        pickUp(prev, v), pickUp(i, v), pickUp(next, v);
        v.push_back(vec[2][Q[nnext]]);
        double delta = 0;
        delta -= p[vec[2][Q[i]]].sub(p[vec[2][Q[prev]]]).abs();
        delta -= p[vec[2][Q[i]]].sub(p[vec[2][Q[next]]]).abs();
        delta -= p[vec[2][Q[nnext]]].sub(p[vec[2][Q[next]]]).abs();
        solve(0, delta, v, false);
    }
}


int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    initConvex();
    solve();
    printf("%.10f\n", ans);
    return 0;
}
