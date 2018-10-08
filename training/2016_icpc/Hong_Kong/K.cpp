#include<bits/stdc++.h>

const int N = 1000010;

std::vector <int> e[N];
std::vector <int> vec[N], vec1[N];
std::vector <std::vector <int>> ans[N];
std::vector <int> man[N];
int fa[N];
int cnt[N], sz[N], top[N];

void dfs(int u){
    int elesz = vec[u].size();
    cnt[u] = INT_MAX;
    int maxsit = -1;
    for (auto v : e[u]){
        elesz -= vec[v].size();
        dfs(v);
        cnt[u] = std::min(cnt[u], cnt[v]);
        if (maxsit == -1 || sz[top[v]] > sz[top[maxsit]]){
            maxsit = v;
        }
    }
    if (cnt[u] == INT_MAX){
        top[u] = u;
        for (auto v : man[u]){
            ans[u].push_back({v});
        }
        cnt[u] = sz[u] = man[u].size();
        return;
    }
    top[u] = top[maxsit];
    if (!elesz){
        for (auto v : e[u]){
            if (v == maxsit) continue;
            for (int i = 0; i < cnt[u]; ++ i){
                for (auto w : ans[top[v]][i]){
                    ans[top[u]][i].push_back(w);
                    ++ sz[top[u]];
                }
            }
        }
    }
    else{
        cnt[u] = 0;
    }
    cnt[u] += man[u].size();
    ans[top[u]].resize(cnt[u]);
    for (int i = 0, ssz = man[u].size(); i < ssz; ++ i){
        ans[top[u]][i + cnt[u] - man[u].size()] = {man[u][i]};
        ++ sz[top[u]];
    }
}

int main(){
    int n, m, p;
    scanf("%d%d%d", &m, &n, &p);
    for (int i = 1; i <= n; ++ i){
        int x;
        scanf("%d", &x);
        for (int j = 0; j < x; ++ j){
            int y;
            scanf("%d", &y);
            vec[i].push_back(y);
            vec1[y].push_back(i);
        }
    }
    for (int i = 1; i <= m; ++ i){
        std::sort(vec1[i].begin(), vec1[i].end(),
                [&](const int &i, const int &j){
                    return vec[i].size() == vec[j].size() ? i < j : vec[i].size() > vec[j].size();
                });
        for (int j = 0, sz = vec1[i].size(); j < sz - 1; ++ j){
            fa[vec1[i][j + 1]] = vec1[i][j];
        }
    }
    for (int i = 1; i <= n; ++ i){
        e[fa[i]].push_back(i);
    }
    for (int i = 1; i <= m; ++ i){
        vec[0].push_back(i);
    }
    for (int i = 1; i <= p; ++ i){
        int x;
        scanf("%d", &x);
        man[x].push_back(i);
    }
    dfs(0);
    printf("%d\n", cnt[0]);
    for (int i = 0; i < cnt[0]; ++ i){
        printf("%d", (int) ans[top[0]][i].size());
        for (auto u : ans[top[0]][i]){
            printf(" %d", u);
        }
        puts("");
    }
    return 0;
}

