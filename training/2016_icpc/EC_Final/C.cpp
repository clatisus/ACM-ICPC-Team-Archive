#include <bits/stdc++.h>

#define MAXN (1010)
#define MAXC (100010)

int n;
int c[MAXN];
int L[MAXN], R[MAXN];
int f[MAXN][MAXN];
int nxt[MAXN], lst[MAXC];
int fa[MAXN];
int ll[MAXN], rr[MAXN];
bool vis[MAXC];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void testCase(int cs) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
        lst[c[i]] = n + 1;
    }
    for (int i = n; i; --i) {
        nxt[i] = lst[c[i]];
        lst[c[i]] = i;
    }
    int ans = 0;
    for (int i = 1, j; i <= n; ++i) {
        for (j = i; j <= n; ++j) {
            if (vis[c[j]]) break;
            vis[c[j]] = true;
        }
        // [i, j)
        R[i] = j - 1;
        ans = std::max(ans, j - i);
        for (--j; j >= i; --j) vis[c[j]] = false;
    }
    for (int i = n, j; i; --i) {
       for (j = i; j; --j) {
           if (vis[c[j]]) break;
           vis[c[j]] = true;
        }
        L[i] = j + 1;
        ans = std::max(ans, i - j);
        for (++j; j <= i; ++j) vis[c[j]] = false;
    }/*
    for (int i = 1; i <= n; ++i) {
        printf("R[%d] = %d\n", i, R[i]);
    }
    for (int i = 1; i <= n; ++i) {
        printf("L[%d] = %d\n", i, L[i]);
    }*/
    for (int i = 1; i <= n; ++i) {
        f[i][i] = 1;
        for (int j = i + 1; j <= n; ++j) {
            f[i][j] = f[i][j - 1];
            int tmp = std::max(i, L[j]);
            f[i][j] = std::max(f[i][j], j - tmp + 1);

            //printf("f[%d][%d] = %d\n", i, j, f[i][j]);
        }
    }

    for (int i = 1; i < n; ++i) {
        int r = R[i];
        for (int j = i; j <= r; ++j) vis[c[j]] = true;

        for (int j = i; j <= n; ++j) {
            fa[j] = j;
            ll[j] = j;
            rr[j] = j;
        }
        int max = 0;
        for (int j = r + 1; j <= n; ++j) {
            if (vis[c[j]]) continue;
            if (j - 1 > r && !vis[c[j - 1]]) {
                // merge left
                int u = find(j - 1);
                int v = find(j);
                if (u != v) {
                    fa[u] = v;
                    ll[v] = std::min(ll[v], ll[u]);
                    rr[v] = std::max(rr[v], rr[u]);
                }
            }
            int u = find(j);
            max = std::max(max, f[ll[u]][rr[u]]);
        }
        ans = std::max(ans, r - i + 1 + max);

        while (r != i) {
            int p = r--;
            vis[c[p]] = false;
            while (p <= n) {
                // merge left
                if (p - 1 > r && !vis[c[p - 1]]) {
                    int u = find(p - 1);
                    int v = find(p);
                    if (u != v) {
                        fa[u] = v;
                        ll[v] = std::min(ll[v], ll[u]);
                        rr[v] = std::max(rr[v], rr[u]);
                    }
                }

                // merge right
                if (p + 1 <= n && !vis[c[p + 1]]) {
                    int u = find(p + 1);
                    int v = find(p);
                    if (u != v) {
                        fa[u] = v;
                        ll[v] = std::min(ll[v], ll[u]);
                        rr[v] = std::max(rr[v], rr[u]);
                    }
                }

                int u = find(p);
                max = std::max(max, f[ll[u]][rr[u]]);
                ans = std::max(ans, r - i + 1 + max);
                p = nxt[p];
            }
        }
        vis[c[i]] = false;
    }

    printf("Case #%d: %d\n", cs, ans);
    // clear
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            f[i][j] = 0;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int _ = 1; _ <= T; ++_) {
        testCase(_);
    }
    return 0;
}
/*
3
3
1 2 3
8
3 1 2 1 6 1 2 5
3
1 1 1
*/
