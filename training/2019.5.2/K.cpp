//
// Created by nonsensetime on 19-5-2.
//

#include <bits/stdc++.h>

const int MAXN = 2010;

int h[4], w[4], x[4], y[4];
std::pair<int, int> tu[4];
char m[4][MAXN][MAXN];

char mat[MAXN][MAXN];

void merge(int a, int b) {
    if (tu[a].first == -1 || tu[b].first == -1)
        return;
    memset(mat, 0, sizeof(mat));
    x[a] = y[a] = 0;
    x[b] = tu[a].first - tu[b].first; y[b] = tu[a].second - tu[b].second;
    if (x[b] < 0) x[a] = -x[b], x[b] = 0;
    if (y[b] < 0) y[a] = -y[b], y[b] = 0;
    for (int i = 0; i < h[a]; ++i) {
        for (int j = 0; j < w[a]; ++j) {
            mat[i + x[a]][j + y[a]] = m[a][i][j];
        }
    }
    for (int i = 0; i < h[b]; ++i) {
        for (int j = 0; j < w[b]; ++j) {
            mat[i + x[b]][j + y[b]] ^= m[b][i][j];
        }
    }
}

// m[a] xor m[b] == m[c] ?
bool check(int a, int b, int c) {
    if (tu[a].first == -1 || tu[b].first == -1) {
        return false;
    }

    merge(a, b);

    h[3] = w[3] = MAXN;
    memcpy(m[3], mat, sizeof(mat));
    tu[3] = {-1, -1};

    for (int i = 0; i < h[3]; ++i) {
        for (int j = 0; j < w[3]; ++j) {
            if (m[3][i][j]) {
                tu[3] = {i, j};
                break;
            }
        }
        if (tu[3].first != -1) break;
    }
    if ((tu[3].first == -1 || tu[c].first == -1) && tu[3].first != tu[c].first) {
        return false;
    }
    merge(c, 3);

    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            if (mat[i][j]) {
                return false;
            }
        }
    }

    printf("YES\n");
    if (c == 2) {
        printf("%d %d\n", y[b] - y[a], x[b] - x[a]);
    } else if (c == 1) {
        printf("%d %d\n", y[c] - y[3] - y[a], x[c] - x[3] - x[a]);
    } else {
        printf("%d %d\n", y[3] - y[c] + y[a], x[3] - x[c] + x[a]);
    }
    return true;
}

int main() {
    freopen("kids.in", "r", stdin);
    freopen("kids.out", "w", stdout);
    for (int k = 0; k < 3; ++k) {
        scanf("%d%d", h + k, w + k);
        tu[k] = {-1, -1};
        for (int i = 0; i < h[k]; ++i) {
            scanf("%s", m[k][i]);
            for (int j = 0; j < w[k]; ++j) {
                m[k][i][j] = m[k][i][j] == '*' ? 1 : 0;
                if (m[k][i][j] && tu[k].first == -1) {
                    tu[k] = {i, j};
                }
            }
        }
    }
    if (check(0, 1, 2) || check(0, 2, 1) || check(1, 2, 0)) {
        return 0;
    }
    printf("NO");
    return 0;
}
