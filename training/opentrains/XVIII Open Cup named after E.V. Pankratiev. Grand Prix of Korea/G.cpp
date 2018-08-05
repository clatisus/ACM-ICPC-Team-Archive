#include <bits/stdc++.h>

namespace LCT {
    const int max_N = (int) 4e5 + 21;

    using ptr = struct node *;

    ptr null, tail, rt[max_N];

    struct node {
        int val, rev;
        ptr max, p, ch[2];

        void updt() {
            max = this;
            if (ch[0]->max->val > max->val) {
                max = ch[0]->max;
            }
            if (ch[1]->max->val > max->val) {
                max = ch[1]->max;
            }
        }

        void down() {
            if (!rev) return;
            std::swap(ch[0], ch[1]);
            ch[0]->rev ^= 1;
            ch[1]->rev ^= 1;
            rev = 0;
        }

        int dir() {
            if (p->ch[0] == this) return 0;
            if (p->ch[1] == this) return 1;
            return -1;
        }

        void set_ch(ptr x, int d) {
            if (~d) ch[d] = x;
            if (x != null) {
                x->p = this;
            }
        }
    } pool[max_N];

    ptr new_node(int val) {
        ptr x = tail++;
        x->val = val;
        x->rev = 0;
        x->ch[0] = x->ch[1] = x->p = null;
        return x->max = x;
    }

    void rot(ptr x) {
        ptr y = x->p;
        int d = x->dir(), dd = y->dir();
        y->p->set_ch(x, dd);
        y->set_ch(x->ch[d ^ 1], d);
        y->updt();
        x->set_ch(y, d ^ 1);
    }

    void putdown(ptr x) {
        if (~x->dir()) putdown(x->p);
        x->down();
    }

    void splay(ptr x) {
        putdown(x);
        int d, dd;
        for(; ~(d = x->dir()); rot(x))
            if (~(dd = x->p->dir())) {
                rot((d ^ dd) ? x : x->p);
            }
        x->updt();
    }

    void access(ptr x) {
        ptr y = x, rch = null;
        for (; x != null; x = x->p) {
            splay(x);
            x->set_ch(rch, 1);
            x->updt();
            rch = x;
        }
        splay(y);
    }

    void evert(ptr x) {
        access(x), x->rev ^= 1;
    }

    ptr path(ptr x, ptr y) {
        evert(x), access(y);
        return y;
    }

    void link(ptr x, ptr y) {
        evert(x), x->p = y;
    }

    void cut(ptr x, ptr y) {
        path(x, y);
        x->p = null;
        y->set_ch(null, 0);
        y->updt();
    }

    void init() {
        tail = pool;
        null = tail++;
        null->val = null->rev = 0;
        null->ch[0] = null->ch[1] = null->p = null->max =null;
    }
};

using ll = long long;

const int max_N = (int) 1e5 + 21;
const int max_M = (int) 3e5 + 21;

int n, m, u[max_M], v[max_M], w[max_M], Q[max_M];

bool inTree[max_M];

std::vector<int> vec[max_N];

struct cmp {
    bool operator()(int x, int y) {
        return w[x] < w[y];
    }
};

int f[max_N];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

ll ans;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        Q[i] = i;
        scanf("%d%d%d", u + i, v + i, w + i);
        if (u[i] > v[i]) std::swap(u[i], v[i]);
        vec[u[i]].push_back(i);
        vec[v[i]].push_back(i);
    }

    LCT::init();
    for (int i = 1; i <= n; ++i) LCT::rt[i] = LCT::new_node(0);
    for (int i = 1; i <= m; ++i) {
        LCT::rt[i + n] = LCT::new_node(w[i]);
        LCT::rt[i + n]->p = LCT::rt[u[i]];
    }

    std::sort(Q + 1, Q + 1 + m, cmp());
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i) {
        int x = find(u[Q[i]]), y = find(v[Q[i]]);
        if (x == y) continue;
        f[x] = y;
        ans += w[Q[i]];
        inTree[Q[i]] = true;
        LCT::link(LCT::rt[Q[i] + n], LCT::rt[v[Q[i]]]);
    }

    for (int i = 1; i <= n; ++i) {
        for (auto it : vec[i]) {
            auto e = LCT::rt[it + n];
            LCT::splay(e);
            e->val = 0;
            e->updt();
        }

        std::vector<int> edge;
        for (auto it : vec[i]) {
            if (inTree[it]) continue;
            auto x = LCT::rt[u[it]];
            auto y = LCT::rt[v[it]];
            int id = LCT::path(x, y)->max - LCT::pool - n;
            ans -= w[id];
            LCT::cut(LCT::rt[v[id]], LCT::rt[id + n]);
            edge.push_back(id);
            ans += w[it];
            LCT::link(LCT::rt[v[it]], LCT::rt[it + n]);
        }

        printf("%lld\n", ans);

        for (auto it : vec[i]) {
            auto e = LCT::rt[it + n];
            LCT::splay(e);
            e->val = w[it];
            e->updt();
            if (!inTree[it]) {
                ans -= w[it];
                LCT::cut(LCT::rt[v[it]], LCT::rt[it + n]);
            }
        }

        for (auto id : edge) {
            ans += w[id];
            LCT::link(LCT::rt[v[id]], LCT::rt[id + n]);
        }
    }

    return 0;
}
