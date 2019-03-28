#include<bits/stdc++.h>

const int N = 1010;

int d[N], s[N];

int main(){
    int n, t;
    scanf("%d%d", &n, &t);
    int min = INT_MAX;
    for (int i = 0; i < n; ++ i){
        scanf("%d%d", &d[i], &s[i]);
        min = std::min(min, s[i]);
    }
    double left = -min + 1e-7, right = 1e7;
    for (int _ = 0; _ < 100; ++ _){
        double mid = (left + right) * 0.5;
        double sum = 0;
        for (int i = 0; i < n; ++ i){
            sum += d[i] / (s[i] + mid);
        }
        if (sum > t){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    printf("%.15f\n", left);
    return 0;
}
