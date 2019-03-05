#include <bits/stdc++.h>

const int N = 10010;

std::vector <int> e[N];
int x[N], y[N];
int deg[N], ans[N];
int vis[N];
int dfscnt;

double calc(int i, int j){
    return std::atan2(y[j] - y[i], x[j] - x[i]);
}

void dfs(int u, int col, int sumCol, std::vector <int> &vec){
    if (ans[u] != col || vis[u] == dfscnt) {
        return;
    }
    vis[u] = dfscnt;
    vec.push_back(u);
    for (auto v : e[u]){
        dfs(v, sumCol - col, sumCol, vec);
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        scanf("%d%d", &x[i], &y[i]);
    }
    for (int i = 0, u, v; i < m; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
        ++ deg[u], ++ deg[v];
    }
    for (int i = 1; i <= n; ++ i){
        std::sort(e[i].begin(), e[i].end(), [&](const int &p1, const int &p2){
            return calc(i, p1) < calc(i, p2);
        });
    }
    std::queue <int> queue;
    for (int i = 1; i <= n; ++ i){
        if (deg[i] <= 4){
            queue.push(i);
            vis[i] = 1;
        }
    }
    std::vector <int> vec;
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        vec.push_back(u);
        for (auto v : e[u]){
            if (!vis[v] && (-- deg[v]) <= 4){
                queue.push(v);
                vis[v] = 1;
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    while (!vec.empty()){
        int u = vec.back();
        vec.pop_back();
        bool vis1[5] = {};
        for (auto v : e[u]){
            if (ans[v]){
                vis1[ans[v]] = true;
            }
        }
        for (int i = 1; i <= 4; ++ i){
            if (!vis1[i]){
                ans[u] = i;
                break;
            }
        }
        if (ans[u]) continue;
        std::vector <int> vec1, vec2;
        for (auto v : e[u]){
            if (ans[v]){
                vec2.push_back(v);
            }
        }
        ++ dfscnt;
        dfs(vec2[0], ans[vec2[0]], ans[vec2[0]] + ans[vec2[2]], vec1);
        bool flag = false;
        for (auto v : vec1){
            if (v == vec2[2]){
                flag = true;
                break;
            }
        }
        if (!flag){
            int tmp = ans[vec2[0]];
            for (auto v : vec1){
                if (ans[v] == tmp) ans[v] = ans[vec2[2]];
                else if (ans[v] == ans[vec2[2]]) ans[v] = tmp;
            }
            ans[u] = tmp;
            continue;
        }
        vec1.clear();
        dfs(vec2[1], ans[vec2[1]], ans[vec2[1]] + ans[vec2[3]], vec1);
        int tmp = ans[vec2[1]];
        for (auto v : vec1){
            if (ans[v] == tmp) ans[v] = ans[vec2[3]];
            else if (ans[v] == ans[vec2[3]]) ans[v] = tmp;
        }
        ans[u] = tmp;
    }
    for (int i = 1; i <= n; ++ i){
        printf("%d\n", ans[i]);
    }
    return 0;
}
