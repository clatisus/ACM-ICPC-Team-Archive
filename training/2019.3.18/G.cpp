#include <bits/stdc++.h>

int n;
int cnt[1010], tot;
std::vector<int> vec;

void dfs(int u) {
    while (cnt[u] != 2) {
        int v = ((2 * u) + 1 - cnt[u]) % (n / 2);
        ++cnt[u];
        dfs(v);
    }
    vec.push_back(u);
}

int main() {
    scanf("%d", &n);
    if (n == 2) {
        puts("10");
        return 0;
    }
    dfs(0);
    std::reverse(vec.begin(), vec.end());
    for (int i = 0, sz = (int)vec.size(); i + 1 < sz; ++i) {
        int u = vec[i];
        int v = vec[i + 1];
        if (v == (2 * u + 1) % (n / 2)) printf("1");
        else printf("0");
    }
    puts("");
    return 0;
}
