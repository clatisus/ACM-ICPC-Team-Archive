#include <bits/stdc++.h>

using LL = unsigned long long;

const int n = 8;

int T, a[n][n], b[n][n], cnt;

char s[10];

void init() {
    memset(a, -1, sizeof(a));
    cnt = n * n;
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < n; ++j) {
            if (s[j] == 'A') {
                a[i][j] = 1;
                --cnt;
            }
            if (s[j] == 'B') {
                a[i][j] = 0;
                --cnt;
            }
        }
    }
}

namespace plug {
    using HashT = std::unordered_map<int, LL>;
    const int max_N = 12;
    struct state {
        int pos, a[max_N], n, m;

        state(int col, int s) : n(col) {
            m = 0;
            pos = 1;
            for (int i = n - 1; ~i; --i) {
                a[i] = (s & 7), s >>= 3;
                (a[i] > m) && (m = a[i]);
            }
            ++m;
        }

        void minimal() {
            static int f[max_N];
            memset(f, -1, sizeof(f));
            f[0] = 0, m = 1;
            bool flag = false;
            for (int i = 0; i < n; ++i) {
                if (a[i] == pos) flag = true;
            }
            if (flag) {
                f[pos] = m++;
                pos = 1;
            } else {
                pos = -1;
            }
            for (int i = 0; i < n; ++i) {
                if (f[a[i]] == -1) f[a[i]] = m++;
                a[i] = f[a[i]];
            }
        }

        void add(int u) {
            a[u] = m++;
        }

        void del(int u) {
            a[u] = 0;
        }

        void unite(int u, int v) {
            for (int i = 0; i < n; ++i)
                if (a[i] == u) a[i] = v;
            if (pos == u) pos = v;
        }

        int hash() {
            minimal();
            int s = 0;
            for (int i = 0; i < n; ++i) {
                assert(a[i] <= 5);
                (s <<= 3) |= a[i];
            }
            return s;
        }
    };

    HashT pre, cur;

    void updt(HashT &map, int set, LL tmp) {
        map[set] += tmp;
    }

    LL solve(int n, int m) {
        //input
        state sta(m, 0);
        for (int i = 0; i < m; ++i) {
            sta.a[i] = 1;
        }
        sta.m = 2, sta.pos = 1;
        pre.clear();
        pre[sta.hash()] = 1;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                //transfer grid (r, c)
                cur.clear();
                for (auto pr : pre) {
                    if (a[r][c] != 0) {
                        state sta(m, pr.first);
                        int left = c ? sta.a[c - 1] : 0;
                        int up = sta.a[c];
                        sta.add(c);
                        if (left) sta.unite(left, sta.a[c]);
                        if (up && left != up) sta.unite(up, sta.a[c]);
                        int s = sta.hash();
                        if (sta.pos != -1) {
                            updt(cur, s, pr.second);
                        }
                    }
                    if (a[r][c] != 1) {
                        state sta(m, pr.first);
                        sta.del(c);
                        int s = sta.hash();
                        if (sta.pos != -1) {
                            updt(cur, s, pr.second);
                        }
                    }
                }
                pre = cur;
            }
        }
        LL ret = 0;
        for (auto pr : cur) ret += pr.second;
        return ret;
    }
};

double solve() {
    return plug::solve(n, n) / pow(2, cnt);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        init();
        printf("Alice %.6f ", solve());
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                b[i][j] = ~a[j][i] ? !a[j][i] : -1;
            }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                a[i][j] = b[i][j];
            }
        printf("Bob %.6f\n", solve());
    }
    return 0;
}

