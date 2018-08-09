#include <bits/stdc++.h>
 
#define MAXN (500010)
 
int n;
int ans[MAXN];
bool vis[MAXN];
 
int main() {
    scanf("%d", &n);
    int m = 0;
    for (; (1 << m) <= (n - 1); ++m);
    for (int i = n - 1; i >= 1; --i) {
        if (!vis[i]) {
            int j = i ^ ((1 << m) - 1);
            if (j >= n) j = 0;
            assert(!vis[j]);
            vis[i] = vis[j] = true;
            ans[i] = j;
            ans[j] = i;
        }
        if (i == (1 << (m - 1))) --m;
    }
    if (!vis[0]) ans[0] = 0;
    for (int i = 0; i < n; ++i) {
        printf("%d%c", ans[i], " \n"[i == n - 1]);
    }
    return 0;
}
