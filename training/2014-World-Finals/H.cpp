#include <bits/stdc++.h>

const int N = 25;
const int M = 10010;
const double eps = 1e-12;
typedef std::pair <int, double> pid;
typedef std::pair <int, int> pii;

char s[M][N];
bool vis[M][N];
int w, h;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int prob[4];
std::vector <pid> rvec[N * M];
std::vector <int> cvec[N * M];
double ans[N * M];

bool check(int x, int y){
    return x >= 0 && x < h && y >= 0 && y < w && s[x][y] != 'X';
}

inline int sig(double p){
    return (p > eps) - (p < -eps);
}

int main(){
    scanf("%d%d", &w, &h);
    for (int i = 0; i < 4; ++ i){
        scanf("%d", &prob[i]);
    }
    for (int i = 0; i < h; ++ i){
        scanf("%s", s[i]);
    }
    std::queue <pii> queue;
    int cnt = 0;
    for (int i = 0; i < w; ++ i){
        if (s[0][i] == '.'){
            ++ cnt;
            vis[0][i] = true;
            queue.push({0, i});
        }
    }
    while (!queue.empty()){
        pii p = queue.front();
        queue.pop();
        for (int i = 0; i < 4; ++ i){
            int x = p.first + dir[i][0], y = p.second + dir[i][1];
            if (check(x, y) && !vis[x][y]){
                vis[x][y] = true;
                queue.push({x, y});
            }
        }
    }
    std::map <pii, int> id;
    for (int i = 0; i < h; ++ i){
        for (int j = 0; j < w; ++ j){
            if (vis[i][j]){
                int x = id.size();
                id[{i, j}] = x;
            }
        }
    }
    for (int i = 0; i < w; ++ i){
        if (s[0][i] == '.'){
            ans[id[{0, i}]] = 1.0 / cnt;
        }
    }
    for (auto u : id){
        int x = u.first.first, y = u.first.second;
        int code = u.second;
        rvec[code].push_back({code, 1.0});
        cvec[code].push_back(code);
        if (s[x][y] != '.'){
            continue;
        }
        int sum = 0;
        for (int k = 0; k < 4; ++ k){
            int xx = x + dir[k][0], yy = y + dir[k][1];
            if (check(xx, yy)){
                sum += prob[k];
            }
        }
        for (int k = 0; k < 4; ++ k){
            int xx = x + dir[k][0], yy = y + dir[k][1];
            if (check(xx, yy)){
                int ccode = id[{xx, yy}];
                rvec[ccode].push_back({code, -1.0 * prob[k] / sum});
                cvec[code].push_back(ccode);
            }
        }
    }
    int idsz = id.size();
    for (int i = 0; i < idsz; ++ i){
        std::sort(rvec[i].begin(), rvec[i].end());
    }
    for (int i = 0; i < idsz; ++ i){
        int sz = rvec[i].size();
        ans[i] /= rvec[i][0].second;
        for (int j = sz - 1; j >= 0; -- j){
            rvec[i][j].second /= rvec[i][0].second;
        }
        for (auto j : cvec[i]){
            if (j <= i || rvec[j].empty() || rvec[j][0].first != i){
                continue;
            }
            int ssz = rvec[j].size();
            double coe = rvec[j][0].second;
            std::vector <pid> vec;
            int u = 0, v = 0;
            for ( ; u < sz && v < ssz; ){
                if (rvec[i][u].first < rvec[j][v].first){
                    vec.push_back({rvec[i][u].first, -coe * rvec[i][u].second});
                    ++ u;
                }
                else if (rvec[i][u].first > rvec[j][v].first){
                    vec.push_back(rvec[j][v]);
                    ++ v;
                }
                else{
                    double x = rvec[j][v].second - coe * rvec[i][u].second;
                    if (sig(x)){
                        vec.push_back({rvec[i][u].first, x});
                    }
                    ++ u, ++ v;
                }
            }
            while (u < sz){
                vec.push_back({rvec[i][u].first, -coe * rvec[i][u].second});
                ++ u;
            }
            while (v < ssz){
                vec.push_back(rvec[j][v]);
                ++ v;
            }
            for (auto w : vec){
                cvec[w.first].push_back(j);
            }
            ans[j] -= coe * ans[i];
            vec.swap(rvec[j]);
        }
        std::vector <int>().swap(cvec[i]);
    }
    for (int i = idsz; i >= 0; -- i){
        int sz = rvec[i].size();
        for (int j = 1; j < sz; ++ j){
            ans[i] -= rvec[i][j].second * ans[rvec[i][j].first];
        }
    }
    for (int i = 0; i < h; ++ i){
        for (int j = 0; j < w; ++ j){
            if (s[i][j] == 'T'){
                printf("%.15f\n", id.count({i, j}) ? ans[id[{i, j}]] : 0.0);
            }
        }
    }
    return 0;
}
