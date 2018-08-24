#include <bits/stdc++.h>

const int max_N = (int) 1e6 + 21;

int n, m, a[max_N], pos[max_N], id[max_N], L, R;

char s[max_N];

void solve(int x) {
    int i = 0, res = -1;
    while (true) {
        res += a[id[i]] + 1;
        if (i + x >= n) break;
        int y = id[i + x];
        i = pos[y];
    }
    printf("%d\n", res);
}

int main() {
    fgets(s, max_N, stdin);
    n = strlen(s);
    while (s[n - 1] == '\n' || s[n - 1] == '\r') s[--n] = ' ';
    int x = 0;
    while (x < n) {
        int y = x;
        while (s[y] != ' ') ++y;
        a[m] = y - x;
        pos[m] = x;
        for (int i = x; i < y; ++i) id[i] = m;
        id[y] = ++m;
        x = y + 1;
    }
    scanf("%d%d", &L, &R);
    for (int i = L; i <= R; ++i) solve(i);
    return 0;
}

