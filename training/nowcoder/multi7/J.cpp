#include <bits/stdc++.h>
 
#define MAXN (1010)
#define ll long long
 
int n, m;
char s[MAXN][MAXN];
int up[MAXN][MAXN], left[MAXN][MAXN], sumleft[MAXN][MAXN];
bool vis[52];
int stack[100];
 
int getid(char t) {
    return isupper(t) ? t - 'A' : t - 'a' + 26;
}
 
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
    }
    for (int j = 1; j <= m; ++j) {
        memset(vis, 0, sizeof(vis));
        int l = 1;
        vis[getid(s[1][j])] = true;
        for (int i = 1; i <= n; ++i) {
            while (l < i && vis[getid(s[i][j])]) {
                vis[getid(s[l][j])] = false;
                ++ l;
            }
            vis[getid(s[i][j])] = true;
            up[i][j] = i - l + 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        int l = 1;
        vis[getid(s[i][1])] = true;
        for (int j = 1; j <= m; ++j) {
            while (l < j && vis[getid(s[i][j])]) {
                vis[getid(s[i][l])] = false;
                ++ l;
            }
            vis[getid(s[i][j])] = true;
            left[i][j] = j - l + 1;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int top = 0;
        for (int j = 1; j <= m; ++j) {
            int t = up[i][j];
            for (int k = 0; k < top; ++k) stack[k]++;
            for (int k = i; k > i - t; --k) {
                stack[i - k] = std::min(stack[i - k], left[k][j]);
                if (k != i) {
                    stack[i - k] = std::min(stack[i - k], stack[i - k - 1]);
                }
                if (stack[i - k] == 0) stack[i - k] = 1;
                ans += stack[i - k];
            }
            if (top < t) top = t;
            else {
                while (top > t) stack[--top] = 0;
            }
        }
        while (top) {
            stack[--top] = 0;
        }
    }
    printf("%lld\n", ans);
 
    return 0;
}
