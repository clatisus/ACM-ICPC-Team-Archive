#include<bits/stdc++.h>

const int N = 1010;
typedef std::pair <double, double> pdd;

int k[N], p[N][N];
pdd prob[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &k[i]);
        for (int j = 0; j < k[i]; ++ j){
            scanf("%d", &p[i][j]);
        }
        std::sort(p[i], p[i] + k[i]);
    }
    for (int i = 0; i < n; ++ i){
        double nowp = 1.0;
        for (int j = 0; j < k[i]; ++ j){
            prob[i].second += nowp;
            prob[i].first += nowp * (1 - p[i][j] / 1000.0);
            nowp *= p[i][j] / 1000.0;
        }
    }
    std::sort(prob, prob + n, [](pdd p1, pdd p2){return (p1.first - 1) * p2.second > (p2.first - 1) * p1.second;});
    double now = 0;
    for (int i = 0; i < n; ++ i){
        now = prob[i].first * now + prob[i].second;
    }
    printf("%.10lf\n", now);
    return 0;
}
