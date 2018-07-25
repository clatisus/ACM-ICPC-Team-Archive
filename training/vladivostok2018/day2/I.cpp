#include <bits/stdc++.h>

#define MAXN (100010)
#define ll long long

int n, m;
int c[MAXN];
int siz[MAXN], son[MAXN], p[MAXN], dep[MAXN];
int head[MAXN];
std::vector<std::pair<int, int> > stack[MAXN];
std::vector<std::pair<int, int> > query;
std::vector<int> vec[MAXN];
int bit[MAXN];
ll total;

void dfs1(int x) {
    siz[x] = 1;
    son[x] = 0;
    for (auto &y : vec[x]) {
        if (y == p[x]) continue;
        p[y] = x;
        dep[y] = dep[x] + 1;
        dfs1(y);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) son[x] = y;
    }
}

void dfs2(int x, int c) {
    head[x] = c;
    if(son[x]) dfs2(son[x], c);
    for (auto &y : vec[x]) {
        if (head[y]) continue;
        dfs2(y, y);
    }
    if (!stack[c].empty() && stack[c].rbegin() -> first == ::c[x]) {
        ++ stack[c].rbegin() -> second;
    } else {
        stack[c].push_back({::c[x], 1});
    }
}

int print(int u) {
    u = head[u];
    for (auto p : stack[u]) {
        printf("stack[%d] = (%d, %d)\n", u, p.first, p.second);
    }
}

ll solve(int u, int v) {
    std::vector<std::pair<int, int> > vector;
    while (u) {
        std::vector<std::pair<int, int> > tmp;
        int c = head[u];
        int d = dep[c] - 1;
        
        while (d + stack[c].rbegin() -> second < dep[u]) {
            d += stack[c].rbegin() -> second;
            tmp.push_back(*stack[c].rbegin());
            stack[c].pop_back();
            
            
            //printf("%d %d\n", stack[c].rbegin() -> first, stack[c].rbegin() -> second);
        }
        if (dep[u] - d) {
            tmp.push_back({stack[c].rbegin() -> first, dep[u] - d});
            stack[c].rbegin() -> second -= dep[u] - d;
        }
        if (!stack[c].rbegin() -> second) stack[c].pop_back();
        if (!stack[c].empty() && stack[c].rbegin() -> first == ::c[v]) {
            stack[c].rbegin() -> second += dep[u] - dep[c] + 1;
        } else {
            stack[c].push_back({::c[v], dep[u] - dep[c] + 1});
        }
        //print(u);
        u = p[c];
        
        std::reverse(tmp.begin(), tmp.end());
        for (auto p : tmp) vector.push_back(p);
        
    }
    
    ll ret = 0;
    std::reverse(vector.begin(), vector.end());
    for (auto &u : vector) {
        //printf("vector = (%d, %d)\n", u.first, u.second);
        ll tmp = total;
        total += u.second;
        for (int i = u.first; i; i -= i & (- i)) tmp -= bit[i];
        for (int i = u.first; i <= m; i += i & (- i)) bit[i] += u.second;
        ret += tmp * u.second;
    }
    for (auto &u : vector) {
        for (int i = u.first; i <= m; i += i & (- i)) bit[i] -= u.second;
    }
    total = 0;
    return ret;
}

int main() {
    scanf("%d", &n);
    std::vector<int> vv;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", c + i);
        vv.push_back(c[i]);
    }
    std::sort(vv.begin(), vv.end());
    vv.erase(std::unique(vv.begin(), vv.end()), vv.end());
    m = vv.size();
    
    for (int i = 1; i <= n; ++ i) {
        c[i] = std::lower_bound(vv.begin(), vv.end(), c[i]) - vv.begin() + 1;
    }
    
    for (int i = 1; i < n; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
        query.push_back({u, v});
    }
    dfs1(1); dfs2(1, 1);
    for (auto &p : query) {
        int u = p.first, v = p.second;
        printf("%lld\n", solve(u, v));
    }
    return 0;
}
