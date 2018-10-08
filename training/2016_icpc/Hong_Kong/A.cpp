#include <bits/stdc++.h>

const int N = 110;

int n, m, k;
std::vector <int> e[N];
std::vector <std::vector <int>> ans;
std::vector <int> min[N][N];
bool vis[N];
int col1[N], col2[N];
int cnt1[N], cnt2[N];
void bfs(int s){
    memset(vis, 0, sizeof(vis));
    std::queue <int> queue;
    vis[s] = true;
    queue.push(s);
    min[s][s] = {s};
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        for (auto v : e[u]){
            if (!vis[v]){
                min[s][v] = min[s][u];
                min[s][v].push_back(v);
                vis[v] = true;
                queue.push(v);
            }
        }
    }
}

void print(){
    std::vector <int> vec;
    for (int i = 1; i <= n; ++ i){
        vec.push_back(col1[i]);
    }
    ans.push_back(vec);
}

void move(int u, int v, int type){
    for (int i = 0, sz = min[u][v].size(); i < sz - type; ++ i){
        if (col1[min[u][v][i]] == col1[min[u][v][i + 1]]){
            continue;
        }
        std::swap(col1[min[u][v][i]], col1[min[u][v][i + 1]]);
        print();
    }
}

void swap(int u, int v){
    move(u, v, 1);
    for (int i = (int) min[u][v].size() - 2; i > 0; -- i){
        if (col1[min[u][v][i]] == col1[min[u][v][i - 1]]){
            continue;
        }
        std::swap(col1[min[u][v][i]], col1[min[u][v][i - 1]]);
        print();
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &col1[i]);
        ++ cnt1[col1[i]];
    }
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &col2[i]);
        ++ cnt2[col2[i]];
    }
    print();
    for (int i = 0, u, v; i < m; ++ i){
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; ++ i){
        bfs(i);
    }
    for (int i = 1; i <= n; ++ i){
        for (int j = i + 1; j <= n; ++ j){
            min[i][j] = min[j][i];
            std::reverse(min[i][j].begin(), min[i][j].end());
        }
    }
    for (int i = 0; i < k; ++ i){
        while (cnt1[i] < cnt2[i]){
            if (!cnt1[i]){
                puts("Impossible");
                return 0;
            }
            for (int j = 1; j <= n; ++ j){
                if (col1[j] == i){
                    for (int k = 1; k <= n; ++ k){
                        if (cnt1[col1[k]] > cnt2[col1[k]]){
                            move(j, k, 2);
                            -- cnt1[col1[k]];
                            col1[k] = i;
                            ++ cnt1[i];
                            print();
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++ i){
        if (col1[i] == col2[i]) continue;
        for (int j = i + 1; j <= n; ++ j){
            if (col1[j] == col2[i]){
                swap(i, j);
                break;
            }
        }
    }
    assert(ans.size() <= 20000);
    for (auto &u : ans){
        for (int i = 0, sz = u.size(); i < sz; ++ i){
            printf("%d%c", u[i], " \n"[i == sz - 1]);
        }
    }
    return 0;
}
