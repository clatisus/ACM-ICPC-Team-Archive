#include <bits/stdc++.h>
 
const int max_N = (int) 1e5 + 21;
 
int n, m, len[4], fail[4][max_N], st[max_N], top, ans[4][max_N];
 
int vis[4][max_N][26];
 
char s[4][max_N], t[max_N];
 
int last[4][max_N][26], trans[4][max_N][26];
 
void init(int k) {
    fail[k][1] = 0;
    for (int i = 2; i <= len[k]; ++i) {
        int j = fail[k][i - 1];
        while (j && s[k][i] != s[k][j + 1]) j = fail[k][j];
        if (s[k][i] == s[k][j + 1]) ++j;
        fail[k][i] = j;
    }
    for (int i = 0; i < len[k]; ++i) {
        for (int j = 0; j < 26; ++j) {
            last[k][i][j] = last[k][fail[k][i]][j];
        }
        last[k][i][s[k][i + 1] - 'a'] = i;
        for (int j = 0; j < 26; ++j) {
            trans[k][i][j] = last[k][i][j];
            if (s[k][trans[k][i][j] + 1] - 'a' == j) ++trans[k][i][j];
        }
    }
    for (int j = 0; j < 26; ++j) trans[k][len[k]][j] = trans[k][fail[k][len[k]]][j];
    /*
    for (int i = 0; i <= len[k]; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (!trans[k][i][j]) continue;
            printf("trans[%d][%d][%d] = %d\n", k, i, j, trans[k][i][j]);
        }
    }
    */
}
 
int main() {
    scanf("%d", &n);
    int tmp = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i) {
        scanf("%s", s[i] + 1);
        len[i] = strlen(s[i] + 1);
        init(i);
        tmp = std::min(tmp, len[i]);
    }
    scanf("%s", t + 1);
    m = strlen(t + 1);
    printf("%d\n", tmp);
    st[top = 1] = 0;
    for (int i = 1; i <= m; ++i) {
        int res = 0x3f3f3f3f;
        if (t[i] == '-') {
            if (top > 1) --top;
            for (int j = 0; j < n; ++j) {
                ans[j][i] = ans[j][st[top]];
                res = std::min(res, len[j] - ans[j][i]);
            }
        } else {
            st[++top] = i;
            for (int j = 0; j < n; ++j) {
                ans[j][i] = trans[j][ans[j][i - 1]][t[i] - 'a'];
                res = std::min(res, len[j] - ans[j][i]);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
/*
2
abacaba
aa
aba-bb
 
1
aa
aa--a---
*/
