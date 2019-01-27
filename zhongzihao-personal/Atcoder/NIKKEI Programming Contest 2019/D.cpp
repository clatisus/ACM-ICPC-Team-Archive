#include<bits/stdc++.h>

const int N = 100010;

int fa[N];
std::vector <int> e[N];
int deg[N];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < n + m - 1; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
        ++ deg[v];
    }
    std::queue <int> queue;
    for (int i = 1; i <= n; ++ i){
        if (!deg[i]){
            queue.push(i);
        }
    }
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        for (auto v : e[u]){
            -- deg[v];
            if (!deg[v]){
                fa[v] = u;
                queue.push(v);
            }
        }
    }
    for (int i = 1; i <= n; ++ i){
        printf("%d\n", fa[i]);
    }
    return 0;
}
