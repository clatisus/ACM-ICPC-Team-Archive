#include <bits/stdc++.h>

const int max_N = 25;

using point = std::pair<int, int>;

point p[max_N] = {
    {0, 300},
    {0, 240},
    {20, 200},
    {0, 180},
    {30, 150},
    {60, 120},
    {0, 120},
    {40, 100},
    {80, 80},
    {120, 60},
    {0, 60},
    {50, 50},
    {100, 40},
    {150, 30},
    {200, 20},
    {0, 0},
    {60, 0},
    {120, 0},
    {180, 0},
    {240, 0},
    {300, 0},
}; //key points

int n = 7; //segments number

int inter[max_N][max_N]; //intersection number

int Sum;

bool w[max_N][max_N], vis[max_N];

void addEdge(int u, int v) { w[u][v] = w[v][u] = true; }
void delEdge(int u, int v) { w[u][v] = w[v][u] = false; }

void Count(int u, int s, int L) {
    if (Sum > 2005) return;
    if (w[u][s] && L >= 3) ++Sum;
    for (int v = 0; v < s; ++v) {
        if (vis[v] || !w[u][v]) continue;
        vis[v] = true;
        Count(v, s, L + 1);
        vis[v] = false;
    }
}

bool exist[2333];

int st[max_N], ed[max_N];

std::vector<std::pair<int, int>> ans[2333];

void save(int ss, int s) {
    exist[ss] = true;
    for (int i = 1; i < n - 1; ++i) {
        int l = 1e9, r = -1;
        for (int j = st[i]; j < ed[i]; ++j) {
            int x = inter[i][j], y = inter[i][j + 1];
            if (i && i != n - 1 && (x > s || y > s)) continue;
            l = std::min(l, j);
            r = std::max(r, j + 1);
        }
        if (r != -1) {
            ans[ss].push_back({inter[i][l], inter[i][r]});
        }
    }
}

void Calc() {
    Sum = 0;
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        Count(i, i, 1);
        if (Sum > 2003) return;
        int tmp = Sum / 2;
        if (exist[tmp]) continue;
        save(tmp, i);
    }
}

void dfs(int x) {
    if (x == n) return Calc();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = n - 2; j > i; --j) {
            if (j != n - 2) break; //WTF
            if ((!x || x == n - 1) && i) break; //WTF
            for (int k = i; k < j; ++k) addEdge(inter[x][k], inter[x][k + 1]);
            st[x] = i, ed[x] = j;
            dfs(x + 1);
            for (int k = i; k < j; ++k) delEdge(inter[x][k], inter[x][k + 1]);
        }
    }
}

inline void init() {
    for (int i = 0; i < n; ++i) {
        int t = i * (i - 1) / 2;
        for (int j = 0; j < i; ++j) {
            inter[i][j] = t++;
        }
        if (i) inter[i][i] = inter[i][i - 1] + i + 1;
        else inter[i][0] = 0;
        for (int j = i + 1; j < n - 1; ++j) {
            inter[i][j] = inter[i][j - 1] + j;
        }
    }
    //debug1
    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            printf("inter[%d][%d] = %d : (%d, %d)\n", i, j, inter[i][j], p[inter[i][j]].first, p[inter[i][j]].second);
        }
    }*/
    dfs(0);
}

point neg(point p) { return {-p.first, -p.second}; }

std::vector<std::pair<point, point>> res;

void add(point a, point b) { res.push_back({a, b}); }

void makeRes(int s, bool tp) {
    for (auto pr : ans[s]) {
        int a = pr.first, b = pr.second;
        if (tp) add(neg(p[a]), neg(p[b]));
        else add(p[a], p[b]);
    }
}

int main() {
    init();
    /*
    int cnt = 0;
    for (int i = 0; i <= 1000; ++i) {
        if (exist[i]) continue;
        bool flag = false;
        for (int a = 0; a < i; ++a)
            if (exist[a] && exist[i - a]) {
                flag = true;
                break;
            }
        if (flag) continue;
        printf("%d ", i);
        ++cnt;
    }
    printf("\ncnt = %d\n", cnt);
    */
    int k;
    scanf("%d", &k);
    if (exist[k]) {
        add(p[0], p[15]), add(p[15], p[20]);
        makeRes(k, false);
    } else {
        add(p[0], neg(p[0])), add(neg(p[20]), p[20]);
        for (int i = 1; i < k; ++i) {
            if (exist[i] && exist[k - i]) {
                makeRes(i, false);
                makeRes(k - i, true);
                break;
            }
        }
    }
    printf("%d\n", int(res.size()));
    for (auto prpr : res) {
        printf("%d %d %d %d\n", prpr.first.first, prpr.first.second, prpr.second.first, prpr.second.second);
    }
    return 0;
}
