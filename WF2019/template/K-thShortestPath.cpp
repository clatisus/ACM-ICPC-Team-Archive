namespace kth { // 求k长路, O((n+m)logn+klogk)
    const int max_N = (int) 3e5 + 21;
    const int log_N = 20;
    using edge = std::pair<int, int>;
    std::vector<edge> vec[max_N], _vec[max_N];
    int n, s, t, p[max_N], dis[max_N], Q[max_N], tot;
    #define ht(x) ((x) ? (x)->h : 0)
    using ptr = struct node *;
    struct node {
        ptr ls, rs;
        int u, v, h;
    } pool[max_N * log_N]; // mlogm
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
    // 求k短路时改成std::greater<state>
    int solve(int k) {
        // 建图, vec为反向边表, _vec为原边表
        // 求最长（最短）路, p中记录最长（最短）路树, Q保存树上拓扑序（路径长度序）
        if (k == 1) return dis[s];

        for (int i = 1; i <= tot; ++i) {
            int u = Q[i];
            rt[u] = rt[p[u]];
            for (auto &e : _vec[u]) {
                int v = e.first, w = e.second;
                if (dis[v] == -1 || p[u] == v) continue;
                // 当有重边存在的时候不能简单判断p[u], 要记录树边的编号
                ptr x = new_node(v, dis[u] - dis[v] - w);
                // 求k短路时改为 w - dis[u] + dis[v]
                rt[u] = merge(rt[u], x);
            }
        }
        if (rt[s]) pq.emplace(dis[s] - rt[s]->v, rt[s]);
        //当求k短路的时候改为 dis[s] + rt[s]->v, 后面代码中的加减也相应取反
        while (k--) {
            auto x = pq.top();
            pq.pop();
            if (k == 1) return x.first;
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
};