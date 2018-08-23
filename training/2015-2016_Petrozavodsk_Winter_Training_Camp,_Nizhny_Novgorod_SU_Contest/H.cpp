#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

int n;

namespace LCT {
    using ptr = struct node *;

    ptr null, tail, rt[max_N];

    struct node {
        int rev;
        ptr p, ch[2];

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

    ptr new_node() {
        ptr x = tail++;
        x->rev = 0;
        x->ch[0] = x->ch[1] = x->p = null;
        return x;
    }

    void rot(ptr x) {
        ptr y = x->p;
        int d = x->dir(), dd = y->dir();
        y->p->set_ch(x, dd);
        y->set_ch(x->ch[d ^ 1], d);
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
    }

    void access(ptr x) {
        ptr y = x, rch = null;
        for (; x != null; x = x->p) {
            splay(x);
            x->set_ch(rch, 1);
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
    }

    ptr find(ptr x) {
        access(x);
        while (x->down(), x->ch[0] != null) x = x->ch[0];
        return x;
    }

    void init() {
        tail = pool;
        null = tail++;
        null->rev = 0;
        null->ch[0] = null->ch[1] = null->p = null;
    }
};

int main() {
    LCT::init();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        LCT::rt[i] = LCT::new_node();
    }
    while (true) {
        char opt[4];
        scanf("%s", opt);
        if (opt[0] == 'E') break;
        int a, b;
        scanf("%d%d", &a, &b);
        if (opt[0] == 'C') {
            LCT::link(LCT::rt[a], LCT::rt[b]);
        } else if (opt[0] == 'D') {
            LCT::cut(LCT::rt[a], LCT::rt[b]);
        } else if (opt[0] == 'T') {
            printf(LCT::find(LCT::rt[a]) == LCT::find(LCT::rt[b]) ? "YES\n" : "NO\n");
            fflush(stdout);
        }
    }
    return 0;
}
