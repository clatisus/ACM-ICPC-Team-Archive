#include <bits/stdc++.h>

#define MAXN (110)

int n, m;
char s[MAXN][MAXN];
bool vis[MAXN][MAXN];
std::pair<int, int> pos[MAXN][MAXN];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s[i]);
    }
    std::queue<std::pair<int, int>> q;
    vis[0][0] = true;
    pos[0][0] = {0, 0};
    q.push({0, 0});

    std::vector<std::pair<int, int>> pat;
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        int x = u.first, y = u.second;
        int px = pos[x][y].first, py = pos[x][y].second;
        for (int i = 0; i < 4; ++i) {
            int xx = (x + dir[i][0] + n) % n;
            int yy = (y + dir[i][1] + m) % m;
            if (s[xx][yy] == '#') continue;
            int pxx = px + dir[i][0];
            int pyy = py + dir[i][1];
            if (!vis[xx][yy]) {
                vis[xx][yy] = true;
                pos[xx][yy] = {pxx, pyy};
                q.push({xx, yy});
            } else if (pxx != pos[xx][yy].first || pyy != pos[xx][yy].second) {
                int dx = (pxx - pos[xx][yy].first) / n;
                int dy = (pyy - pos[xx][yy].second) / m;
                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx *= -1;
                    dy *= -1;
                }
               // printf("dx = %d, dy = %d\n", dx, dy);
                pat.push_back({dx, dy});
            }
        }
    }

    std::sort(pat.begin(), pat.end());
    pat.erase(std::unique(pat.begin(), pat.end()), pat.end());

    int t;
    scanf("%d", &t);
    while (t --) {
        int x, y;
        scanf("%d%d", &x, &y);
        int xx = (x % n + n) % n;
        int yy = (y % m + m) % m;
        bool ans = vis[xx][yy];
        if (pat.empty()) {
            ans &= pos[xx][yy].first == x && pos[xx][yy].second == y;
        } else if (pat.size() == 1) {
            int dx = pat[0].first;
            int dy = pat[0].second;
            int nowx = (x - pos[xx][yy].first) / n;
            int nowy = (y - pos[xx][yy].second) / m;
            if (!dx) {
                std::swap(dx, dy);
                std::swap(nowx, nowy);
            }
            ans &= (nowx % dx == 0 && nowx / dx * dy == nowy);
        }
        printf(ans ? "yes\n" : "no\n");
    }
    return 0;
}

