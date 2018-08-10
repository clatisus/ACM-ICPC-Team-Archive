#include <bits/stdc++.h>

const int max_N = 35;

/*
int n, per[max_N], ord[2333], tot;

char s[max_N], t[max_N], ans[max_N];

std::unordered_map<int, int> map;

void output(int hash) {
    for (int i = 0; (i + 1) < n; ++i) {
        if (s[i] == s[i + 1]) ans[i] = '=';
        else {
            if ((hash >> i) & 1) ans[i] = '<';
            else ans[i] = '>';
        }
    }
    for (int i = 0; (i + 1) < n; ++i) {
        putchar(s[i]), putchar(' ');
        putchar(ans[i]), putchar(' ');
    }
    putchar(s[n - 1]), putchar('\n');
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    memcpy(t, s, n * sizeof(char));
    std::sort(t, t + n);
    tot = std::unique(t, t + n) - t;
    assert(tot == 10);
    for (int i = 0; i < tot; ++i) per[i] = i;
    do {
        for (int i = 0; i < tot; ++i) ord[t[i]] = per[i];
        int hash = 0;
        for (int i = 0; i + 1 < n; ++i) {
            if (s[i] == s[i + 1]) continue;
            if (ord[s[i]] < ord[s[i + 1]]) {
                hash |= (1 << i);
            }
        }
        ++map[hash];

    } while (std::next_permutation(per, per + tot));
    for (auto pr : map) {
        if (pr.second != 1) continue;
        return output(pr.first), 0;
    }
    return puts("Impossible"), 0;
}
*/

int n, ord[max_N], id[max_N];

char s[max_N], t[max_N];

int pre[15][1 << 10];

bool e[max_N][max_N], vis[15][1 << 10];

int idx(char c) {
    return c - 'a';
}

std::queue<std::pair<int, int>> Q;

void getAns(int x, int set, int len) {
    ord[x] = len;
    if (pre[x][set] == -1) return;
    getAns(pre[x][set], set ^ (1 << x), len - 1);
}

int main() {
    memset(pre, -1, sizeof(pre));
    scanf("%s", s);
    n = strlen(s);
    memcpy(t, s, n * sizeof(char));
    std::sort(t, t + n);
    int tot = std::unique(t, t + n) - t;
    t[tot] = '\0';
    // printf("t : %s\n", t);
    for (int i = 0; i < tot; ++i) id[idx(t[i])] = i;
    for (int i = 0; i + 1 < n; ++i) {
        int a = id[idx(s[i])];
        int b = id[idx(s[i + 1])];
        if (a == b) continue;
        e[a][b] = e[b][a] = true;
    }
    for (int i = 0; i < tot; ++i) {
        vis[i][1 << i] = true;
        Q.push({i, 1 << i});
    }
    while (!Q.empty()) {
        auto pr = Q.front();
        Q.pop();
        int x = pr.first, set = pr.second;
        for (int y = 0; y < tot; ++y)
            if (e[x][y] && !((set >> y) & 1)) {
                if (vis[y][set | (1 << y)]) continue;
                vis[y][set | (1 << y)] = true;
                pre[y][set | (1 << y)] = x;
                Q.push({y, set | (1 << y)});
            }
    }
    int goal = (1 << tot) - 1;
    for (int i = 0; i < tot; ++i) {
        if (vis[i][goal]) {
            getAns(i, goal, tot - 1);
            // for (int j = 0; j < tot; ++j) printf("%d ", ord[j]);
            // puts("");
            for (int j = 0; j + 1 < n; ++j) {
                putchar(s[j]), putchar(' ');
                if (s[j] == s[j + 1]) putchar('=');
                else {
                    if (ord[id[idx(s[j])]] < ord[id[idx(s[j + 1])]]) putchar('<');
                    else putchar('>');
                }
                putchar(' ');
            }
            puts(s + n - 1);
            return 0;
        }
    }
    return puts("Impossible"), 0;
}
