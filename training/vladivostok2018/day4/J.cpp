#include <bits/stdc++.h>

#define MAXN (1010)

int n;
char s[3][3 * MAXN];
int C;
int W[3][MAXN << 3];
bool cla[52][52][52], found;
int press[26];

int hash(char c) {
    if (islower(c)) return (c - 'a') << 1 | 1;
    return (c - 'A') << 1;
}

bool sat(int h) {
    return press[h >> 1] == (h & 1);
}

void dfs(int u) {
    while (u < C && (sat(W[0][u]) || sat(W[1][u]) || sat(W[2][u]))) ++ u;
    if (u == C) {
        found = true;
        return;
    }
    int tmp[3];
    for (int i = 0; i < 3; ++ i) tmp[i] = press[W[i][u] >> 1];
    for (int i = 0; i < 3; ++ i) {
        if (press[W[i][u] >> 1] == -1) {
            press[W[i][u] >> 1] = W[i][u] & 1;
            dfs(u + 1);
            if (found) return;
            press[W[i][u] >> 1] = 1 - press[W[i][u] >> 1];
        } else if (sat(W[i][u])) {
            dfs(u + 1);
            if (found) return;
        }
    }
    for (int i = 0; i < 3; ++ i) press[W[i][u] >> 1] = tmp[i];
}

void testCase() {
    for (int i = 0; i < 3; ++ i) scanf("%s", s[i]);
    for (int i = 0; i < n; ++ i) {
        for (int k = 1; k <= 2; ++ k) for (int p = 1; p <= 2; ++ p) for (int t = 1; t <= 2; ++ t) {
            int tmp[3] = {hash(s[0][i * 3 + k]), hash(s[1][i * 3 + p]), hash(s[2][i * 3 + t])};
            std::sort(tmp, 3 + tmp);
            cla[tmp[0]][tmp[1]][tmp[2]] = true;
        }
    }
    C = 0;
    for (int i = 0; i < 52; ++ i) {
        for (int j = i; j < 52; ++ j) {
            for (int k = j; k < 52; ++ k) {
                if (!cla[i][j][k]) continue;
                W[0][C] = i;
                W[1][C] = j;
                W[2][C] = k;
                ++ C;
                cla[i][j][k] = false;
            }
        }
    }
    for (int i = 0; i < 26; ++ i) press[i] = -1;
    found = false;
    dfs(0);
    if (found) {
        int on = 0;
        for (int i = 0; i < 26; ++ i) if (press[i] == 1) ++ on;
        printf("%d", on);
        for (int i = 0; i < 26; ++ i) if (press[i] == 1) printf(" %c", i + 'A');
        printf("\n");
    } else {
        puts("-1");
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
        testCase();
    }
    return 0;
}

