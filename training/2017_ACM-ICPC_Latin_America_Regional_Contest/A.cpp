#include<bits/stdc++.h>

const int N = 15;
const double INF = 1e100;

struct P{
    int x, y;

    void read(){
        scanf("%d%d", &x, &y);
    }

    bool operator < (const P &p)const{
        return y < p.y;
    }

    bool operator == (const P &p)const{
        return y == p.y;
    }
};

double cross(P p1, P p2, P q){
    //printf("%d %d %d %d\n", p1.x, p1.y, p2.x, p2.y);
    return p1.x + 1. * (p2.x - p1.x) * (q.y - p1.y) / (p2.y - p1.y);
    /*
    double k = 1.0 * (p2.x - p1.x) / (p2.y - p1.y);
    double b = p2.x - k * p2.y;
    return k * q.y + b;*/
}

int n;
std::vector <P> ps[N];
std::vector <P> left[N], right[N];
double min[N][N];
int leftmost[N], rightmost[N];
double dp[1 << N][N];

void solve(){
    int h = 0;
    for (int i = 0; i < n; ++ i){
        leftmost[i] = INT_MAX;
        rightmost[i] = INT_MIN;
        ps[i].clear();
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; ++ j){
            P p;
            p.read();
            ps[i].push_back(p);
            h = std::max(h, p.y);
            leftmost[i] = std::min(leftmost[i], p.x);
            rightmost[i] = std::max(rightmost[i], p.x);
        }
    }
    for (int i = 0; i < n; ++ i){
        left[i].clear();
        right[i].clear();
        int sit, sz = ps[i].size();
        for (int j = 1; j < sz; ++ j){
            right[i].push_back(ps[i][j]);
            if (ps[i][j].y == h){
                sit = j;
                break;
            }
        }
        for (int j = sit + 1; j < sz; ++ j){
            left[i].push_back(ps[i][j]);
        }
        left[i].push_back(ps[i][0]);
        std::reverse(left[i].begin(), left[i].end());
        /*puts("--------left-------");
        for (auto u : left[i]){
            printf("%d %d\n", u.x, u.y);
        }
        puts("--------right-------");
        for (auto u : right[i]){
            printf("%d %d\n", u.x, u.y);
        }*/
    }
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j){
            if (i == j) continue;
            min[i][j] = 0;
            for (auto u : right[i]){
                int sit = std::upper_bound(left[j].begin(), left[j].end(), u) - left[j].begin();
                -- sit;
                double crossp;
                if (sit + 1 == left[j].size()){
                    crossp = left[j][sit].x;
                }
                else{
                    crossp = cross(left[j][sit], left[j][sit + 1], u);
                }
                //printf("%.10f\n", crossp);
                min[i][j] = std::max(min[i][j], rightmost[j] - crossp + u.x - rightmost[i]);
            }
            for (auto u : left[j]){
                int sit = std::upper_bound(right[i].begin(), right[i].end(), u) - right[i].begin();
                -- sit;
                double crossp;
                if (sit + 1 == right[i].size()){
                    crossp = right[i][sit].x;
                }
                else{
                    crossp = cross(right[i][sit], right[i][sit + 1], u);
                }
                //printf("u = %d %d, sit = %d, crossp = %.10f\n", u.x, u.y, sit, crossp);
                min[i][j] = std::max(min[i][j], crossp + rightmost[j] - u.x - rightmost[i]);
            }
        }
    }
    for (int i = 0; i < n; ++ i){
        dp[1 << i][i] = rightmost[i] - leftmost[i];
    }
    for (int i = 1; i < 1 << n; ++ i){
        if ((i & -i) == i){
            continue;
        }
        for (int j = 0; j < n; ++ j){
            if (i >> j & 1){
                dp[i][j] = INF;
                for (int k = 0; k < n; ++ k){
                    if (i >> k & 1){
                        if (j == k) continue;
                        dp[i][j] = std::min(dp[i][j], dp[i ^ 1 << j][k] + min[k][j]);
                    }
                }
            }
        }
    }
    double ans = INF;
    for (int i = 0; i < n; ++ i){
        ans = std::min(ans, dp[(1 << n) - 1][i]);
    }
    printf("%.3f\n", ans);
}

int main(){
    while (scanf("%d", &n) != EOF){
        solve();
    }
}

/*
2
4
0 0
2 0
4 2
2 2
5
0 0
1 0
1 2
0 2
-1 1
*/
