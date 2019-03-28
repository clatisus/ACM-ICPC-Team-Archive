#include<bits/stdc++.h>

int main(){
    double ans = 0;
    int p, a, b, c, d, n;
    scanf("%d%d%d%d%d%d", &p, &a, &b, &c, &d, &n);
    double max = 1e-100;
    for (int i = 1; i <= n; ++ i){
        double x = p * (std::sin(i * a + b) + std::cos(i * c + d) + 2);
        ans = std::max(ans, max - x);
        max = std::max(max, x);
    }
    printf("%.15f\n", ans);
    return 0;
}
