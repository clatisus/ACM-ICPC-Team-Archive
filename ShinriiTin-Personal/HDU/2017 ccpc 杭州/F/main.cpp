/*
怎么搜都能过 
*/
#include <bits/stdc++.h>

int T, n, Hm, He;

int a[5], b[5], c[5], hp[5];

int t[10], cost[10], x[10], y[10], p[10];

std::pair<int, int> opt[10];

std::vector<int> ans[5];

bool dfs(int x, int crystal, int sp, int Hm, int He, int turn) {
    if (He <= 0) return true;
    if (x > n || turn > 3 || Hm <= 0) return false;
    int id = p[x];
    if (crystal < cost[id] || (t[id] == 1 && hp[1] <= 0 && hp[2] <= 0 && hp[3] <= 0)) {
        int tmp[5];
        for (int i = 1; i <= 3; ++i) {
            if (hp[i] > 0) {
                Hm -= a[i];
            } else {
                hp[i] = c[i];
            }
            tmp[i] = hp[i];
        }
        bool res = dfs(x, 10, 0, Hm, He, turn + 1);
        for (int i = 1; i <= 3; ++i) hp[i] = tmp[i];
        return res;
    }
    crystal -= cost[id];
    opt[x] = {turn, -1};
    if (t[id] == 1) {
        for (int i = 1; i <= 3; ++i) hp[i] -= ::x[id] + sp;
        if (dfs(x + 1, crystal, sp + y[id], Hm, He, turn)) return true;
        for (int i = 1; i <= 3; ++i) hp[i] += ::x[id] + sp;
    } else if (t[id] == 2) {
        He -= ::x[id] + sp;
        if (dfs(x + 1, crystal, sp + y[id], Hm, He, turn)) return true;
    } else {
        opt[x].second = 0;
        if (dfs(x + 1, crystal, sp, Hm, He - ::x[id] - sp, turn)) return true;
        for (int i = 1; i <= 3; ++i) {
            opt[x].second = i;
            hp[i] -= ::x[id] + sp;
            if (dfs(x + 1, crystal, sp, Hm, He, turn)) return true;
            hp[i] += ::x[id] + sp;
        }
    }
    opt[x] = {0, 0};
    return false;
}

void testCase() {
    memset(opt, 0, sizeof(opt));
    scanf("%d%d%d", &n, &Hm, &He);
    for (int i = 1; i <= 3; ++i) {
        scanf("%d%d%d", a + i, b + i, c + i);
    }
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        scanf("%d%d%d", t + i, cost + i, x + i);
        if (t[i] != 3) scanf("%d", y + i);
    }
    do {
        for (int i = 1; i <= 3; ++i) hp[i] = b[i];
        if (dfs(1, 10, 0, Hm, He, 1)) {
            puts("Yes");
            for (int i = 0; i <= 3; ++i) ans[i].clear();
            for (int i = 1; i <= n; ++i) ans[opt[i].first].push_back(i);
            for (int i = 1; i <= 3; ++i) {
                int siz = int(ans[i].size());
                printf("%d\n", siz);
                for (int j = 0; j < siz; ++j) {
                    printf("%d%c", p[ans[i][j]], " \n"[j + 1 == siz]);
                }
                for (int j = 0; j < siz; ++j) {
                    printf("%d%c", opt[ans[i][j]].second, " \n"[j + 1 == siz]);
                }
            }
            return;
        }
    } while (std::next_permutation(p + 1, p + 1 + n));
    puts("No");
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
