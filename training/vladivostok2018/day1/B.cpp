#include<bits/stdc++.h>

const long double eps = 1e-9;
const long double PI = std::acos(-1);
typedef long long ll;

struct P{
    int x, y;
    long double angle;

    P (int x = 0, int y = 0):x(x), y(y){
        angle = std::atan2(y, x);
        angle += angle < 0 ? 2 * PI : 0;
    }

    bool operator < (const P &p)const{
        return angle < p.angle;
    }

    P operator - (const P &p)const{
        return P(x - p.x, y - p.y);
    }

    void read(){
        scanf("%d%d", &x, &y);
    }
};

const int N = 1010;

P p[N];

void solve(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        p[i].read();
    }
    if (n <= 2){
        printf("%.7f\n", 0.0);
        return;
    }
    ll sum = 0;
    for (int i = 0; i < n; ++ i){
        std::vector <P> vec;
        for (int j = 0; j < n; ++ j){
            if (i == j) continue;
            vec.push_back(p[j] - p[i]);
        }
        std::sort(vec.begin(), vec.end());
        int sumx = 0, sumy = 0;
        for (auto u : vec){
            sumx += u.x;
            sumy += u.y;
        }
        for (int j = 0; j < n - 1; ++ j){
            vec.push_back(vec[j]);
            (-- vec.end()) -> angle += 2 * PI;
        }
        int nowx = 0, nowy = 0;
        for (int j = 0, k = 0; j < n - 1; ++ j){
            P u = vec[j];
            while (k < 2 * n - 2){
                long double dif = vec[k].angle - u.angle;
                if (dif > PI){
                    break;
                }
                nowx += vec[k].x;
                nowy += vec[k].y;
                ++ k;
            }
            sum += 1ll * u.x * (2 * nowy - sumy) - 1ll * u.y * (2 * nowx - sumx);
            nowx -= u.x;
            nowy -= u.y;
        }
    }
    printf("%.7Lf\n", (long double) 0.5 * (n / 3) * sum / n / (n - 1) / (n - 2));
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
