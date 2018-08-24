#include <bits/stdc++.h>

const int max_N = 10000 + 21;

namespace maxFlow {
    using flowType = int;
    const flowType inf = 0x3f3f3f3f;

    struct edge {
        int v, n;
        flowType c;
    };

    std::vector<edge> e;
    int M, head[max_N], cur[max_N], dis[max_N];

    bool bfs(int n, int s, int t) {
        static int Q[max_N];
        int tail = 0;
        memset(dis + 1, -1, n * sizeof(int));
        dis[s] = 0, Q[tail++] = s;
        for (int i = 0; i < tail; ++i) {
            int u = Q[i];
            for (int it = head[u]; ~it; it = e[it].n) {
                if (!e[it].c) continue;
                int v = e[it].v;
                if (dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    Q[tail++] = v;
                }
            }
        }
        return dis[t] != -1;
    }

    flowType dfs(int t, int u, flowType a) {
        if (u == t) return a;
        flowType ret = 0, tmp;
        for (int &it = cur[u]; ~it; it = e[it].n) {
            int v = e[it].v;
            if (!e[it].c || dis[u] + 1 != dis[v]) continue;
            tmp = dfs(t, v, std::min(a - ret, e[it].c));
            if (tmp) {
                e[it].c -= tmp, e[it ^ 1].c += tmp;
                if ((ret += tmp) == a) break;
            }
        }
        if (!ret) dis[u] = -1;
        return ret;
    }

    void init(int n) {
        e.clear();
        memset(head + 1, -1, n * sizeof(int));
        M = 0;
    }

    void addEdge(int u, int v, flowType c) {
        e.push_back({v, head[u], c});
        head[u] = M++;
    }

    flowType dinic(int n, int s, int t) {
        flowType ret = 0;
        while (bfs(n, s, t)) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            ret += dfs(t, s, inf);
        }
        return ret;
    }
};

int n, m;

int u[max_N], v[max_N], f[max_N];

std::vector<int> vec_p[max_N], vec_e[max_N];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void merge(int u, int v) {
    f[find(u)] = find(v);
}

int p[max_N], e[max_N], p_tot, e_tot, id[max_N], tmp[max_N];

int tree_u[max_N], tree_v[max_N], tree_w[max_N], tree_tot, tree_q[max_N];

void solve(int l, int r) {
    if (l == r) return;
    std::random_shuffle(p + l, p + r + 1);
    maxFlow::init(p_tot + 2);
    int s = p_tot + 1, t = p_tot + 2;
    maxFlow::addEdge(s, id[p[l]], maxFlow::inf);
    maxFlow::addEdge(id[p[l]], s, 0);
    maxFlow::addEdge(id[p[r]], t, maxFlow::inf);
    maxFlow::addEdge(t, id[p[r]], 0);
    for (int i = 1; i <= e_tot; ++i) {
        int eID = e[i];
        maxFlow::addEdge(id[u[eID]], id[v[eID]], 1);
        maxFlow::addEdge(id[v[eID]], id[u[eID]], 1);
    }
    int ret = maxFlow::dinic(p_tot + 2, s, t);
    ++tree_tot;
    tree_u[tree_tot] = p[l], tree_v[tree_tot] = p[r], tree_w[tree_tot] = ret;
    //printf("u = %d, v = %d, w = %d\n", p[l], p[r], ret);
    int L = l, R = r;
    for (int i = l; i <= r; ++i) {
        int pp = p[i];
        if (maxFlow::dis[id[pp]] != -1) {
            tmp[L++] = p[i];
        } else {
            tmp[R--] = p[i];
        }
    }
    for (int i = l; i <= r; ++i) p[i] = tmp[i];
    solve(l, L - 1), solve(L, r);
}

int f1[max_N], sz[max_N], ans;

int find1(int x) {
    return x == f1[x] ? x : f1[x] = find1(f1[x]);
}

void merge1(int x, int y, int w) {
    x = find1(x), y = find1(y);
    ans += w * sz[x] * sz[y];
    f1[x] = y;
    sz[y] += sz[x];
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", u + i, v + i), merge(u[i], v[i]);
    }
    for (int i = 1; i <= n; ++i) {
        vec_p[find(i)].push_back(i);
    }
    for (int i = 1; i <= m; ++i) {
        vec_e[find(u[i])].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        if (f[i] != i) continue;
        p_tot = 0;
        for (auto x : vec_p[i]) {
            p[++p_tot] = x;
            id[x] = p_tot;
        }
        e_tot = 0;
        for (auto x : vec_e[i]) e[++e_tot] = x;
        tree_tot = 0;
        solve(1,  p_tot);
        for (auto x : vec_p[i]) {
            f1[x] = x, sz[x] = 1;
        }
        int cnt[4] = {0, 0, 0, 0};
        for (int j = 1; j <= tree_tot; ++j) ++cnt[tree_w[j]];
        for (int j = 1; j <= 3; ++j) cnt[j] += cnt[j - 1];
        for (int j = tree_tot; j; --j) tree_q[cnt[tree_w[j]]--] = j;
        for (int j = tree_tot; j; --j) {
            int k = tree_q[j];
            //printf("%d %d %d\n", tree_u[k], tree_v[k], tree_w[k]);
            merge1(tree_u[k], tree_v[k], tree_w[k]);
        }
    }
    printf("%d\n", ans);
    return 0;
}

