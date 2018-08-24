#include <bits/stdc++.h>

#define MAXN (3010)

int n;
int cntr[MAXN][26], numr[MAXN];
int cntc[MAXN][26], numc[MAXN];
bool visr[MAXN], visc[MAXN];
char s[MAXN][MAXN];
std::vector<std::pair<int, char> > ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i][j] == '?') continue;
            if (cntr[i][s[i][j] - 'a'] ++ == 0) ++ numr[i];
            if (cntc[j][s[i][j] - 'a'] ++ == 0) ++ numc[j];
        }
    }
    std::queue<int> queue;
    for (int i = 1; i <= n; ++i) {
        if (numr[i] <= 1) queue.push(i), visr[i] = true;
        if (numc[i] <= 1) queue.push(-i), visc[i] = true;
    }
    while (!queue.empty()) {
        int u = queue.front(); queue.pop();
        if (u > 0) {
            if (numr[u] == 0) ans.push_back({u, 'a'});
            else {
                for (int i = 0; i < 26; ++i) {
                    if (cntr[u][i]) {
                        ans.push_back({u, i + 'a'});
                        break;
                    }
                }
            }
            for (int j = 1; j <= n; ++j) {
                if (s[u][j] == '?' || visc[j]) continue;
                if (-- cntc[j][s[u][j] - 'a'] == 0) -- numc[j];
                if (numc[j] <= 1) {
                    queue.push(-j);
                    visc[j] = true;
                }
            }
        } else {
            u = -u;
            if (numc[u] == 0) ans.push_back({-u, 'a'});
            else {
                for (int i = 0; i < 26; ++i) {
                    if (cntc[u][i]) {
                        ans.push_back({-u, i + 'a'});
                        break;
                    }
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (s[i][u] == '?' || visr[i]) continue;
                if (-- cntr[i][s[i][u] - 'a'] == 0) -- numr[i];
                if (numr[i] <= 1) {
                    queue.push(i);
                    visr[i] = true;
                }
            }
        }
    }
    std::reverse(ans.begin(), ans.end());
    for (auto p : ans) {
        printf("%c %d %c\n", p.first > 0 ? 'h' : 'v', std::abs(p.first), p.second);
    }
    return 0;
}
