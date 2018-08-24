#include <bits/stdc++.h>

#define MAXN (200010)

int n;
int f[MAXN];
bool in[MAXN];
int cnt[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n + n; ++i) {
        scanf("%d", f + i);
    }
    for (int i = 1; i <= n; ++i) {
       in[i] = true;
       ++ cnt[f[i]];
    }
    std::queue<int> q;
    for (int i = n + 1; i <= n + n; ++i) {
        if (!cnt[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        in[u] = true;
        if (in[f[u]]) {
            in[f[u]] = false;
            if (-- cnt[f[f[u]]] == 0) {
                q.push(f[f[u]]);
            }
            cnt[f[u]] = 0;
        }
        ++ cnt[f[u]];

    }
    for (int i = 1; i <= n + n; ++i) {
        if (in[i]) {
            printf("%d ", i);
        }
    }
    puts("");
    return 0;
}

