#include <bits/stdc++.h>

const int MAXN = 200010;

int n;
int l[MAXN], r[MAXN];
std::vector<std::pair<int, int>> right[MAXN];
int ans[MAXN];

struct Tree {
    int min[MAXN << 2], min_pos[MAXN << 2], lazy[MAXN << 2];

    void merge(int u) {
        int ls = u << 1, rs = ls | 1;
        min[u] = min[ls];
        min_pos[u] = min_pos[ls];
        if (min[u] > min[rs]) {
            min[u] = min[rs];
            min_pos[u] = min_pos[rs];
        }
    }

    void pushdown(int u) {
        if (!lazy[u]) return;
        int ls = u << 1, rs = ls | 1;
        min[ls] += lazy[u];
        min[rs] += lazy[u];
        lazy[ls] += lazy[u];
        lazy[rs] += lazy[u];
        lazy[u] = 0;
    }

    void build(int u, int l, int r, std::vector<int> &v) {
        if (l == r) {
            min[u] = v[l];
            min_pos[u] = l;
            lazy[u] = 0;
            return;
        }
        int m = (l + r) >> 1, ls = u << 1, rs = ls | 1;
        build(ls, l, m, v);
        build(rs, m + 1, r, v);
        merge(u);
    }

    void modify(int u, int l, int r, int ql, int qr, int v, bool set=false) {
        if (ql > qr || qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            if (set) {
                min[u] = v;
                return;
            }
            min[u] += v;
            lazy[u] += v;
            return;
        }
        pushdown(u);
        int m = (l + r) >> 1, ls = u << 1, rs = ls | 1;
        modify(ls, l, m, ql, qr, v, set);
        modify(rs, m + 1, r, ql, qr, v, set);
        merge(u);
    }

    void set(int u, int l, int r, int pos, int v) {
        modify(u, l, r, pos, pos, v, true);
    }

    int query(int u, int l, int r, int ql, int qr) {
        if (ql > qr || qr < l || r < ql) return -1;
        if (ql <= l && r <= qr) {
            return u;
        }
        pushdown(u);
        int m = (l + r) >> 1, ls = u << 1, rs = ls | 1;
        int a = query(ls, l, m, ql, qr);
        int b = query(rs, m + 1, r, ql, qr);
        if (a == -1) return b;
        if (b == -1) return a;
        return min[a] > min[b] ? b : a;
    }

    int find(int u, int l, int r, int v) {
        if (l == r) return l;
        pushdown(u);
        int m = (l + r) >> 1, ls = u << 1, rs = ls | 1;
        if (min[ls] <= v) return find(ls, l, m, v);
        return find(rs, m + 1, r, v);
    }

} hall, right_position;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", l + i, r + i);
        right[l[i]].emplace_back(r[i], i);
    }

    // check if no solution
    std::multiset<int> multiset;
    for (int i = 1; i <= n; ++i) {
        for (auto &p : right[i]) {
            multiset.insert(p.first);
        }
        if (multiset.empty() || *multiset.begin() < i) {
            puts("-1");
            return 0;
        }
        multiset.erase(multiset.begin());
    }

    // set up trees
    std::vector<int> vec(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (auto &p : right[i]) {
            ++vec[p.first];
        }
    }
    for (int i = 1; i <= n; ++i) {
        vec[i] += vec[i - 1];
    }
    for (int i = 1; i <= n; ++i) {
        vec[i] = i - vec[i];
    }
    hall.build(1, 1, n, vec);

    for (int i = 1; i <= n; ++i) {
        vec[i] = n + 1;
    }
    right_position.build(1, 1, n, vec);

    for (int i = 1; i <= n; ++i) {
        for (auto &p : right[i]) {
            right_position.set(1, 1, n, p.second, p.first);
        }
        int u = hall.query(1, 1, n, i, n);
        int right_bound = n;
        if (hall.min[u] == 0) {
            right_bound = hall.min_pos[u];
        }
        // find r <= u, and sub [i + 1, r) by -1

        int v = right_position.find(1, 1, n, right_bound);
        ans[i] = v;

        hall.modify(1, 1, n, i + 1, r[v] - 1, -1);
        right_position.set(1, 1, n, v, n + 1);
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }

    return 0;
}
/*
5
 2 5
 1 5
 3 5
 4 5
 1 5

 6
 2 4
 1 3
 4 6
 4 6
 4 6
 3 5
 */