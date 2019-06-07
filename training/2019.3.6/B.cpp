#include<bits/stdc++.h>

const int N = 200010;
const int BIT = 19;
const int MAX = 1 << 18;
const int moder = 998244353;
typedef long long ll;
typedef std::pair<ll, ll> pii;
const ll INF = 3e18;

struct Edge {
    int v, c, d;
};

struct Event {
    int id;
    bool in;
};

std::vector<Edge> e[N];
int dep[N], fa[N][BIT];
ll cost[N][BIT];
std::vector<Event> event[N];

void dfs(int u, int fa, int t, int c) {
    ::fa[u][0] = fa;
    cost[u][0] = c;
    for (int i = 1; i < BIT; ++i) {
        ::fa[u][i] = ::fa[::fa[u][i - 1]][i - 1];
        cost[u][i] = cost[u][i - 1] + cost[::fa[u][i - 1]][i - 1];
    }
    for (auto tmp : e[u]) {
        int v = tmp.v;
        if (v == fa) {
            continue;
        }
        dep[v] = dep[u] + 1;
        dfs(v, u, t, tmp.c);
    }
}

pii lca(int u, int v) {
    if (dep[u] < dep[v]) {
        std::swap(u, v);
    }
    ll ret = 0;
    for (int i = 0, diff = dep[u] - dep[v]; i < BIT; ++i) {
        if (diff >> i & 1) {
            ret += cost[u][i];
            u = fa[u][i];
        }
    }
    if (u == v) {
        return {u, ret};
    }
    for (int i = BIT - 1; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            ret += cost[u][i] + cost[v][i];
            u = fa[u][i], v = fa[v][i];
        }
    }
    return {fa[u][0], ret + cost[u][0] + cost[v][0]};
}

struct Seg {
    ll seg[MAX << 1];
    ll offset;

    void add(int sit, ll value) {
        seg[sit += MAX] = value - offset;
        for (sit >>= 1; sit; sit >>= 1) {
            seg[sit] = std::max(seg[sit << 1], seg[sit << 1 | 1]);
        }
    }

    int query(int sit, int l, int r, int ql, int qr, ll value) {
        if (ql > r || qr < l) {
            return -1;
        }
        if (seg[sit] < value) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        int ret = query(sit << 1, l, mid, ql, qr, value);
        if (ret != -1) {
            return ret;
        }
        return query(sit << 1 | 1, mid + 1, r, ql, qr, value);
    }

    int query(int ql, int qr, ll value) {
        return query(1, 0, MAX - 1, ql, qr, value - offset);
    }
};

Seg seg[4];

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; ++i) {
        e[i].clear();
        event[i].clear();
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v, c, d;
        scanf("%d%d%d%d", &u, &v, &c, &d);
        e[u].push_back({v, c, d});
        e[v].push_back({u, c, d});
    }
    std::vector<int> a(k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &a[i]);
    }
    a.push_back(a[0]);
    int s, t;
    scanf("%d%d", &s, &t);
    dep[s] = 0;
    dfs(s, 0, t, 0);
    std::vector<int> id(n + 1), points;
    while (t) {
        points.push_back(t);
        t = fa[t][0];
    }
    std::reverse(points.begin(), points.end());
    t = points.back();
    int sz = points.size();
    for (int i = 0; i < sz; ++i) {
        id[points[i]] = i;
    }
    std::vector<ll> prec(n), disd(n);
    for (int i = 0; i < sz - 1; ++i) {
        for (auto u : e[points[i]]) {
            if (u.v == points[i + 1]) {
                prec[i + 1] = prec[i] + u.c;
                disd[i] = u.d;
            }
        }
    }
    ll tot = 0;
    std::vector<ll> begintime;
    std::vector<bool> type;
    int zzh = 0;
    for (int i = 0; i < k; ++i) {
        int u = a[i], v = a[i + 1];
        int l1 = lca(u, t).first, l2 = lca(v, t).first;
        if (l1 != l2) {
            if (id[l1] > id[l2]) {
                begintime.push_back(tot + lca(u, l1).second + prec[id[l1]]);
                std::swap(l1, l2);
                std::swap(u, v);
                type.push_back(true);
            } else {
                begintime.push_back(tot + lca(u, l1).second - prec[id[l1]]);
                type.push_back(false);
            }
            event[id[l1]].push_back({zzh, true});
            event[id[l2] - 1].push_back({zzh, false});
            ++zzh;
        }
        tot += lca(a[i], a[i + 1]).second;
    }
    auto getbegin = [&](int id, int i) {
        if (type[id]) {
            return begintime[id] - prec[i + 1];
        }
        return begintime[id] + prec[i];
    };
    auto getend = [&](int id, int i) {
        if (type[id]) {
            return begintime[id] - prec[i];
        }
        return begintime[id] + prec[i + 1];
    };
    int ans = 0;
    ll ans2 = 0;
    std::set<int> set;
    for (int i = 0; i < 4; ++i) {
        seg[i].offset = 0;
        for (int j = 0; j < k; ++j) {
            seg[i].add(j, -INF);
        }
    }
    for (int i = 0; i < sz - 1; ++i) {
        for (auto u : event[i]) {
            if (!u.in) {
                continue;
            }
            auto v = set.insert(u.id).first;
            auto w = v;
            ++w;
            if (w == set.end()) {
                w = set.begin();
            }
            ll diff = getbegin(*w, i) - getend(*v, i);
            diff += diff < 0 ? tot : 0;
            seg[type[*v] << 1 | type[*w]].add(*v, diff);
            auto _w = v;
            if (_w == set.begin()) {
                _w = set.end();
            }
            --_w;
            seg[type[*_w] << 1 | type[*w]].add(*_w, -INF);
            diff = getbegin(*v, i) - getend(*_w, i);
            diff += diff < 0 ? tot : 0;
            seg[type[*_w] << 1 | type[*v]].add(*_w, diff);
        }
        if (set.empty()) {
            ans2 += disd[i];
            ans = (ans + ans2 / tot * tot) % moder;
            ans2 %= tot;
        } else {
            int left = 0, right = zzh;
            while (left < right) {
                int mid = (left + right) >> 1;
                if (ans2 <= getbegin(mid, i)) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            if (set.lower_bound(left) == set.end()) {
                ans2 = std::max(ans2, getend(*(--set.end()), i));
                if (ans2 + disd[i] <= getbegin(*set.begin(), i) + tot) {
                    ans2 += disd[i];
                    ans = (ans + ans2 / tot * tot) % moder;
                    ans2 %= tot;
                } else {
                    int ret = -1;
                    for (int j = 0; j < 4; ++j) {
                        int tmp = seg[j].query(0, zzh - 1, disd[i]);
                        if (ret == -1 || (tmp != -1 && ret > tmp)) {
                            ret = tmp;
                        }
                    }
                    if (ret == -1) {
                        puts("-1");
                        return;
                    }
                    ans2 = getend(ret, i) + disd[i] + tot;
                    ans = (ans + ans2 / tot * tot) % moder;
                    ans2 %= tot;
                }
            } else {
                auto w = set.lower_bound(left);
                if (w != set.begin()) {
                    --w;
                    ans2 = std::max(ans2, getend(*w, i));
                    ++w;
                }
                int x = *w;
                if (ans2 + disd[i] <= getbegin(x, i)) {
                    ans2 += disd[i];
                    ans = (ans + ans2 / tot * tot) % moder;
                    ans2 %= tot;
                } else {
                    int ret = -1;
                    for (int j = 0; j < 4; ++j) {
                        int tmp = seg[j].query(x, (int) zzh - 1, disd[i]);
                        if (ret == -1 || (tmp != -1 && ret > tmp)) {
                            ret = tmp;
                        }
                    }
                    if (ret == -1) {
                        for (int j = 0; j < 4; ++j) {
                            int tmp = seg[j].query(0, x - 1, disd[i]);
                            if (ret == -1 || (tmp != -1 && ret > tmp)) {
                                ret = tmp;
                            }
                        }
                        if (ret == -1) {
                            puts("-1");
                            return;
                        }
                        ans2 = getend(ret, i) + disd[i] + tot;
                        ans = (ans + ans2 / tot * tot) % moder;
                        ans2 %= tot;
                    } else {
                        ans2 = getend(ret, i) + disd[i];
                        ans = (ans + ans2 / tot * tot) % moder;
                        ans2 %= tot;
                    }
                }
            }
        }
        for (auto u : event[i]) {
            if (u.in) {
                continue;
            }
            auto v = set.erase(set.find(u.id));
            if (set.empty()) {
                seg[type[u.id] << 1 | type[u.id]].add(u.id, -INF);
                continue;
            }
            if (v == set.end()) {
                v = set.begin();
            }
            seg[type[u.id] << 1 | type[*v]].add(u.id, -INF);
            if (v == set.begin()) {
                v = set.end();
            }
            --v;
            seg[type[*v] << 1 | type[u.id]].add(*v, -INF);
            auto w = v;
            ++w;
            if (w == set.end()) {
                w = set.begin();
            }
            ll diff = getbegin(*w, i) - getend(*v, i);
            diff += diff < 0 ? tot : 0;
            seg[type[*v] << 1 | type[*w]].add(*v, diff);
        }
        ll begin0 = prec[i + 1] - prec[i], end0 = prec[i + 2] - prec[i + 1];
        ll begin1 = -end0, end1 = -begin0;
        seg[0].offset += begin0 - end0;
        seg[1].offset += begin1 - end0;
        seg[2].offset += begin0 - end1;
        seg[3].offset += begin1 - end1;
    }
    ans = (ans + ans2) % moder;
    printf("%d\n", ans);
}

int main() {
    int test;
    scanf("%d", &test);
    while (test--) {
        solve();
    }
    return 0;
}
