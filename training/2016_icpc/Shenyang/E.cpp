#include <bits/stdc++.h>

const int max_N = 100 + 5;

int T, n, m, k, deg[max_N], ans;

std::bitset<max_N> vec[max_N];

bool vis[max_N];

int vp[max_N], cnt;

void dfs(int u) {
    vis[u] = true;
    vp[++cnt] = u;
    for (int v = 1; v <= n; ++v) {
        if (vis[v] || !vec[u].test(v)) continue;
        dfs(v);
    }
}

int Q[max_N], tot;

void calc(int x, int siz, std::bitset<max_N> cur) {
    if (x > tot) {
        ++ans;
        /*
        printf("[%d]", ans);
        for (int i = 1; i <= n; ++i) {
            if (!cur.test(i)) continue;
            printf(" %d", i);
        }
        puts("");
        */
        return;
    }
    if (tot - x + siz + 1 < k) return;
    if (tot - x + siz >= k) calc(x + 1, siz, cur);
    if (siz == k) return;
    int u = Q[x];
    if ((vec[u] & cur).count() < siz) return;
    cur.set(u);
    calc(x + 1, siz + 1, cur);
}

void solve(int u) {
    cnt = 0;
    dfs(u);
    if (cnt < k) return;
    int sum = 0;
    for (int i = 1; i <= cnt; ++i) {
        u = vp[i];
        sum += deg[u];
    }
    if (sum == cnt * (cnt - 1)) {
        int tmp = 1;
        for (int i = 0; i < k; ++i) {
            tmp = tmp * (cnt - i) / (i + 1);
        }
        ans += tmp;
        return;
    }
    for (int i = 1; i <= cnt; ++i) {
        u = vp[i];
        tot = 0;
        for (int v = 1; v < u; ++v)
            if (vec[u].test(v)) {
                Q[++tot] = v;
            }
        if (tot + 1 < k) continue;
        std::bitset<max_N> st;
        st.set(u);
        calc(1, 1, st);
    }
}

void testCase() {
    scanf("%d%d%d", &n, &m, &k);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].set(v);
        vec[v].set(u);
        ++deg[u], ++deg[v];
    }
    memset(vis + 1, 0, n * sizeof(bool));
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        solve(i);
    }
    printf("%d\n", ans);
}

void clear() {
    for (int i = 1; i <= n; ++i) {
        deg[i] = 0;
        vec[i].reset();
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        testCase();
        clear();
    }
    return 0;
}

