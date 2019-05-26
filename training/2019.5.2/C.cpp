#include <bits/stdc++.h>

const int N = 50010;

std::map <int, int> e[N];
std::vector <int> loop[N];
int loopcnt;
bool vis[N], instack[N];
std::vector <int> stack;

void dfs(int u){
    stack.push_back(u);
    instack[u] = true;
    vis[u] = true;
    for (auto tmp : e[u]){
        int v = tmp.first;
        if (instack[v]){
            int sit = stack.size() - 1;
            if (stack[sit - 1] != v) {
                loop[loopcnt].push_back(v);
                e[v][u] = e[u][v] = loopcnt;
                while (stack[sit] != v) {
                    loop[loopcnt].push_back(stack[sit]);
                    e[stack[sit]][stack[sit - 1]] = e[stack[sit - 1]][stack[sit]] = loopcnt;
                    --sit;
                }
                ++loopcnt;
            }
        }
        if (vis[v]){
            continue;
        }
        dfs(v);
    }
    instack[u] = false;
    stack.pop_back();
}

char s[100];

std::vector <std::string> ans;

void solve(int u){
    if (e[u].empty()){
        return;
    }
    auto tmp = e[u].begin();
    int v = tmp -> first;
    if (tmp -> second == -1){
        e[u].erase(v);
        e[v].erase(u);
        solve(u), solve(v);
        sprintf(s, "r %d 1 3", v);
        ans.emplace_back(s);
        sprintf(s, "j %d %d", u, v);
        ans.emplace_back(s);
        sprintf(s, "c %d 1 3", u);
        ans.emplace_back(s);
        sprintf(s, "r %d 3 2", v);
        ans.emplace_back(s);
        return;
    }
    auto &vec = loop[tmp -> second];
    int n = vec.size();
    for (int i = 0; i < n; ++ i){
        if (vec[i] == u){
            std::rotate(vec.begin(), vec.begin() + i, vec.end());
            break;
        }
    }
    for (int i = 0; i < n; ++ i){
        e[vec[i]].erase(vec[(i + 1) % n]);
        e[vec[(i + 1) % n]].erase(vec[i]);
    }
    for (int i = 0; i < n; ++ i){
        solve(vec[i]);
    }
    sprintf(s, "r %d 1 4", vec[0]);
    ans.emplace_back(s);
    sprintf(s, "j %d %d", vec[0], vec[1]);
    ans.emplace_back(s);
    sprintf(s, "c %d 1 4", vec[0]);
    ans.emplace_back(s);
    for (int i = 2; i < n; ++ i) {
        sprintf(s, "r %d 1 3", vec[0]);
        ans.emplace_back(s);
        sprintf(s, "j %d %d", vec[0], vec[i]);
        ans.emplace_back(s);
        sprintf(s, "c %d 1 3", vec[0]);
        ans.emplace_back(s);
        sprintf(s, "r %d 3 2", vec[0]);
        ans.emplace_back(s);
    }
    sprintf(s, "c %d 4 1", vec[0]);
    ans.emplace_back(s);
    sprintf(s, "r %d 1 2", vec[0]);
    ans.emplace_back(s);
    sprintf(s, "r %d 4 1", vec[0]);
    ans.emplace_back(s);
}

int main(){
    freopen("cactus.in", "r", stdin);
    freopen("cactus.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i){
        int k;
        scanf("%d", &k);
        std::vector <int> vec(k);
        for (int j = 0; j < k; ++ j){
            scanf("%d", &vec[j]);
        }
        for (int j = 0; j < k - 1; ++ j){
            e[vec[j]][vec[j + 1]] = -1;
            e[vec[j + 1]][vec[j]] = -1;
        }
    }
    dfs(1);
    solve(1);
    printf("%d\n", (int) ans.size());
    for (auto u : ans){
        printf("%s\n", u.c_str());
    }
    return 0;
}
