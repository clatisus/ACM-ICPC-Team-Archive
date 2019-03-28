#include <bits/stdc++.h>

const int N = 10010;
const double PI = std::acos(-1.0);

inline double cube(double x){return x * x * x;}

int r[N], x[N], y[N], z[N];
double ans[N];
int n, w;

double inte(double l, double r, double rr){
    return PI * ((r * rr * rr - cube(r) / 3) - (l * rr * rr - cube(l) / 3));
}

double calc(double mid){
    double ans = 0;
    for (int i = 0; i < n; ++ i){
        double up = std::min((z[i] + r[i]) / 1000.0, mid);
        double t = up - z[i] / 1000.0;
        if (t >= -r[i] / 1000.0) {
            ans += inte(-r[i] / 1000.0, t, r[i] / 1000.0);
        }
    }
    return ans;
}

int main(){
    scanf("%d%d", &n, &w);
    double total = 1e6;
    for (int i = 0; i < n; ++ i){
        scanf("%d%d%d%d", &r[i], &x[i], &y[i], &z[i]);
        total -= 4 * PI * cube(r[i] / 1000.0) / 3;
    }
    for (int i = 1; i < w; ++ i){
        double left = 0, right = 100;
        double area = total * i / w;
        for (int _ = 0; _ < 60; ++ _){
            double mid = (left + right) * 0.5;
            if (100 * 100 * mid - calc(mid) < area){
                left = mid;
            }
            else{
                right = mid;
            }
        }
        ans[i] = left;
    }
    ans[w] = 100;
    for (int i = 1; i <= w; ++ i){
        printf("%.15f\n", ans[i] - ans[i - 1]);
    }
    return 0;
}
