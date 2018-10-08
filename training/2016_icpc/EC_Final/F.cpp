#include <bits/stdc++.h>

const int max_N = (int) 1e6 + 21;
const int sigma = 27;

int T, n;

char s[max_N], t[max_N];

struct SAM {
    int tot, root, last;

    int go[max_N][sigma], par[max_N], maxlen[max_N];

    bool ban[max_N];

    void init() {
        tot = 0;
        root = last = newnode(0);
    }

    int newnode(int len) {
        int x = ++tot;
        maxlen[x] = len;
        memset(go[x], 0, sizeof(go[x]));
        par[x] = 0;
        ban[x] = false;
        return x;
    }

    void extend(int w) {
        int p = last;
        int np = newnode(maxlen[p] + 1);
        for (; p && !go[p][w]; p = par[p]) {
            go[p][w] = np;
        }
        if (!p) {
            par[np] = root;
        } else {
            int q = go[p][w];
            if (maxlen[q] == maxlen[p] + 1) {
                par[np] = q;
            } else {
                int nq = newnode(maxlen[p] + 1);
                memcpy(go[nq], go[q], sizeof(go[q]));
                ban[nq] = false;
                par[nq] = par[q];
                par[np] = par[q] = nq;
                for (; p && go[p][w] == q; p = par[p]) {
                    go[p][w] = nq;
                }
            }
        }
        last = np;
    }

    int cnt[max_N], ord[max_N], dp[max_N];

    void solve() {
        int n = maxlen[last];
        for (int i = 1; i <= tot; ++i) cnt[maxlen[i]]++;
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
        for (int i = tot; i; --i) ord[cnt[maxlen[i]]--] = i;
        for (int i = 0; i <= n; ++i) cnt[i] = 0;

        for (int i = tot; i; --i) {
            int x = ord[i];
            if (par[x]) ban[par[x]] |= ban[x];
        }

        for (int i = tot; i; --i) {
            int x = ord[i];
            dp[x] = 0x3f3f3f3f;
            if (!ban[x]) dp[x] = 0;
            for (int j = 0; j + 1 < sigma; ++j) {
                int y = go[x][j];
                if (!y) continue;
                dp[x] = std::min(dp[x], dp[y] + 1);
            }
            // printf("[%d] ban = %d, dp = %d\n", x, ban[x], dp[x]);
        }

        /*for (int i = 1; i <= tot; ++i) {
            printf("[%d] par = %d\n", i, par[i]);
            for (int j = 0; j < sigma; ++j) {
                int v = go[i][j];
                if (v) printf("(%d, %d) : %c\n", i, v, j == 26 ? '@' : j + 'a');
            }
        }*/

        int u = root, ans = dp[root];

        if (ans == 0x3f3f3f3f) {
            puts("Impossible");
            return;
        }

        for (int i = 0; i < ans; ++i) {
            for (int j = 0; j + 1 < sigma; ++j) {
                int v = go[u][j];
                if (!v) continue;
                if (i + 1 + dp[v] == ans) {
                    t[i] = 'a' + j;
                    u = v;
                    break;
                }
            }
        }
        t[ans] = '\0';
        puts(t);
    }
} sam;

void testCase() {
    sam.init();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s);
        int m = strlen(s);
        if (i == 1) {
            for (int j = 0; j < m; ++j) {
                sam.extend(s[j] - 'a');
            }
        } else {
            sam.extend(26);
            sam.ban[sam.last] = true;
            for (int j = 0; j < m; ++j) {
                sam.extend(s[j] - 'a');
                sam.ban[sam.last] = true;
            }
        }
    }
    static int id = 0;
    printf("Case #%d: ", ++id);
    sam.solve();
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
    }
    return 0;
}

