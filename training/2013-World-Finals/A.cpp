//
// Created by zzh on 2019/3/7.
//

#include <bits/stdc++.h>

const int max_N = 121;

int n, st[max_N][max_N], ed[max_N][max_N], vis[max_N][max_N], map[max_N][max_N];

char s[max_N];

inline int decode(char a, char b) {
    if (a == '0') return 0;
    return (a - 'A' + 1) * 2 + (b == '+');
}

inline int opt(char a, char b) {
    if (a == '0') return 0;
    return (a - 'A' + 1) * 2 + (b != '+');
}

#define left(x) ((x) << 1)
#define right(x) left(x)
#define down(x) (left(x) | 1)
#define up(x) down(x)

void bfs(int rt) {
    std::queue<int> Q;
    for (int i = 0; i < max_N; ++i) {
        if (st[rt][i]) {
            Q.push(i);
            vis[rt][i] = 1;
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < max_N; ++i) {
            if (map[u][i] && !vis[rt][i]) {
                Q.push(i);
                vis[rt][i] = 1;
            }
        }
    }
    for (int i = 0; i < max_N; ++i) {
        if (ed[rt][i] && vis[rt][i]) {
            puts("unbounded");
            exit(0);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int k = 1; k <= n; ++k) {
        scanf("%s", s);

        std::vector<int> vec;
        for (int j = 0; j < 8; j += 2) {
            vec.push_back(decode(s[j], s[j + 1]));
        }

        for (int i = 0; i < 4; ++i) {
            char a = s[i << 1];
            char b = s[(i << 1) | 1];

            if (a == '0') continue;

            st[left(vec[i])][right(vec[(i + 2) % 4])] = 1;
            st[left(vec[i])][up(vec[(i + 1) % 4])] = 1;
            st[left(vec[i])][up(vec[(i + 3) % 4])] = 1;

            st[down(vec[i])][up(vec[(i + 2) % 4])] = 1;
            st[down(vec[i])][right(vec[(i + 1) % 4])] = 1;
            st[down(vec[i])][right(vec[(i + 3) % 4])] = 1;

            int tmp = opt(a, b);

            ed[left(vec[i])][right(tmp)] = 1;
            ed[down(vec[i])][up(tmp)] = 1;

            map[right(tmp)][right(vec[(i + 2) % 4])] = 1;
            map[right(tmp)][up(vec[(i + 1) % 4])] = 1;
            map[right(tmp)][up(vec[(i + 3) % 4])] = 1;

            map[up(tmp)][up(vec[(i + 2) % 4])] = 1;
            map[up(tmp)][right(vec[(i + 1) % 4])] = 1;
            map[up(tmp)][right(vec[(i + 3) % 4])] = 1;
        }
    }
    for (int i = 0; i < max_N; ++i) {
        bfs(i);
    }
    puts("bounded");
}