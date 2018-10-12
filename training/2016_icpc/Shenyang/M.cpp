#include <bits/stdc++.h>

using LL = long long;
using edge = std::pair<int, int>;

const int max_N = (int) 3e5 + 21;
const int log_N = 20;

int T, n, k, s, t, a[max_N], c[max_N], dis[max_N], p[max_N], Q[max_N], tot;

std::vector<edge> vec[max_N]; // reversed edge
std::vector<edge> _vec[max_N];

void bfs() {
    memset(dis + 1, -1, t * sizeof(int));
    memset(p + 1, 0, t * sizeof(int));
    Q[tot = 1] = t;
    dis[t] = 0;
    for (int i = 1; i <= tot; ++i) {
        int u = Q[i];
        for (auto &e : vec[u]) {
            int v = e.first, w = dis[u] + e.second;
            if (dis[v] == -1) {
                Q[++tot] = v;
            }
            if (dis[v] < w) {
                dis[v] = w;
                p[v] = u;
            }
        }
    }
}

#define ht(x) ((x) ? (x)->h : 0)

using ptr = struct node *;

struct node {
    ptr ls, rs;
    int u, v, h;
} pool[max_N * log_N];

ptr tail = pool, rt[max_N];

inline ptr new_node(int u, int v) {
    ptr x = tail++;
    x->u = u;
    x->v = v;
    x->h = 1;
    x->ls = x->rs = nullptr;
    return x;
}

ptr merge(ptr u, ptr v) {
    if (!u) return v;
    if (!v) return u;
    if (u->v > v->v) {
        std::swap(u, v);
    }
    ptr x = tail++;
    *x = *u;
    x->rs = merge(u->rs, v);
    if (ht(x->ls) < ht(x->rs)) {
        std::swap(x->ls, x->rs);
    }
    x->h = ht(x->rs) + 1;
    return x;
}

using state = std::pair<int, ptr>;

std::priority_queue<state, std::vector<state>, std::less<state>> pq;

#define slt(x) ((x) + n + n)
#define unslt_0(x) (x)
#define unslt_1(x) ((x) + n)

void testCase() {
    scanf("%d%d", &n, &k);
    assert(n <= 100000);
    s = n + n + n + 1, t = s + 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", a + i, a + n + i, c + i);
        if (i == 1) {
            vec[slt(i)].emplace_back(s, a[i]);
            vec[unslt_0(i)].emplace_back(s, 0);
        } else {
            vec[slt(i)].emplace_back(unslt_0(i - 1), a[i]);
            vec[slt(i)].emplace_back(unslt_1(i - 1), a[i + n]);

            if (c[i - 1]) {
                vec[slt(i)].emplace_back(slt(i - 1), a[i + n]);
                vec[unslt_1(i)].emplace_back(slt(i - 1), 0);
            } else {
                vec[slt(i)].emplace_back(slt(i - 1), a[i]);
                vec[unslt_0(i)].emplace_back(slt(i - 1), 0);
            }

            vec[unslt_0(i)].emplace_back(unslt_0(i - 1), 0);
            vec[unslt_1(i)].emplace_back(unslt_1(i - 1), 0);
        }
    }

    vec[t].emplace_back(slt(n), 0);
    vec[t].emplace_back(unslt_0(n), 0);
    vec[t].emplace_back(unslt_1(n), 0);

    bfs(); // calc longest path

    if (k == 1) {
        printf("%d\n", dis[s]);
        return;
    }

    for (int u = 1; u <= t; ++u)
        for (auto &e : vec[u]) {
            int v = e.first, w = e.second;
            _vec[v].emplace_back(u, w);
            // printf("(%d, %d) -> %d\n", v, u, w);
        }

    for (int i = 2; i <= tot; ++i) {
        int u = Q[i];
        rt[u] = rt[p[u]];
        for (auto &e : _vec[u]) {
            int v = e.first, w = e.second;
            if (dis[v] == -1 || p[u] == v) continue;
            // printf("%d -> %d : %d\n", u, v, dis[u] - dis[v] - w);
            ptr x = new_node(v, dis[u] - dis[v] - w);
            rt[u] = merge(rt[u], x);
        }
    }

    if (rt[s]) pq.emplace(dis[s] - rt[s]->v, rt[s]);

    while (k--) {
        auto x = pq.top();
        pq.pop();
        if (k == 1) {
            printf("%d\n", x.first);
            break;
        }
        int u = x.second->u;
        ptr cur = x.second, ls = cur->ls, rs = cur->rs;
        if (rt[u]) pq.emplace(x.first - rt[u]->v, rt[u]);
        if (ls) pq.emplace(x.first + cur->v - ls->v, ls);
        if (rs) pq.emplace(x.first + cur->v - rs->v, rs);
    }
}

void clr() {
    while (!pq.empty()) pq.pop();
    tail = pool;
    for (int i = 1; i <= t; ++i) {
        rt[i] = nullptr;
        std::vector<edge>().swap(vec[i]);
        std::vector<edge>().swap(_vec[i]);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
        clr();
    }
    return 0;
}

