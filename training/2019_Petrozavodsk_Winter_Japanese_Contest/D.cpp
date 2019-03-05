//
// Created by zzh on 2019/3/1.
//

#include <bits/stdc++.h>

using pair = std::pair<int, int>;

const int max_N = 4000 + 21;

int n, m, nxt[4][max_N], tmp[2], dis[max_N][max_N];

char s[2][max_N];

inline pair next(int i, int j, int d) {
    return {nxt[d][i], nxt[d + 2][j]};
}

int main() {
    scanf("%s%s", s[0], s[1]);
    n = strlen(s[0]);
    m = strlen(s[1]);
    tmp[0] = tmp[1] = n;
    nxt[0][n] = nxt[1][n] = n + 1;
    nxt[0][n + 1] = nxt[1][n + 1] = n + 1;
    for (int i = n - 1; ~i; --i) {
        tmp[s[0][i] - '0'] = i;
        nxt[0][i] = tmp[0] + 1;
        nxt[1][i] = tmp[1] + 1;
    }
    tmp[0] = tmp[1] = m;
    nxt[2][m] = nxt[3][m] = m + 1;
    nxt[2][m + 1] = nxt[3][m + 1] = m + 1;
    for (int i = m - 1; ~i; --i) {
        tmp[s[1][i] - '0'] = i;
        nxt[2][i] = tmp[0] + 1;
        nxt[3][i] = tmp[1] + 1;
    }
    dis[n + 1][m + 1] = 0;
    for (int i = n + 1; ~i; --i) {
        for (int j = m + 1; ~j; --j) {
            if (i == n + 1 && j == m + 1) continue;
            dis[i][j] = 0x3f3f3f3f;
            for (int d = 0; d < 2; ++d) {
                auto tmp = next(i, j, d);
                dis[i][j] = std::min(dis[i][j], dis[tmp.first][tmp.second] + 1);
            }
        }
    }
    pair cur = {0, 0};
    while (cur.first < n + 1 || cur.second < m + 1) {
        for (int d = 0; d < 2; ++d) {
            auto tmp = next(cur.first, cur.second, d);
            if (dis[tmp.first][tmp.second] + 1 == dis[cur.first][cur.second]) {
                putchar('0' + d);
                cur = tmp;
                break;
            }
        }
    }
}
/*
 0101
 1100001

 101010101
 010101010

 11111111
 00000000
 */