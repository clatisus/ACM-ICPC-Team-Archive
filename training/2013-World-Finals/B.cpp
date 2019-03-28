#include <bits/stdc++.h>

const int N = 100010;
const double eps = 1e-50;

inline int sig(double p){return (p > eps) - (p < -eps);}

double r, t, logr;
double powr[N], powinv[N];

double calc(int l, int w){
    if (!l && !w) {
        return 0;
    }
    if (w * logr > 40){
        return l * t;
    }
    double powl = powinv[-l], poww = powr[w];
    double win = (1 - powl) * w;
    double lose = (poww - 1) * l * t;
    return (win + lose) / (poww - powl);
}

int main(){
    double x, p;
    scanf("%lf%lf", &x, &p);
    x /= 100, p /= 100;
    if (!sig(x) || !sig(p)){
        printf("%.15f\n", 0.0);
        return 0;
    }
    r = (1 - p) / p, t = 1 - x;
    logr = std::log(r);
    powr[0] = 1;
    for (int i = 1; i < N; ++ i){
        powr[i] = powr[i - 1] * r;
        if (std::log(powr[i]) > 500){
            break;
        }
    }
    powinv[0] = 1;
    for (int i = 1; i < N; ++ i){
        powinv[i] = powinv[i - 1] / r;
        if (powinv[i] < eps){
            break;
        }
    }
    const int MAX1 = 21000;
    const int MAX2 = 2500;
    double ans = 0;
    for (int l = -MAX1; l <= 0; ++ l){
        for (int w = 0; w <= MAX2; ++ w){
            ans = std::max(ans, calc(l, w));
        }
    }
    printf("%.15f\n", (double) ans);
    return 0;
}
