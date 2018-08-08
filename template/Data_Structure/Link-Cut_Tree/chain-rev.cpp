const int max_N = (int) 1e5 + 21;

namespace Splay {
    typedef struct node *star;
    star null, tail;

    inline star new_node(int val);

    struct node {
        int siz, val, add;
        bool rev;
        star ch[2], p;

        inline int d() {
            if (this == null)return -1;
            rpt(i, 0, 1)
            if (p->ch[i] == this)return i;
            return -1;
        }

        inline void set_ch(star x, int d) {
            if (this != null && ~d) ch[d] = x;
            if (x != null) x->p = this;
        }

        inline void add_it(int a) {
            if (this == null)return;
            val += a, add += a;
        }

        inline void update() {
            siz = ch[0]->siz + 1 + ch[1]->siz;
        }

        inline void push_down() {
            if (rev) {
                std::swap(ch[0], ch[1]);
                ch[0]->rev ^= 1, ch[1]->rev ^= 1;
                rev = 0;
            }
            if (add) {
                ch[0]->add_it(add), ch[1]->add_it(add);
                add = 0;
            }
        }
    } pool[max_N];

    inline void rot(star x) {
        star y = x->p;
        int d = x->d(), d1 = y->d();
        y->p->set_ch(x, d1);
        y->set_ch(x->ch[d ^ 1], d), y->update();
        x->set_ch(y, d ^ 1);
    }

    void pd(star x) {
        if (~x->d())pd(x->p);
        x->push_down();
    }

    inline void splay(star x) {
        pd(x);
        for (int d, d1; ~(d = x->d()); rot(x))
            if (~(d1 = x->p->d()))rot(d ^ d1 ? x : x->p);
        x->update();
    }

    star kth(star x, int k) {
        x->push_down();
        int rk = x->ch[0]->siz + 1;
        if (rk == k)return x;
        if (rk > k)return kth(x->ch[0], k);
        return kth(x->ch[1], k - rk);
    }

    inline star new_node(int val) {
        star x = tail++;
        x->ch[0] = x->ch[1] = x->p = null;
        x->val = val, x->siz = 1;
        x->add = x->rev = 0;
        return x;
    }

    inline void init() {
        tail = pool;
        null = tail++;
        null->ch[0] = null->ch[1] = null->p = null;
        null->val = null->siz = null->add = null->rev = 0;
    }
};

namespace LCT {
    typedef struct node *star;
    star null, tail;

    struct node {
        int siz;
        bool rev;
        star ch[2], p;
        Splay::star link;

        inline int d() {
            if (this == null)return -1;
            rpt(i, 0, 1)
            if (p->ch[i] == this)return i;
            return -1;
        }

        inline void set_ch(star x, int d) {
            if (this != null && ~d) ch[d] = x;
            if (x != null) x->p = this;
        }

        inline void maintain() {
            push_down();
            int rk = ch[0]->siz + 1;
            link = Splay::kth(link, rk);
            Splay::splay(link);
        }

        inline void update() {
            siz = ch[0]->siz + 1 + ch[1]->siz;
        }

        inline void push_down() {
            if (rev) {
                std::swap(ch[0], ch[1]);
                ch[0]->rev ^= 1, ch[1]->rev ^= 1;
                rev = 0;
            }
        }
    } pool[max_N];

    inline void rot(star x) {
        star y = x->p;
        int d = x->d(), d1 = y->d();
        y->p->set_ch(x, d1);
        y->set_ch(x->ch[d ^ 1], d), y->update();
        x->set_ch(y, d ^ 1);
    }

    void pd(star x, star &top) {
        if (~x->d())pd(x->p, top);
        else top = x;
        x->push_down();
    }

    inline void splay(star x) {
        star top;
        pd(x, top), x->link = top->link;
        for (int d, d1; ~(d = x->d()); rot(x))
            if (~(d1 = x->p->d()))rot(d ^ d1 ? x : x->p);
        x->update();
    }

    inline void change_rch(star x, star y) {
        x->maintain();
        x->ch[1]->link = x->link->ch[1];
        x->ch[1]->link->p = Splay::null;
        x->set_ch(y, 1), x->link->set_ch(y->link, 1);
        x->update(), x->link->update();
    }

    inline void Access(star x) {
        star rch = null;
        for (star y = x; y != null; rch = y, y = y->p)splay(y), change_rch(y, rch);
        splay(x);
    }

    inline void Evert(star x) {
        Access(x), x->rev ^= 1, x->link->rev ^= 1;
    }

    inline star get_path(star x, star y) {
        return Evert(x), Access(y), y;
    }

    inline int query(star x) {
        Evert(x), Access(x);
        return x->link->val;
    }

    inline star new_node(int val) {
        star x = tail++;
        x->ch[0] = x->ch[1] = x->p = null;
        x->siz = 1, x->rev = 0;
        x->link = Splay::new_node(val);
        return x;
    }

    inline void init() {
        Splay::init();
        tail = pool;
        null = tail++;
        null->ch[0] = null->ch[1] = null->p = null;
        null->link = Splay::null;
        null->siz = null->rev = 0;
    }
};
