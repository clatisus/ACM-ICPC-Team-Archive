#include <bits/stdc++.h>

const int MAXN = 3000010;

int n, tot;

struct twoSat{   //for 2-sat MAXN is double large
    int col[MAXN], ncnt, scnt;
    std::vector<int> vec[MAXN];
    int dfn[MAXN], low[MAXN], bel[MAXN];
    std::stack<int> stack;
    void tarjan(int u){
        dfn[u] = low[u] = ++ncnt;
        stack.push(u);
        for(auto v : vec[u]){
            if(!dfn[v]){
                tarjan(v); low[u] = std::min(low[u], low[v]);
            } else if(!bel[v]) low[u] = std::min(low[u],dfn[v]);
        }
        if (low[u] != dfn[u]) return;
        int v; ++scnt;
        do {
            v = stack.top(); stack.pop(); bel[v] = scnt;
        } while(v != u);
    }
    bool solve(){
        memset(dfn, 0, sizeof(dfn));
        ncnt = scnt = 0;
        for (int i = 0; i < tot + tot; ++i) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }
        for (int i = 0; i < tot; ++i) {
            if (bel[i << 1] == bel[i << 1 | 1]) return false;
            col[i] = (bel[i << 1] < bel[i << 1 | 1]);
        }
        return true;
    }
} ts;

char s[MAXN];
int ss[MAXN], cnt;
int go[MAXN][2], par[MAXN], var[MAXN], rav[MAXN];
std::vector<int> node[MAXN];

void insert(char *s, int u) {
    for (int k = 0; k < 2; ++k) {
        int p = 0;
        for (int i = 0; s[i]; ++i) {
            int c = s[i] == '?' ? k : s[i] - '0';
            if (!go[p][c]) {
                go[p][c] = ++cnt;
                par[cnt] = p;
            }
            p = go[p][c];
        }
        node[p].push_back(u << 1 | (k ^ 1));
    }
}

int main() {
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s + ss[i]);
        int len = strlen(s + ss[i]);
        insert(s + ss[i], i);
        ss[i + 1] = ss[i] + len + 1;
    }
    // build graph
    tot = n;
    for (int u = 0; u <= cnt; ++u) {
        if (node[u].empty()) continue;
        int k = node[u].size();
        for (int i = 0; i < k; ++i) {
            ts.vec[node[u][i]].push_back((tot + i) << 1);
            ts.vec[(tot + i) << 1 | 1].push_back(node[u][i] ^ 1);
            if (i < k - 1) {
                ts.vec[(tot + i) << 1].push_back(node[u][i + 1] ^ 1);
                ts.vec[node[u][i + 1]].push_back((tot + i) << 1 | 1);

                ts.vec[(tot + i) << 1].push_back((tot + i + 1) << 1);
                ts.vec[(tot + i + 1) << 1 | 1].push_back((tot + i) << 1 | 1);
            }
        }
        var[u] = (tot + k - 1) << 1;
        rav[u] = var[u] | 1;

        for (int v = par[u]; v; v = par[v]) {
            if (node[v].empty()) continue;
            ts.vec[var[u]].push_back(rav[v]);
            ts.vec[var[v]].push_back(rav[u]);
        }

        tot += k;
    }
    if (!ts.solve()) {
        puts("NO");
    } else {
        puts("YES");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; (s + ss[i])[j]; ++j) {
                if ((s + ss[i])[j] == '?') {
                    (s + ss[i])[j] = ts.col[i] + '0';
                }
            }
            printf("%s\n", s + ss[i]);
        }
    }
    return 0;
}
