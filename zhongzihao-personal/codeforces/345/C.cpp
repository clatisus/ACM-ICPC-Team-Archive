#include<bits/stdc++.h>

const int N = 1000010;
typedef std::pair <int, int> pii;
typedef std::pair <int, pii> piii;

std::vector <int> vecx[N], vecy[N], vec[N];
piii p[N];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    int cnt = 0;
    for (int i = 0; i < n; ++ i){
        for (int j = 0, x; j < m; ++ j){
            scanf("%d", &x);
            vec[i].push_back(x);
            vecx[i].push_back(x);
            vecy[j].push_back(x);
            p[cnt ++] = {x, {i, j}};
        }
    }
    for (int i = 0; i < n; ++ i){
        std::sort(vecx[i].begin(), vecx[i].end());
        vecx[i].erase(std::unique(vecx[i].begin(), vecx[i].end()), vecx[i].end());
    }
    for (int i = 0; i < m; ++ i){
        std::sort(vecy[i].begin(), vecy[i].end());
        vecy[i].erase(std::unique(vecy[i].begin(), vecy[i].end()), vecy[i].end());
    }
    std::sort(p, p + cnt);
    std::map <int, int> ans;
    for (int i = 0; i < cnt; ++ i){
        if (!ans.count(p[i].first)){
            ans[p[i].first] = 1;
        }
        int sit = p[i].second.first;
        int sit1 = std::lower_bound(vecx[sit].begin(), vecx[sit].end(), p[i].first) - vecx[sit].begin() - 1;
        if (sit1 >= 0){
            ans[p[i].first] = std::max(ans[vecx[sit][sit1]] + 1, ans[p[i].first]);
        }

        sit = p[i].second.second;
        sit1 = std::lower_bound(vecy[sit].begin(), vecy[sit].end(), p[i].first) - vecy[sit].begin() - 1;
        if (sit1 >= 0){
            ans[p[i].first] = std::max(ans[vecy[sit][sit1]] + 1, ans[p[i].first]);
        }
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            printf("%d%c", ans[vec[i][j]], " \n"[j == m - 1]);
        }
    }
    return 0;
}
