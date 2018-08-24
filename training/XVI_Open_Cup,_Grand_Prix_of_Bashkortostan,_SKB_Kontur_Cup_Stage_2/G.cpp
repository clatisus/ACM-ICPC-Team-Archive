#include <bits/stdc++.h>

#define MAXN (20)

int n;
int mat[MAXN][MAXN];
int tag[MAXN][MAXN];
int dir[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};
std::set<std::pair<int, int>> que;

bool in(int r, int c) { return 1 <= r && r <= n && 1 <= c && c <= n; }

void ask(int type, int r = 0, int c = 0) {
    if (type == 4) {
        printf("4\n");
        fflush(stdout);
        exit(0);
    }
    printf("%d %d %d\n", type, r, c);
    fflush(stdout);
    if (type == 1) {
        int m, u, v, w;
        scanf("%d", &m);
        while (m --) {
            scanf("%d%d%d", &u, &v, &w);
            mat[u][v] = w;
        }
    } else if (type == 3) {
        scanf("%*d%*d%*d%*d%*s");
    }
}

bool puttag(int x, int y, int e) {
    tag[x][y] = e;

    std::vector<std::pair<int, int>> trash;

    // add adjacent opened block into check list
    for (int i = 0; i < 8; ++i) {
        int dx = x + dir[i][0], dy = y + dir[i][1];
        if (!in(dx, dy) || mat[dx][dy] == -1 || que.count({dx, dy})) {
            continue;
        }
        que.insert({dx, dy});
        trash.push_back({dx, dy});
    }

    bool canput = true;
    int nx = -1, ny = -1, min_untag = INT_MAX;
    // for every opened block check neighbor unopened block
    for (auto p : que) {
        int u = p.first, v = p.second;

        int tag_mine = 0;
        int untagged = 0;
        for (int i = 0; i < 8; ++i) {
            int dx = u + dir[i][0], dy = v + dir[i][1];
            if (!in(dx, dy) || mat[dx][dy] != -1) continue;
            tag_mine += tag[dx][dy] == 1;
            untagged += tag[dx][dy] == -1;
        }

        if (untagged == 0) {
        // all unopened neighbors are tagged, and tag_mine wrong
            if (tag_mine != mat[u][v]) {
                canput = false;
                break;
            }
        } else if (min_untag > untagged) {
        // find the opened block with smallest untagged neighbor
            min_untag = untagged;
            nx = u;
            ny = v;
        }
    }

    if (canput && nx != -1 && ny != -1) {
        for (int i = 0; i < 8; ++i) {
            int dx = nx + dir[i][0], dy = ny + dir[i][1];
            if (!in(dx, dy) || mat[dx][dy] != -1 || tag[dx][dy] != -1) continue;
            if (!puttag(dx, dy, 1) && !puttag(dx, dy, 0)) {
                canput = false;
            }
            break;
        }
    }

    for (auto p : trash) que.erase(p);
    tag[x][y] = -1;

    return canput;
}

int main() {
    memset(mat, -1, sizeof(mat));
    memset(tag, -1, sizeof(tag));

    n = 16;
    int x, y;
    scanf("%d%d", &x, &y);
    ask(1, x, y);

    while (true) {
        bool flag = false;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (mat[i][j] == -1 && !puttag(i, j, 1)) {
                    ask(1, i, j);
                    flag = true;
                }
            }
        }
        if (!flag) break;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mat[i][j] == -1){
                ask(3, i, j);
            }
        }
    }
    ask(4);
    return 0;
}
