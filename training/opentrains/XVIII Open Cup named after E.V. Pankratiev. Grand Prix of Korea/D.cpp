#include <bits/stdc++.h>

#define MAXN (1000010)

int n;
int link[MAXN][26], first[26];
char s[MAXN];

int main() {
    scanf("%s", s);
    n = strlen(s);
    for (int i = 0; i < 26; ++ i) {
        link[n - 1][i] = n;
    }
    for (int i = n - 2; ~i; -- i) {
        for (int j = 0; j < 26; ++ j) {
            link[i][j] = link[i + 1][j];
        }
        link[i][s[i + 1] - 'a'] = i + 1;
    }
    for (int i = n - 1; ~i; -- i) {
        first[s[i] - 'a'] = i;
    }
    int ans = 0;
    for (int i = 0, j; i < n - 1; ) {
        j = i + 1;
        int p = first[s[j] - 'a'];
        while (p <= i && j < n && link[p][s[j + 1] - 'a'] <= i) {
            ++ j;
            p = link[p][s[j] - 'a'];
        }
        ++ ans;
        i = j;
    }
    printf("%d\n", ans + 1);
    return 0;
}
