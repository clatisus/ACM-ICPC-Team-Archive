#include<bits/stdc++.h>

bool check(int n, int l, int v1, int v2, double x){
    double cur = 0;
    for (int i = 0; i < n; ++ i){
        double dis = 2 * (cur + x) / v1 / (1.0 / v1 + 1.0 / v2);
        if (dis + x > l){
            return false;
        }
        cur = dis;
    }
    return true;
}

int main(){
    int n, l, v1, v2, k;
    scanf("%d%d%d%d%d", &n, &l, &v1, &v2, &k);
    n = (n + k - 1) / k;
    double left = 0, right = l;
    for (int i = 0; i < 40; ++ i){
        double mid = (left + right) / 2;
        if (check(n, l, v1, v2, mid)){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    printf("%.10lf\n", left / v2 + (l - left) / v1);
    return 0;
}
