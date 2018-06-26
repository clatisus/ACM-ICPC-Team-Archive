#include<bits/stdc++.h>

const int N = 100010;

int x[N], y[N], tp[N], a[N << 1], fa[N << 1];
std::set <int> set[N << 1];
int n;

int find(int u){
    return u == fa[u] ? u : (fa[u] = find(fa[u]));
}

bool unite(int u, int v){
    u = find(u), v = find(v);
    if (set[u].count(v)){
        return false;
    }
    if (set[u].size() > set[v].size()){
        std::swap(u, v);
    }
    for (auto w : set[u]){
        set[w].erase(u);
        set[w].insert(v);
        set[v].insert(w);
    }
    fa[u] = v;
    return true;
}

int main(){
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 0; i < n; ++ i){
        scanf("%d%d%d", &x[i], &y[i], &tp[i]);
        a[cnt ++] = x[i];
        a[cnt ++] = y[i];
    }
    std::sort(a, a + cnt);
    cnt = std::unique(a, a + cnt) - a;
    for (int i = 0; i < cnt; ++ i){
        fa[i] = i;
    }
    for (int i = 0; i < n; ++ i){
        int x1 = std::lower_bound(a, a + cnt, x[i]) - a;
        int y1 = std::lower_bound(a, a + cnt, y[i]) - a;
        if (x1 == y1){
            puts(tp[i] ? "YES" : "NO");
            continue;
        }
        if (tp[i]){
            puts(unite(x1, y1) ? "YES" : "NO");
        }
        else{
            if (find(x1) == find(y1)){
                puts("NO");
            }
            else{
                puts("YES");
                set[fa[x1]].insert(fa[y1]);
                set[fa[y1]].insert(fa[x1]);
            }
        }
    }
    return 0;
}
