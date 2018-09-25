#include <bits/stdc++.h>

#define MAX (30)
#define DEBUG (1)

int n;
int mat[MAX][MAX << 1];
bool tam[8][MAX][MAX << 1];
int l[] = {0, 1, 1, 0, 0, -5, -4, -4, -3, -3, -3, -4, -4, -5, 0, 0, 1, 1};
int r[] = {0, 1, 2, 2, 3,  7,  7,  6,  6,  5,  6,  6,  7,  7, 3, 2, 2, 1};
int op[] = {0, 2, 1, 4, 3, 6, 5};

void go(int t, int x, int y, int &tx, int &ty) {
    if (t == 0) tx = x, ty = y - 1;
    if (t == 1) tx = x, ty = y + 1;
    if (t == 2) tx = x - 1, ty = y - !(x & 1);
    if (t == 3) tx = x - 1, ty = y + (x & 1);
    if (t == 4) tx = x + 1, ty = y - !(x & 1);
    if (t == 5) tx = x + 1, ty = y + (x & 1);
}

bool valid(int t, int x, int y) {
    if (!(1 <= x && x <= 17)) return false;
    if (!(l[x] <= y && y <= r[x])) return false;
    for (int i = 1; i <= 6; ++i) {
        if (i == t || i == op[t]) continue;
        if (tam[i][x][y + MAX]) return false;
    }
    //if (mat[x][y + MAX]) return false;
    return true;
}

void getLoc(int i, int j, int &ti, int &tj) {
    ti = i;
    tj = j + l[i] - 1;
}

std::pair<int, int> getCol(int i, int j) {
    return {i, j + 1 - l[i]};
}

void print(int x, int y) {
    if (!DEBUG) return;
    auto u = getCol(x, y);
    printf("print [%d, %d]\n", u.first, u.second);
}

void init() {
    memset(mat, 0, sizeof(mat));
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= i; ++j) {
            int x, y;
            getLoc(i, j, x, y);
            mat[x][y + MAX] = 1;
            tam[1][x][y + MAX] = true;
        }
        for (int j = 5 - i; j; --j) {
            int x, y;
            getLoc(i + 4, j, x, y);
            mat[x][y + MAX] = 6;
            tam[6][x][y + MAX] = true;
            getLoc(i + 4, j + 9, x, y);
            mat[x][y + MAX] = 4;
            tam[4][x][y + MAX] = true;
        }
        for (int j = 1; j <= i; ++j) {
            int x, y;
            getLoc(i + 9, j, x, y);
            mat[x][y + MAX] = 3;
            tam[3][x][y + MAX] = true;
            getLoc(i + 9, j + 9, x, y);
            mat[x][y + MAX] = 5;
            tam[5][x][y + MAX] = true;
        }
        for (int j = 5 - i; j; --j) {
            int x, y;
            getLoc(i + 13, j, x, y);
            mat[x][y + MAX] = 2;
            tam[2][x][y + MAX] = true;
        }
    }
}

bool check(std::string s) {
    int n = s.length();
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        int turn = 0;
        for (int i = 1; i <= n; ++i) {
            turn = turn % 6 + 1;
            static char s[10];
            int tx, ty, op;
            scanf("%d%d%s", &tx, &ty, s);
            int x, y;
            getLoc(tx, ty, x, y);
            if (!mat[x][y + MAX] || mat[x][y + MAX] != turn) continue;
            if (s[0] == 'L') op = 0;
            if (s[0] == 'R') op = 1;
            if (s[0] == 'U' && s[1] == 'L') op = 2;
            if (s[0] == 'U' && s[1] == 'R') op = 3;
            if (s[0] == 'L' && s[1] == 'L') op = 4;
            if (s[0] == 'L' && s[1] == 'R') op = 5;
            std::string str;

            tx = -1, ty = -1;
            int nx, ny;
            go(op, x, y, nx, ny);
            if (!valid(mat[x][y + MAX], nx, ny)) continue;
            if (!mat[nx][ny + MAX]) tx = nx, ty = ny;
            bool pass = false;
            while (true) {
                if (mat[nx][ny + MAX]) {
                    pass = true;
                    str += '1';
                } else {
                    str += '0';
                }
                int _x, _y;
                go(op, nx, ny, _x, _y);
                nx = _x, ny = _y;
                if (!valid(mat[x][y + MAX], nx, ny)) break;
                if (!mat[nx][ny + MAX] && pass && check(str)) {
                    tx = nx, ty = ny;
                }
            }

            if (tx == -1) continue;
            mat[tx][ty + MAX] = mat[x][y + MAX];
            mat[x][y + MAX] = 0;

            //auto tmp = getCol(tx, ty);
           // printf("%d %d\n", tmp.first, tmp.second);
        }

        std::vector<std::pair<int, int>> vec[8];
        for (int i = 1; i <= 17; ++i) {
            for (int j = l[i]; j <= r[i]; ++j) {
                if (!mat[i][j + MAX]) continue;
                vec[mat[i][j + MAX]].push_back(getCol(i, j));
            }
        }
        for (int i = 1; i <= 6; ++i) {
            std::sort(vec[i].begin(), vec[i].end());
           // printf("sz[%d] = %d\n", i, vec[i].size());
            //continue;
            for (int j = 0; j < 10; ++j) {
                printf("%d %d%c", vec[i][j].first, vec[i][j].second, " \n"[j == 9]);
            }
        }
    }
    return 0;
}

