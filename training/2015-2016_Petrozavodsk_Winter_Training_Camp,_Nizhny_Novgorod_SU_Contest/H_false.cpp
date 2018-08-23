#include <bits/stdc++.h>

#define MAXN (100010)

int n;
int f[MAXN];

void splay(int x, int fa) {
    if (f[x] == 0) {
        f[x] = fa;
        return;
    }
    splay(f[x], x);
    f[x] = fa;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) f[i] = 0;
    while (true) {
        static char opt[4];
        scanf("%s", opt);
        if (opt[0] == 'E') break;
        int a, b;
        scanf("%d%d", &a, &b);
        splay(a, 0);
        if (opt[0] == 'C') {
            f[a] = b;
        } else if (opt[0] == 'D') {
            f[b] = 0;
        } else if (opt[0] == 'T') {
            for (; a != b && b; b = f[b]);
            printf(a == b ? "YES\n" : "NO\n");
            fflush(stdout);
        }
    }
    return 0;
}

