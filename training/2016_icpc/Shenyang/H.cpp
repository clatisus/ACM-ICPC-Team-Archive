#include <bits/stdc++.h>

#define MAXN (200)
#define DICS (7)

namespace AC_DFA {
    int go[MAXN][DICS], fail[MAXN], f[MAXN];
    bool bl[MAXN];
    int sz, root;

    int newnode() {
        int ret = ++sz;
        memset(go[ret], 0, sizeof(go[ret]));
        fail[ret] = root;
        bl[ret] = false;
        return ret;
    }

    void init() {
        memset(f, 0, sizeof(f));
        root = 0;
        sz = 0;
        root = newnode();
    }

    void insert(int *s, int len, int v) {
        int p = root;
        for (int i = 1; i <= len; ++i) {
            int c = s[i];
            if (!go[p][c]) {
                go[p][c] = newnode();
            }
            p = go[p][c];
        }
        f[v] = p;
        bl[p] = true;
    }

    void makefail() {
        std::queue<int> que;
        que.push(root);
        while (!que.empty()) {
            int p = que.front(); que.pop();
            for (int i = 1; i < DICS; ++i) {
                if (go[p][i]) {
                    fail[go[p][i]] = fail[p] ? go[fail[p]][i] : root;
                    int q = go[p][i];
                    que.push(q);
                } else {
                    go[p][i] = p == root ? root : go[fail[p]][i];
                }
            }
        }
    }
}

using namespace AC_DFA;

int s[20];
double a[100][100], b[100][100];

void sqr() {
    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= sz; ++j) {
            b[i][j] = 0;
            for (int k = 1; k <= sz; ++k) {
                b[i][j] += a[i][k] * a[k][j];
            }
        }
    }
    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= sz; ++j) {
            a[i][j] = b[i][j];
        }
    }
}

void testCase() {
    int n, l;
    scanf("%d%d", &n, &l);
    init();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= l; ++j) {
            scanf("%d", &s[j]);
        }
        insert(s, l, i);
    }
    makefail();

    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= sz; ++j) {
            a[i][j] = 0;
        }
        if (bl[i]) {
            a[i][i] = 1;
            continue;
        }
        for (int j = 1; j < DICS; ++j) {
            a[i][go[i][j]] += 1.0 / 6;
        }
    }

    for (int _ = 1; _ <= 30; ++ _) {
        sqr();
    }
    for (int i = 1; i <= n; ++i) {
        printf("%.6lf%c", a[root][f[i]], " \n"[i == n]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}
