#include <bits/stdc++.h>

#define mid ((l + r) >> 1)
#define lch l, mid
#define rch mid + 1, r

#define SZ(x) int((x).size())
#define ALL(x) (x).begin(), (x).end()

const int max_N = (int) 2e5 + 21;
const int max_M = 25000 + 21;
const int log_M = std::log(max_M);

int N, R, Q, r[max_N], cnt[max_M];

bool isBig[max_M];

int dfn[max_N], tot, _dfn[max_N], p[max_N << 1];

std::vector<int> vec[max_N], col[max_M], _col[max_M], big;

std::unordered_map<int, int> map;

void dfs(int x) {
    dfn[x] = ++tot;
    p[tot] = x;
    col[r[x]].push_back(tot);

    if (isBig[r[x]]) {
        for (auto &y : big) {
            if (r[x] == y) continue;
            int hash = y * max_M + r[x];
            map[hash] += cnt[y];
        }
        ++cnt[r[x]];
    }

    for (auto &y : vec[x]) {
        dfs(y);
    }

    if (isBig[r[x]]) --cnt[r[x]];
    _dfn[x] = ++tot;
    _col[r[x]].push_back(tot);
}

int query(int r1, int r2) {
    int hash = r1 * max_M + r2;

    if (map.count(hash)) return map[hash];

    int res = 0;  

    if (SZ(col[r1]) < SZ(col[r2]) * 1.1) {
        std::vector<int> &v = col[r2];
        for (auto &id : col[r1]) {
            int x = p[id], l = dfn[x], r = _dfn[x];
            res += std::upper_bound(ALL(v), r) - std::lower_bound(ALL(v), l);
        }
    } else {
        std::vector<int> &v = col[r1];
        std::vector<int> &_v = _col[r1];
        for (auto &id : col[r2]) {
            int x = p[id], r = _dfn[x];
            res += std::upper_bound(ALL(v), r) - v.begin();
            res -= std::upper_bound(ALL(_v), r) - _v.begin();
        } 
    }

    return map[hash] = res;
}

int main() {
    scanf("%d%d%d", &N, &R, &Q);
    for (int i = 1, p; i <= N; ++i) {
        if (i > 1) {
            scanf("%d", &p);
            vec[p].push_back(i);
        }
        scanf("%d", r + i);
        ++cnt[r[i]];
    }

    for (int i = 1; i <= R; ++i) {
        if (1ll * cnt[i] * cnt[i] >= N) {
            isBig[i] = true;
            big.push_back(i);
        }
        cnt[i] = 0;
    }

    dfs(1);

    while (Q--) {
        int r1, r2;
        scanf("%d%d", &r1, &r2);
        printf("%d\n", query(r1, r2));
        fflush(stdout);
    }

    return  0;
}
