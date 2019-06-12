#include <bits/stdc++.h>

const int N = 2010;

int mat[N][N];
char s[N];
bool dpl[N][N], dpr[N][N];
/*
 * set1: dpl[i]
 * set2: dpl[j]
 * set3: dpr[i]
 * set4: dpr[j]
 */
std::bitset<N> set1[N], set2[N], set3[N], set4[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < i; ++j) {
            mat[i][j] = s[j] - '0';
            mat[j][i] = 1 - mat[i][j];
        }
    }
    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i < n; ++i) {
            int j = i + len - 1;
            if (j >= n) {
                continue;
            }
            if (len == 1) {
                dpl[i][j] = dpr[i][j] = true;
            } else {
                if ((set1[i] & set2[j]).any() || ((set1[i] << 1 & set4[j]).any() && mat[i][j])) {
                    dpl[i][j] = true;
                }
                if ((set4[j] & set3[i]).any() || ((set4[j] >> 1 & set1[i]).any() && mat[j][i])) {
                    dpr[i][j] = true;
                }
            }
            set1[i][j] = set2[j][i] = dpl[i][j];
            set3[i][j] = set4[j][i] = dpr[i][j];
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cnt += dpl[i][n - 1] && dpr[0][i];
    }
    printf("%d\n", cnt);
    return 0;
}
