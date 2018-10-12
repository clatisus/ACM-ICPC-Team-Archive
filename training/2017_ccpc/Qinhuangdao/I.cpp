#include <bits/stdc++.h>

using LL = long long;

const int max_N = 18;
const int max_S = 1 << max_N;

const double eps = 1e-9;
const double PI = acos(-1.0);

inline int dcmp(double p) { return (p > eps) - (p < -eps); }

struct P {
    double x, y;

    explicit P(double x = 0, double y = 0) : x(x), y(y) {}

    P sub(const P &p) const { return P(x - p.x, y - p.y); }

    double det(const P &p) const { return x * p.y - y * p.x; }

    P rot(const double &rad) const {
        double sin = std::sin(rad), cos = std::cos(rad);
        return P(x * cos - y * sin, x * sin + y * cos);
    }

    bool operator<(const P &p) const { return dcmp(x - p.x) ? x < p.x : dcmp(y - p.y) < 0; }

    bool operator==(const P &p) const { return !dcmp(x - p.x) && !dcmp(y - p.y); }
} p[max_N];

int T, n, a[max_N][max_N];

void my_shuffle() {
    static std::random_device rd;
    static std::mt19937 gen = std::mt19937(rd());
    static std::uniform_real_distribution<> dis(-1, 1);
    static auto my_rand = std::bind(dis, gen);

    while (true) {
        double angle = PI * my_rand();
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            p[i] = p[i].rot(angle);
        }
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (!dcmp(p[i].x - p[j].x)) {
                    flag = false;
                    break;
                }
        if (flag) break;
    }
}

bool ok[max_N][max_N][max_N];

int val[max_S][max_N + 1], Q[max_N], rk[max_N], st[max_N << 1];

LL count[max_S][max_N + 1];

bool vis[max_S][max_N];

std::vector<int> bit[max_S];

double onLeft(P p1, P p2, P q) {
    return p2.sub(p1).det(q.sub(p1));
}

inline bool inside(P p1, P p2, P p3, P q) {
    if (dcmp(onLeft(p1, p3, p2)) > 0) {
        std::swap(p2, p3);
    }
    if (dcmp(onLeft(p1, p2, q)) < 0) return false;
    if (dcmp(onLeft(p2, p3, q)) < 0) return false;
    if (dcmp(onLeft(p3, p1, q)) < 0) return false;
    return true;
}

void init() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            scanf("%d", a[i] + j);
        }

    my_shuffle();

    for (int i = 0; i < n; ++i) {
        Q[i] = i;
    }
    std::sort(Q, Q + n, [&](int u, int v) { return p[u] < p[v]; });
    for (int i = 0; i < n; ++i) {
        rk[Q[i]] = i;
    }

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k) {
                ok[i][j][k] = true;
                for (int x = 0; x < n; ++x) {
                    if (x == i || x == j || x == k) continue;
                    if (inside(p[Q[i]], p[Q[j]], p[Q[k]], p[Q[x]])) {
                        ok[i][j][k] = false;
                        break;
                    }
                }
                if (ok[i][j][k]) {
                    // printf("ok (%d, %d, %d)\n", Q[i], Q[j], Q[k]);
                }
            }
}

inline void updt(int &val, LL &count, int v, LL c) {
    if (val < v) return;
    if (val > v) {
        val = v;
        count = c;
    } else {
        count += c;
    }
}

void dfs(int s, int u) {
    int sz = (int) bit[s].size();
    if (u == sz - 1 || vis[s][u]) return;
    vis[s][u] = true;

    dfs(s, u + 1);
    auto &V = val[s][u] = val[s][u + 1];
    auto &C = count[s][u] = count[s][u + 1];

    if (u && u + 1 < sz) {
        int l = bit[s][u - 1], m = bit[s][u], r = bit[s][u + 1];
        if (ok[l][m][r] && dcmp(onLeft(p[Q[l]], p[Q[r]], p[Q[m]])) > 0) {
            int ns = s ^ (1 << m);
            dfs(ns, u - 1);
            updt(V, C, val[ns][u - 1] + a[Q[l]][Q[m]] + a[Q[m]][Q[r]], count[ns][u - 1]);
        }
    }

    if (u + 1 < sz) {
        int l = bit[s][u], r = bit[s][u + 1];
        for (int m = l + 1; m < r; ++m) {
            if (!ok[l][m][r]) continue;
            if (dcmp(onLeft(p[Q[l]], p[Q[r]], p[Q[m]])) > 0) continue;
            int ns = s | (1 << m);
            dfs(ns, u);
            updt(V, C, val[ns][u] + a[Q[l]][Q[r]], count[ns][u]);
        }
    }

    // printf("val[%d][%d] = %d\n", s, u, V);
}

void testCase() {
    init();

    int top = 0, start = 0, end = 0, sum = 0;

    for (int i = 0; i < n; ++i) {
        while (top > 1 && dcmp(onLeft(p[st[top - 1]], p[st[top]], p[Q[i]])) <= 0) --top;
        st[++top] = Q[i];
    }

    for (int i = 1; i <= top; ++i) {
        start |= 1 << rk[st[i]];
        // printf("start %d\n", st[i]);
        if (i < top) {
            sum += a[st[i]][st[i + 1]];
        }
    }

    int tmp = top;
    for (int i = n - 2; ~i; --i) {
        while (top > tmp && dcmp(onLeft(p[st[top - 1]], p[st[top]], p[Q[i]])) <= 0) --top;
        st[++top] = Q[i];
    }
    for (int i = tmp; i <= top; ++i) {
        // printf("end %d\n", st[i]);
        end |= 1 << rk[st[i]];
    }

    for (int s = 0; s < (1 << n); ++s) {
        for (int i = 0; i <= (int) bit[s].size(); ++i) {
            val[s][i] = 0x3f3f3f3f;
            count[s][i] = 0;
            vis[s][i] = false;
        }
    }

    val[start][tmp - 1] = sum;
    count[start][tmp - 1] = 1;
    vis[start][tmp - 1] = true;

    // printf("start = %d\n", start);

    dfs(end, 0);
    printf("%d %lld\n", val[end][0], count[end][0]);
}

int main() {
    for (int s = 0; s < max_S; ++s)
        for (int i = 0; i < max_N; ++i) {
            if ((s >> i) & 1) {
                bit[s].push_back(i);
            }
        }
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}

