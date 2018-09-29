#include<bits/stdc++.h>

const int N = 16;
const int M = 10000010;

bool vis[1 << N];
int x[4][5] = {{0, 0, 0, 1, 2}, {0, 1, 2, 2, 2}, {0, 1, 2, 2, 2}, {0, 0, 0, 1, 2}};
int y[4][5] = {{0, 1, 2, 0, 0}, {0, 0, 0, 1, 2}, {2, 2, 2, 1, 0}, {0, 1, 2, 2, 2}};
char s[M];
int a[M];
int n, m;

void init(){
    std::queue <int> queue;
    vis[0] = 1;
    queue.push(0);
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        for (int i = 0; i < std::min(n, 4) - 2; ++ i){
            for (int j = 0; j < std::min(m, 4) - 2; ++ j){
                for (int k = 0; k < 4; ++ k){
                    int v = u;
                    for (int w = 0; w < 5; ++ w){
                        int tmp = (i + x[k][w]) * std::min(m, 4) + (j + y[k][w]);
                        v ^= 1 << tmp;
                    }
                    if (!vis[v]){
                        vis[v] = true;
                        queue.push(v);
                    }
                }
            }
        }
    }
}

int &get(int x, int y){
    return a[x * m + y];
}

int main(){
    int test;
    scanf("%d%d%d", &n, &m, &test);
    if (n < 3 || m < 3){
        while (test --){
            for (int i = 0; i < n; ++ i){
                scanf("%s", s + i * m);
            }
            bool flag = true;
            for (int i = 0; i < n * m; ++ i){
                if (s[i] == '#'){
                    flag = false;
                    break;
                }
            }
            puts(flag ? "Yes" : "No");
        }
        return 0;
    }
    init();
    while (test --){
        for (int i = 0; i < n; ++ i){
            scanf("%s", s + i * m);
        }
        for (int i = 0; i < n * m; ++ i){
            a[i] = s[i] == '#';
        }
        for (int i = 0; i < n; ++ i){
            for (int j = m - 1; j >= 4; -- j){
                if (!get(i, j)) continue;
                get(i, j - 1) ^= 1;
                get(i, j - 3) ^= 1;
                get(i, j - 4) ^= 1;
            }
        }
        for (int j = 0; j < std::min(m, 4); ++ j){
            for (int i = n - 1; i >= 4; -- i){
                if (!get(i, j)) continue;
                get(i - 1, j) ^= 1;
                get(i - 3, j) ^= 1;
                get(i - 4, j) ^= 1;
            }
        }
        int x = 0;
        for (int i = 0; i < std::min(n, 4); ++ i){
            for (int j = 0; j < std::min(m, 4); ++ j){
                x ^= get(i, j) << (i * std::min(m, 4) + j); 
            }
        }
        puts(vis[x] ? "Yes" : "No");
    }
    return 0;
}
