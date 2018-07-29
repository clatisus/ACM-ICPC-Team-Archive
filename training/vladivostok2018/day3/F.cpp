#include <bits/stdc++.h>

const int max_N = (int) 4e5 + 21;
const int Block = std::sqrt(max_N * std::log(max_N));
//const int Block = 1;

#define ALL(x) (x).begin(), (x).end()
#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r

using pair = std::pair<int, int>;
using VI = std::vector<int>;

int n, m, q;

int t[max_N], x1[max_N], x2[max_N], Y1[max_N], y2[max_N];

pair big[max_N], small[max_N];

int h[max_N], tot, seg_tot;

VI seg[max_N << 2];

void seg_clear() {
    for (int i = 1; i < (seg_tot << 1); ++i) {
        VI().swap(seg[i]);
    }
}

void seg_build() {
    for (int i = 1; i <= n; ++i) {
        if (big[i].first > seg_tot) continue;
        seg[seg_tot + big[i].first - 1].push_back(big[i].second);
    }
    for (int i = 0; i < seg_tot; ++i) {
        std::sort(ALL(seg[i + seg_tot]));
    }
    for (int i = seg_tot - 1; i; --i) {
        seg[i].resize(seg[ls(i)].size() + seg[rs(i)].size());
        std::merge(ALL(seg[ls(i)]), ALL(seg[rs(i)]), seg[i].begin());
    }
}

int qxl, qxr, qa, qyl, qyr;

void seg_query(int x, int l, int r) {
    if (qxl <= l && r <= qxr) {
        qa += std::upper_bound(ALL(seg[x]), qyr) - std::lower_bound(ALL(seg[x]), qyl);
    } else {
        if (qxl <= mid) seg_query(lch);
        if (qxr > mid) seg_query(rch);
    }
}

int query(int x1, int x2, int Y1, int y2) {
    int res = 0;
    for (int i = 1; i <= m; ++i)
        if (x1 <= small[i].first && small[i].first <= x2 && Y1 <= small[i].second && small[i].second <= y2) {
            ++res;
        }
    qxl = x1, qxr = x2, qyl = Y1, qyr = y2;
    qa = 0;
    seg_query(1, 1, seg_tot);
    res += qa;
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &big[i].first, &big[i].second);
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        char opt[5];
        scanf("%s", opt);
        if (*opt == '?') {
            scanf("%d%d%d%d", x1 + i, Y1 + i, x2 + i, y2 + i);
            t[i] = 0;
            h[++tot] = x1[i];
            h[++tot] = x2[i];
            if (x1[i]) h[++tot] = x1[i] - 1;
        } else {
            scanf("%d%d", x1 + i, Y1 + i);
            t[i] = 1;
        }
    }

    std::sort(h + 1, h + 1 + tot);
    tot = std::unique(h + 1, h + 1 + tot) - (h + 1);
    for (int i = 1; i <= n; ++i) {
        big[i].first = std::lower_bound(h + 1, h + 1 + tot, big[i].first) - h;
    }

    seg_tot = 1;
    while (seg_tot < tot) seg_tot <<= 1;
    seg_build();

    int last = 0;

    for (int i = 1; i <= q; ++i) {
        if (t[i]) {
            x1[i] += last % 100;
            Y1[i] += last % 101;

            x1[i] = std::lower_bound(h + 1, h + 1 + tot, x1[i]) - h;
            small[++m] = {x1[i], Y1[i]};
            if (m >= Block) {
                while (m) big[++n] = small[m--];
                seg_clear();
                seg_build();
            }
        } else {
            x1[i] = std::lower_bound(h + 1, h + 1 + tot, x1[i]) - h;
            x2[i] = std::lower_bound(h + 1, h + 1 + tot, x2[i]) - h;
            printf("%d\n", last = query(x1[i], x2[i], Y1[i], y2[i]));
        }
    }

    return 0;
}
/*
5
0 0
1 0
0 1
1 1
1 1
9
? 0 1 1 2
+ 1 2
+ 2 2
? 1 0 2 2
? 0 0 0 0
+ 3 3
? 3 3 3 3
? 4 3 4 3
? 4 4 5 5
*/

