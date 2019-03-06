//
// Created by zzh on 2019/3/5.
//

#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
    int c;
    while (!isdigit(c = getchar()));
    x = c - '0';
    while (isdigit(c = getchar())) {
        x = x * 10 + c - '0';
    }
}

const int max_N = (1 << 20) + 21;

int T, n, m, dis[max_N], vis[max_N];

std::vector<int> vec[21];

char tmp[233];

void bfs(int u) {
    std::queue<int> Q;
    Q.push(u);
    dis[u] = 0;
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (int i = 0; i < n; ++i) {
            int v = u ^ (1 << i);
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                Q.push(v);
                if (vis[v]) {
                    vec[dis[v]].push_back(v);
                }
            }
        }
    }
}

void testCase() {
    read(n), read(m);
    for (int i = 0; i < (1 << n); ++i) {
        dis[i] = n + 1;
        vis[i] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        vec[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%s", tmp);
        int s = 0;
        for (int j = 0; j < n; ++j) {
            (s <<= 1) |= (tmp[j] == 'R');
        }
        vis[s] = 1;
        if (i == 1) {
            vec[0].push_back(s);
        }
    }
    int ans = 0;
    while (true) {
        int u = -1;
        for (int i = 0; i <= n; ++i) {
            while (!vec[i].empty() && !vis[vec[i].back()]) {
                vec[i].pop_back();
            }
            if (!vec[i].empty()) {
                ans += i;
                u = vec[i].back();
                vis[u] = 0;
                break;
            }
        }
        if (u == -1) break;
        bfs(u);
    }
    printf("%d\n", ans);
}

int main() {
    read(T);
    while (T--) {
        testCase();
    }
}
/*
2
5 4
LLLLL
LLLLR
RRRRL
RRRRR

2 3
LR
RL
RR
 */