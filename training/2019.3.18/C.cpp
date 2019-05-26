#include <bits/stdc++.h>

const int N = 100010;

int a[N], b[N];
double tmp[N];
int n;

double calc(double x){
    for (int i = 0; i < n; ++ i){
        tmp[i] = a[i] * x + b[i];
    }
    std::sort(tmp, tmp + n);
    double mid = tmp[(n - 1) >> 1];
    double ans = 0;
    for (int i = 0; i < n; ++ i){
        ans += std::abs(tmp[i] - mid);
    }
    return ans / std::max(1.0, std::abs(x));
}

double solve(double l, double r){
    const int S = 100;
    for (int _ = 0; _ < S; ++ _){
        double mid1 = (2 * l + r) / 3, mid2 = (l + 2 * r) / 3;
        if (calc(mid1) > calc(mid2)){
            l = mid1;
        }
        else{
            r = mid2;
        }
    }
    return calc(l);
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d%d", &a[i], &b[i]);
    }
    double ans = 1e100;
    ans = std::min(ans, solve(-1, 1));
    ans = std::min(ans, solve(1, 1e7));
    for (int i = 0; i < n; ++ i){
        a[i] = -a[i];
    }
    ans = std::min(ans, solve(1, 1e7));
    std::sort(a, a + n);
    int mid = a[(n - 1) >> 1];
    double sum = 0;
    for (int i = 0; i < n; ++ i){
        sum += std::abs(a[i] - mid);
    }
    ans = std::min(ans, 1.0 * sum);
    printf("%.15f\n", ans);
    return 0;
}
