#include<bits/stdc++.h>

const double eps = 1e-5;
inline double sqr(double x){return x * x;}

double simpson(double l, double r, double (*f)(double)){
    double mid = (l + r) * 0.5;
    return (f(l) + 4 * f(mid) + f(r)) * (r - l) / 6;
}

double asr(double l, double r, double eps, double value, double (*f) (double)){
    double mid = (l + r) * 0.5;
    double left = simpson(l, mid, f), right = simpson(mid, r, f);
    if (std::abs(left + right - value) < 15 * eps){
        return left + right + (left + right - value) / 15;
    }
    return asr(l, mid, eps / 2, left, f) + asr(mid, r, eps / 2, right, f);
}

double calc(double l, double r, double (*f) (double), double eps) {
    return asr(l, r, eps, simpson(l, r, f), f);
}

const int N = 1010;

double h[N], r[N];
double x[N];
double x1[N], yy1[N], x2[N], y2[N];
int n;

double f(double xx){
    double max = 0;
    for (int i = 0; i < n; ++ i){
        if (std::abs(xx - x[i]) <= r[i]){
            max = std::max(max, std::sqrt(sqr(r[i]) - sqr(xx - x[i])));
        }
        if (x1[i] <= xx && xx <= x2[i]){
            if (std::abs(x1[i] - x2[i]) < eps){
                max = std::max(max, yy1[i]);
                continue;
            }
            max = std::max(max, yy1[i] + (y2[i] - yy1[i]) * (xx - x1[i]) / (x2[i] - x1[i]));
        }
    }
    return max * 2;
}

int main(){
    double alpha; 
    scanf("%d%lf", &n, &alpha);
    for (int i = 0; i <= n; ++ i){
        scanf("%lf", &h[i]);
        if (i) h[i] += h[i - 1];
    }
    for (int i = 0; i < n; ++ i){
        scanf("%lf", &r[i]);
    }
    for (int i = 0; i <= n; ++ i){
        x[i] = h[i] * std::cos(alpha) / std::sin(alpha);
    }
    for (int i = 0; i < n; ++ i){
        double Cos = (r[i] - r[i + 1]) / (x[i + 1] - x[i]);
        if (std::abs(Cos) >= 1 - eps){
            x1[i] = 1, x2[i] = 0;
            continue;
        }
        x1[i] = r[i] * Cos, yy1[i] = std::sqrt(sqr(r[i]) - sqr(x1[i])), x1[i] += x[i];
        x2[i] = r[i + 1] * Cos, y2[i] = std::sqrt(sqr(r[i + 1]) - sqr(x2[i])), x2[i] += x[i + 1];
    }
    double left = 1e100, right = -1e100;
    for (int i = 0; i <= n; ++ i){
        left = std::min(left, x[i] - r[i]);
        right = std::max(right, x[i] + r[i]);
    }
    printf("%.2f\n", calc(left, right, f, eps));
    return 0;
}
