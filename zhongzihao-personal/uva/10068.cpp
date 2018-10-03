#include<bits/stdc++.h>

const int N = 30;
const int M = 10010;
const int BIT = 12;
typedef std::pair <int, int> pii;

char s[N][N];
int n, m;
int dis[N][N][N][N];
pii dispre[N][N][N][N];
int dp[1 << BIT][BIT], pre[1 << BIT][BIT];
bool vis[N][N];
int p[BIT], c[BIT];
int x[BIT], y[BIT];
char ans[M];

bool check(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m && s[x][y] != '#';
}

void bfs(int sx, int sy){
    memset(vis, 0, sizeof(vis));
    std::queue <pii> queue;
    queue.push({sx, sy});
    vis[sx][sy] = true;
    dis[sx][sy][sx][sy] = 0;
    while (!queue.empty()){
        pii p = queue.front();
        queue.pop();
        int x = p.first, y = p.second;
        int move[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < 4; ++ i){
            int nx = x + move[i][0], ny = y + move[i][1];
            if (check(nx, ny) && !vis[nx][ny]){
                dis[sx][sy][nx][ny] = dis[sx][sy][x][y] + 1;
                vis[nx][ny] = true;
                dispre[sx][sy][nx][ny] = {x, y};
                queue.push({nx, ny});
            }
        }
    }
}

void write(int &sx, int &sy, int ex, int ey, int &sz){
    while (sx != ex || sy != ey){
        pii p = dispre[ex][ey][sx][sy];
        if (sx - p.first == 1){
            ans[sz ++] = 'N';
        }
        if (sx - p.first == -1){
            ans[sz ++] = 'S';
        }
        if (sy - p.second == 1){
            ans[sz ++] = 'W';
        }
        if (sy - p.second == -1){
            ans[sz ++] = 'E';
        }
        sx = p.first, sy = p.second;
    }
}

void solve(){
    for (int i = 0; i < n; ++ i){
        scanf("%s", s[i]);
    }
    memset(dis, -1, sizeof(dis));
    int sx, sy, ex, ey;
    int cnt = 0;
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            if (s[i][j] != '#'){
                bfs(i, j);
            }
            if (s[i][j] == 'S'){
                sx = i, sy = j;
            }
            if (s[i][j] == 'T'){
                ex = i, ey = j;
            }
            if (s[i][j] == '*'){
                x[cnt] = i;
                y[cnt ++] = j;
            }
        }
    }
    int v;
    scanf("%d", &v);
    for (int i = 0; i < cnt; ++ i){
        scanf("%d%d", &p[i], &c[i]);
    }
    if (!cnt){
        printf("Minimum energy required = %d cal\n", dis[sx][sy][ex][ey] * v);
        int sz = 0, nowx = ex, nowy = ey;
        write(nowx, nowy, sx, sy, sz);
        ans[sz] = '\0';
        std::map <int, int> map;
        map['S'] = 'N', map['N'] = 'S';
        map['E'] = 'W', map['W'] = 'E';
        std::reverse(ans, ans + sz);
        for (int i = 0; i < sz; ++ i){
            if (map.count(ans[i])){
                ans[i] = map[ans[i]];
            }
        }
        puts(ans);
        puts("");
        return;
    }
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i < 1 << cnt; ++ i){
        if (__builtin_popcount(i) == 1){
            for (int j = 0; j < cnt; ++ j){
                if (i >> j & 1){
                    if (!~dis[sx][sy][x[j]][y[j]]){
                        puts("The hunt is impossible.\n");
                        return;
                    }
                    dp[i][j] = dis[sx][sy][x[j]][y[j]] * v;
                    break;
                }
            }
            continue;
        }
        int sum = 0;
        for (int j = 0; j < cnt; ++ j){
            if (i >> j & 1){
                sum += c[j];
            }
        }
        for (int j = 0; j < cnt; ++ j){
            if (i >> j & 1){
                for (int k = 0; k < cnt; ++ k){
                    if ((i >> k & 1) && j != k){
                        if (!~dis[x[k]][y[k]][x[j]][y[j]]){
                            puts("The hunt is impossible.\n");
                            return;
                        }
                        int value = dp[i ^ 1 << j][k] + (sum - c[j] + v) * dis[x[k]][y[k]][x[j]][y[j]];
                        if (!~dp[i][j] || dp[i][j] > value){
                            dp[i][j] = value;
                            pre[i][j] = k;
                        }
                    }
                }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < cnt; ++ i){
        sum += c[i];
    }
    int minsit = -1, min;
    for (int i = 0; i < cnt; ++ i){
        if (!~dis[x[i]][y[i]][ex][ey]){
            puts("The hunt is impossible.\n");
            return;
        }
        int value = dp[(1 << cnt) - 1][i] + (sum + v) * dis[x[i]][y[i]][ex][ey];
        if (!~minsit || min > value){
            min = value;
            minsit = i;
        }
    }
    for (int i = 0; i < cnt; ++ i){
        min += p[i];
    }
    printf("Minimum energy required = %d cal\n", min);
    int sz = 0, nowx = ex, nowy = ey, now = minsit;
    write(nowx, nowy, x[now], y[now], sz);
    ans[sz ++] = 'P';
    int bit = (1 << cnt) - 1;
    while (__builtin_popcount(bit) > 1){
        int prev = pre[bit][now];
        write(nowx, nowy, x[prev], y[prev], sz);
        ans[sz ++] = 'P';
        bit ^= 1 << now;
        now = prev;
    }
    write(nowx, nowy, sx, sy, sz);
    ans[sz] = '\0';
    std::map <int, int> map;
    map['S'] = 'N', map['N'] = 'S';
    map['E'] = 'W', map['W'] = 'E';
    std::reverse(ans, ans + sz);
    for (int i = 0; i < sz; ++ i){
        if (map.count(ans[i])){
            ans[i] = map[ans[i]];
        }
    }
    puts(ans);
    puts("");
}

int main(){
    int cnt = 0;
    while (scanf("%d%d", &n, &m), n || m){
        ++ cnt;
        printf("Hunt #%d\n", cnt);
        solve();
    }    
    return 0;
}
