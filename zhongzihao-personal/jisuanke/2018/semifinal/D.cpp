#include<bits/stdc++.h>

const int N = 100010;
typedef std::pair <int, int> pii;

char s1[N], s2[N];
int a[N], b[N];
int fa[N], sz[N];

int find(int u){
    return fa[u] == u ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v){
    u = find(u), v = find(v);
    if (u == v) return;
    fa[u] = v;
}

int main(){
    int n;
    scanf("%d", &n);
    scanf("%s", s1);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    scanf("%s", s2);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &b[i]);
    }
    if (s1[0] == 'C' && s2[0] == 'C'){
        for (int i = 0; i < n; ++ i){
            if (a[i] != b[i]){
                puts("-1");
                return 0;
            }
        }
        puts("0");
        return 0;
    }
    if (s1[0] == 'C' && s2[0] == 'V'){
        for (int i = 0; i < n; ++ i){
            std::swap(a[i], b[i]);
        }
        std::swap(s1[0], s2[0]);
    }
    if (s1[0] == 'V' && s2[0] == 'C'){
        std::set <pii> set;
        for (int i = 0; i < n; ++ i){
            if (a[i] != b[i]) set.insert({a[i], b[i]});
        }
        printf("%d\n", (int) set.size());
        return 0;
    }
    for (int i = 1; i < N; ++ i){
        fa[i] = i;
    }
    for (int i = 0; i < n; ++ i){
        unite(a[i], b[i]);
    }
    for (int i = 0; i < N; ++ i){
        ++ sz[find(i)];
    }
    int ans = 0;
    for (int i = 0; i < N; ++ i){
        if (sz[i]){
            ans += sz[i] - 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
