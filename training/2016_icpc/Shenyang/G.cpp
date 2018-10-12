#include<bits/stdc++.h>

const double eps = 1e-6;
const double PI = std::acos(-1.0);
inline double sqr(double x){return x * x;}
inline double cube(double x){return x * x * x;}

double calc(double alpha){
    return -alpha * std::cos(alpha) + std::sin(alpha) - cube(std::sin(alpha)) / 3;
}

double calc1(double alpha){
    return alpha - std::sin(alpha) * std::cos(alpha);
}

void solve(){
    double v;
    scanf("%lf", &v);
    v *= PI;
    const int MAX = 60;
    if (v > PI){
        double left = 0, right = 2;
        for (int Time = 0; Time < MAX; ++ Time){
            double mid = (left + right) * 0.5;
            double area = 2 * PI - PI * (2 - mid) * 0.5;
            if (area > v){
                right = mid;
            }
            else{
                left = mid;
            }
        }
        printf("%.5f\n", PI * std::sqrt(4 + sqr(2 - left)) / 2);
    }
    else{
        double left = 0, right = PI / 4;
        for (int Time = 0; Time < MAX; ++ Time){
            double mid = (left + right) * 0.5;
            if (calc(std::acos(1 - 2 * std::tan(mid))) < std::tan(mid) * v){
                left = mid;
            }
            else{
                right = mid;
            }
        }
        if (left < eps){
            puts("0.00000");
            return;
        }
        printf("%.5f\n", calc1(std::acos(1 - 2 * std::tan(left))) / std::sin(left));
    }
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

