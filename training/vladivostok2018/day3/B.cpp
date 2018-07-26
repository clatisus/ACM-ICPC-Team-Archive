#include <bits/stdc++.h>

#define MAXN (100010)

int SQRT;
int BLOCK_NUM;

struct node {
    std::vector<std::pair<int, int> > a;
    int len;
    int set;
    bool reversed;

    node() { len = 0; set = -1; reversed = false; }
};
int n, q;
int a[MAXN];
int block_num;
std::vector<struct node> vec;

void rebuild() {
    block_num = (n + SQRT - 1) / SQRT;
    std::vector<struct node>().swap(vec);
    vec.resize(block_num);
    for (int i = 0; i < block_num; ++ i) {
        if (i != block_num - 1) {
            vec[i].a.resize(SQRT);
        } else {
            vec[i].a.resize(n % SQRT);
        }
    }
    for (int i = 0; i < n; ++ i) {
        int bl = i / SQRT, bs = i % SQRT, l = bl * SQRT;
        vec[bl].a[bs] = {a[i], i - l};
        ++ vec[bl].len;
    }
    for (int i = 0; i < block_num; ++ i) {
        std::sort(vec[i].a.begin(), vec[i].a.end());
    }
}

void putdown() {
    for (int i = 0, l = 0; i < block_num; l += vec[i ++].len) {
        struct node &p = vec[i];
        int len = p.len;
        for (int j = 0; j < len; ++ j) {
            int v = p.a[j].first, o = p.a[j].second;
            if (p.set != -1) v = p.set;
            else if (p.reversed) o = len - o - 1;
            a[l + o] = v;
        }
    }
}

int split(int sit) {
    if (sit >= n) return block_num;
    int i, l = 0;
    for (i = 0; sit >= l + vec[i].len && i < block_num; l += vec[i ++].len);
    if (sit == l) return i;

    struct node a, b;
    a.a.resize(sit - l);
    b.a.resize(l + vec[i].len - sit);

    for (int j = 0; j < vec[i].len; ++ j) {
        int v = vec[i].a[j].first, o = vec[i].a[j].second;
        if (vec[i].set != -1) v = vec[i].set;
        else if (vec[i].reversed) o = vec[i].len - o - 1;
        if (l + o < sit) a.a[a.len ++] = {v, o};
        else b.a[b.len ++] = {v, l + o - sit};
    }
    ++ block_num;
    vec.insert(vec.begin() + i, a);
    vec[++ i] = b;
    return i;
}

void modify(int l, int r, int x) {
    l = split(l);
    r = split(r + 1) - 1;
    if (x != -1) {
        for (int i = l; i <= r; ++ i) {
            vec[i].set = x;
        }
    } else {
        for (int i = l; i <= r; ++ i) {
            vec[i].reversed = !vec[i].reversed;
        }
        std::reverse(vec.begin() + l, 1 + vec.begin() + r);
    }
}

int solve(int l, int r, int x) {
    int ret = 0;
    l = split(l);
    r = split(r + 1) - 1;
    for (int i = l; i <= r; ++ i) {
        if (vec[i].set != -1) {
            ret += vec[i].set >= x ? vec[i].len : 0;
        } else {
            ret += vec[i].len - (std::lower_bound(vec[i].a.begin(), vec[i].a.end(), std::make_pair(x, INT_MIN)) - vec[i].a.begin());
        }
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }

    SQRT = n / sqrt(n * log(n)) + 1;
    BLOCK_NUM = sqrt(n * log(n)) + 1;

    rebuild();

    scanf("%d", &q);
    for (int ti = 1; ti <= q; ++ ti) {
        //if (block_num == 2 * BLOCK_NUM) {
        if (!(ti % BLOCK_NUM)) {
            putdown();
            rebuild();
        }

        char opt[10];
        int l, r, x;
        scanf("%s%d%d", opt, &l, &r);
        -- l; -- r;
        if (opt[0] == 's') {
            scanf("%d", &x);
            modify(l, r, x);
        } else if (opt[0] == 'g') {
            scanf("%d", &x);
            printf("%d\n", solve(l, r, x));
        } else {
            modify(l, r, -1);
        }
    }
    return 0;
}
