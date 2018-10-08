#include<bits/stdc++.h>

const int N = 210;
typedef std::pair <int, int> pii;

std::vector <int> e[N * N];
std::vector <pii> ans;
int n, m;
bool vis[N * N];

int encode(int x, int y){
    return x * m + y;
}

pii decode(int x){
    return {x / m, x % m};
}

void dfs(int u){
    if (vis[u]) return;
    vis[u] = true;
    ans.push_back(decode(u));
    for (auto v : e[u]){
        dfs(v);
    }
}

void addedge(int x1, int y1, int x2, int y2){
    int u = encode(x1, y1), v = encode(x2, y2);
    e[u].push_back(v);
    e[v].push_back(u);
}

int main(){
    scanf("%d%d", &n, &m);
    bool flag = false;
    if (n > m){
        std::swap(n, m);
        flag = true;
    }
    if (n == 1){
        if (m < 10){
            if (m != 5){
                puts("-1");
                return 0;
            }
            addedge(0, 0, 0, 2);
            addedge(0, 0, 0, 3);
            addedge(0, 1, 0, 3);
            addedge(0, 1, 0, 4);
            addedge(0, 2, 0, 4);
        }
        else{
            addedge(0, 0, 0, 2);
            addedge(0, 0, 0, 3);
            addedge(0, 1, 0, 3);
            addedge(0, 1, 0, 4);
            addedge(0, 2, 0, 5);
            for (int i = 4; i < m - 6; ++ i){
                addedge(0, i, 0, i + 2);
            }
            addedge(0, m - 1, 0, m - 3);
            addedge(0, m - 1, 0, m - 4);
            addedge(0, m - 2, 0, m - 4);
            addedge(0, m - 2, 0, m - 5);
            addedge(0, m - 3, 0, m - 6);
        }
    }
    else if (n == 2){
        if (m == 2){
            puts("-1");
            return 0;
        }
        addedge(0, 0, 1, 1);
        addedge(0, 0, 1, 2);
        addedge(1, 0, 0, 1);
        addedge(1, 0, 0, 2);
        for (int i = 1; i < m - 2; ++ i){
            for (int j = 0; j < 2; ++ j){
                addedge(j, i, j, i + 2);
            }
        }
        addedge(0, m - 2, 1, m - 1);
        addedge(1, m - 2, 0, m - 1);
    }
    else if (m == 4 || n == 4){
        if (n != 4){
            std::swap(n, m);
            flag = !flag;
        }
        for (int k = 0; k < 2; ++ k){
            addedge(k << 1, 0, k << 1 | 1, 1);
            addedge(k << 1, 0, k << 1 | 1, 2);
            addedge(k << 1 | 1, 0, k << 1, 1);
            addedge(k << 1 | 1, 0, k << 1, 2);
            for (int i = 1; i < m - 2; ++ i){
                for (int j = 0; j < 2; ++ j){
                    addedge(k << 1 | j, i, k << 1 | j, i + 2);
                }
            }
        }
        addedge(0, m - 2, 2, m - 1);
        addedge(1, m - 1, 2, m - 2);
        addedge(1, m - 2, 3, m - 2);
        addedge(0, m - 1, 3, m - 1);
    }
    else if (m == 5){
        if (n == 3){
            addedge(0, 0, 1, 1);
            addedge(1, 1, 0, 2);
            addedge(0, 2, 1, 3);
            addedge(1, 3, 0, 4);
            addedge(0, 4, 2, 4);
            addedge(2, 4, 2, 2);
            addedge(2, 2, 2, 0);
            addedge(2, 0, 1, 2);
            addedge(1, 2, 1, 4);
            addedge(1, 4, 2, 3);
            addedge(2, 3, 2, 1);
            addedge(2, 1, 1, 0);
            addedge(1, 0, 0, 1);
            addedge(0, 1, 0, 3);
            addedge(0, 3, 0, 0);
        }
        else{
            for (int i = 0; i < n; ++ i){
                addedge(i, 0, i, 2);
                addedge(i, 0, i, 3);
                addedge(i, 1, i, 3);
                addedge(i, 1, i, 4);
            }
            addedge(0, m - 3, 1, m - 1);
            addedge(1, m - 3, 4, m - 3);
            addedge(4, m - 1, 3, m - 3);
            addedge(3, m - 1, 2, m - 3);
            addedge(2, m - 1, 0, m - 1);
        }
    }
    else if (m >= 6){
        for (int i = 0; i < n; ++ i){
            addedge(i, 0, i, 2);
            addedge(i, 0, i, 3);
            addedge(i, 1, i, 3);
            addedge(i, 1, i, 4);
            addedge(i, 2, i, 5);
            for (int j = 4; j < m - 2; ++ j){
                addedge(i, j, i, j + 2);
            }
        }
        if (n == 3){
            addedge(0, m - 2, 1, m - 1);
            addedge(1, m - 2, 2, m - 1);
            addedge(2, m - 2, 0, m - 1);
        }
        else{
            addedge(0, m - 2, 1, m - 1);
            addedge(0, m - 1, 2, m - 1);
            addedge(1, m - 2, 3, m - 2);
            for (int i = 2; i < n - 2; i += 2){
                addedge(i, m - 2, i + 2, m - 1);
                if (i < n - 3){
                    addedge(i + 1, m - 1, i + 3, m - 2);
                }
            }
            addedge(n - 2, m - (n & 1 ? 1 : 2), n - 1, m - (n & 1 ? 2 : 1));
        }
    }
    else{
        addedge(0, 0, 1, 1);
        addedge(1, 1, 0, 2);
        addedge(0, 2, 2, 2);
        addedge(2, 2, 2, 0);
        addedge(2, 0, 0, 1);
        addedge(0, 1, 1, 2);
        addedge(1, 2, 1, 0);
        addedge(1, 0, 2, 1);
        addedge(2, 1, 0, 0);
    }
    dfs(0);
    for (auto u : ans){
        if (flag){
            std::swap(u.first, u.second);
        }
        printf("%d %d\n", u.first + 1, u.second + 1);
    }
    return 0;
}
