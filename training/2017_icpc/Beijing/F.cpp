#include <bits/stdc++.h>

const int max_N = 233;

int n, tot;

char a[max_N][max_N], b[max_N * max_N], ans[max_N][max_N];

void getEven() {
    b[tot = 1] = a[1][1];
    int x = 1, y = 1, tp = 0;
    while (true) {
        if (x == n && y == 1) {
            break;
        }
        if (!tp && y == n) {
            tp ^= 1;
        } else if (tp && x == n) {
            tp ^= 1;
        }
        if (tp) {
            assert(x < n);
            b[++tot] = a[++x][y];
            while (x > 1 && y < n) {
                b[++tot] = a[--x][++y];
            }
        } else {
            assert(y < n);
            b[++tot] = a[x][++y];
            while (x < n && y > 1) {
                b[++tot] = a[++x][--y];
            }
        }
        tp ^= 1;
    }
    tp = 0;
    while (true) {
        if (x == n && y == n) {
            break;
        }
        if (!tp && y == n) {
            tp ^= 1;
        } else if (tp && x == n) {
            tp ^= 1;
        }
        if (tp) {
            assert(x < n);
            b[++tot] = a[++x][y];
            while (x < n && y > 1) {
                b[++tot] = a[++x][--y];
            }
        } else {
            assert(y < n);
            b[++tot] = a[x][++y];
            while (x > 1 && y < n) {
                b[++tot] = a[--x][++y];
            }
        }
        tp ^= 1;
    }
}

void getB() {
    if (~n & 1) return getEven();
    b[tot = 1] = a[1][1];
    int x = 1, y = 1, tp = 0;
    while (true) {
        if (x == 1 && y == n) {
            break;
        }
        if (!tp && y == n) {
            tp ^= 1;
        } else if (tp && x == n) {
            tp ^= 1;
        }
        if (tp) {
            assert(x < n);
            b[++tot] = a[++x][y];
            while (x > 1 && y < n) {
                b[++tot] = a[--x][++y];
            }
        } else {
            assert(y < n);
            b[++tot] = a[x][++y];
            while (x < n && y > 1) {
                b[++tot] = a[++x][--y];
            }
        }
        tp ^= 1;
    }
    tp = 1;
    while (true) {
        if (x == n && y == n) {
            break;
        }
        if (!tp && y == n) {
            tp ^= 1;
        } else if (tp && x == n) {
            tp ^= 1;
        }
        if (tp) {
            assert(x < n);
            b[++tot] = a[++x][y];
            while (x < n && y > 1) {
                b[++tot] = a[++x][--y];
            }
        } else {
            assert(y < n);
            b[++tot] = a[x][++y];
            while (x > 1 && y < n) {
                b[++tot] = a[--x][++y];
            }
        }
        tp ^= 1;
    }
    // printf("tot = %d\n", tot);
    // puts(b + 1);
}

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void getAns() {
    memset(ans, 0, sizeof(ans));
    int x = 1, y = 1;
    ans[x][y] = b[1];
    int d = 0;
    // printf("(%d, %d)\n", x, y);
    for (int cur = 2; cur <= tot; ++cur) {
        int nx = x + dir[d][0], ny = y + dir[d][1];
        if (!nx || !ny || nx > n || ny > n || ans[nx][ny]) {
            d = (d + 1) % 4;
            nx = x + dir[d][0], ny = y + dir[d][1];
        }
        ans[x = nx][y = ny] = b[cur];
        // printf("(%d, %d)\n", x, y);
    }
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%s", a[i] + 1);
        }
        getB();
        getAns();
        for (int i = 1; i <= n; ++i) {
            ans[i][n + 1] = '\0';
            puts(ans[i] + 1);
        }
    }
    return 0;
}

