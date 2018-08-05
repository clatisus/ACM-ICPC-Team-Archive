#include <bits/stdc++.h>
 
const int N = 100010;
 
int s[N], c[N];
double a[N];
 
int main() {
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF){
        for (int i = 0; i < n; ++ i){
            scanf("%d", &s[i]);
        }
        for (int i = 0; i < n; ++ i){
            scanf("%d", &c[i]);
        }
        double left = 0, right = 1e4;
        for (int i = 0; i < 50; ++ i){
            double mid = (left + right) / 2;
            for (int j = 0; j < n; ++ j){
                a[j] = s[j] * (c[j] - mid);
            }
            std::sort(a, a + n, std::greater <double>());
            double sum = 0;
            for (int i = 0; i < n - k; ++ i){
                sum += a[i];
            }
            if (sum > 0){
                left = mid;
            }
            else{
                right = mid;
            }
        }
        printf("%.10lf\n", left);
    }
    return 0;
}
