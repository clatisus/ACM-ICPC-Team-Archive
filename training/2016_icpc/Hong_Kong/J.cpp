#include <bits/stdc++.h>

const int max_N = (int) 2e5 + 21;

int n, rt, ch[max_N][2], fail[max_N], Q[max_N], vis[max_N], tot, in[max_N], out[max_N], dp[max_N], _dp[max_N];

char s[max_N], t[max_N];

std::vector<int> vec[max_N], _vec[max_N];

void insert(int n) {
    int u = rt;
    for (int i = 0; i < n; ++i) {
        int c = s[i] - '0';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    vis[u] = 1;
}

int get_fail() {
    int tail = 0;
    Q[++tail] = rt;
    for (int i = 1; i <= tot; ++i) fail[i] = rt;
    fail[rt] = 0;
    for (int x = 1; x <= tail; ++x) {
        int p = Q[x];
        for (int i = 0; i < 2; ++i) {
            if (ch[p][i]) {
                vis[ch[p][i]] |= vis[p];
                fail[ch[p][i]] = fail[p] ? ch[fail[p]][i] : rt;
                int q = ch[p][i];
                vis[q] |= vis[fail[q]];
                Q[++tail] = q;
            } else {
                ch[p][i] = p == rt ? rt : ch[fail[p]][i];
            }
        }
    }

    int ret = 0;
    for (int x = 1; x <= tail; ++x) {
        int u = Q[x];
        if (vis[u]) continue;
        ++ret;
        // printf("valid : %d\n", u);
        for (int i = 0; i < 2; ++i) {
            int v = ch[u][i];
            if (vis[v]) continue;
            // printf("valid(%d) %d -> %d\n", i, u, v);
            vec[u].push_back(v), ++in[v];
            _vec[v].push_back(u), ++out[u];
        }
    }
    return ret;
}

bool topu(int n, std::vector<int> *vec, int *deg, int *dp) {
    int tail = 0;
    for (int i = 1; i <= tot; ++i)
        if (!vis[i] && !deg[i]) {
            Q[++tail] = i;
        }
    for (int x = 1; x <= tail; ++x) {
        int u = Q[x];
        for (auto &v : vec[u]) {
            dp[v] = std::max(dp[v], dp[u] + 1);
            if (!--deg[v]) {
                Q[++tail] = v;
            }
        }
    }
    return tail == n;
}

int main() {
    rt = ++tot;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s);
        insert(strlen(s));
    }
    int sz = get_fail();
    if (!topu(sz, vec, in, dp)) {
        puts("-1");
    } else {
        assert(topu(sz, _vec, out, _dp));
        int ans = 0;
        for (int i = 1; i <= tot; ++i) {
            if (vis[i]) continue;
            // printf("[%d] dp = %d, _dp = %d\n", i, dp[i], _dp[i]);
            ans = std::max(ans, dp[i]);
        }
        int u = rt, cnt = 0;
        for (int i = 0; i < ans; ++i) {
            int v = ch[u][0];
            if (!vis[v] && dp[u] + _dp[v] + 1 == ans) {
                u = v;
                t[cnt++] = '0';
            } else {
                assert(!vis[ch[u][1]]);
                u = ch[u][1];
                t[cnt++] = '1';
            }
        }
        t[cnt] = '\0';
        puts(t);
    }
    return 0;
}
/*
5
00
01
10
110
111


*/

