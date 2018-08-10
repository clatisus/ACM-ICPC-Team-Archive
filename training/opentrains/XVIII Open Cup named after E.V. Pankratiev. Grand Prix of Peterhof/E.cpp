#include <bits/stdc++.h>

#define MAXN (100010)
#define MAXS (95)
#define ll long long

int n, l;
char s[MAXN], t[MAXN];
int nxt[MAXN][MAXS];

int getdis(int a, int b) {
    int ret = a <= b ? b - a : b + l - a;
    //printf("a = %d, b = %d, dis = %d\n", a, b, ret);
    return ret;
}

int main() {
    //freopen("stdin2", "r", stdin);
    fgets(s, MAXN, stdin);
    l = strlen(s);
    s[-- l] = 0;
    memset(nxt, -1, sizeof(nxt));
    for (int i = 0; i < l - 1; ++i) {
        if (nxt[l - 1][s[i] - 33] == -1) {
            nxt[l - 1][s[i] - 33] = i;
        }
    }
    nxt[l - 1][s[l - 1] - 33] = l - 1;
    for (int i = l - 2; i >= 0; --i) {
        for (int j = 0; j < MAXS; ++j) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i] - 33] = i;
    }
    ll ans = 0;
    int pos = 0;
    while (fgets(t, MAXN, stdin) != NULL) {
        n = strlen(t);
        while (t[n - 1] == '\n') t[-- n] = 0;
        if (!n) break;
        //printf("t = %s\n", t);
        int now = 0;
        //printf("pos = %d\n", pos);
        for (int i = 0; i < n; ++i) {
            if (isspace(t[i])) continue;
            int j = (pos + i) % l;
            //printf("[i = %d]", i);
            now = std::max(now, getdis(j, nxt[j][t[i] - 33]));
        }
        //printf("now = %d\n", now);
        ans += now + 1;
        pos = (pos + now + 1) % l;
    }
    printf("%lld\n", ans);
    return 0;
}
