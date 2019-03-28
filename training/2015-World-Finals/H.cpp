#include<bits/stdc++.h>

const int N = 1010;
inline double sqr(double x){return x * x;}

double ans[N];
double coe[N];

int main(){
    int w, h, n;
    scanf("%d%d%d", &w, &h, &n);
    ans[0] = sqr(1.0 * h / w + 1) * 0.5;
    for (int i = 1; i <= n; ++ i){
        double a = sqr(1.0 * h / w - 1) * 0.5 - sqr(1.0 * h / w) + ans[i - 1];
        double b = sqr(1.0 * h / w) - 1;
        double c = sqr(1.0 * h / w + 1) * 0.5;
        coe[i] = -b / (2 * a);
        ans[i] = a * sqr(coe[i]) + b * coe[i] + c;
    }
    printf("%.15f\n", ans[n] * sqr(w) * 0.5);
    double now = w;
    std::vector <double> aans(n + 1);
    for (int i = n; i >= 1; -- i){
        now *= coe[i];
        aans[i] = now;
    }
    for (int i = 1; i <= std::min(n, 10); ++ i){
        printf("%.15f\n", aans[i]);
    }
    return 0;
}
