#include<bits/stdc++.h>

int main(){
    int x, y;
    scanf("%d%d", &x, &y);
    int sum = 0;
    double tot = 0;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        int l, u;
        double f;
        scanf("%d%d%lf", &l, &u, &f);
        sum += u - l;
        tot += (u - l) * f;
    }
    tot += y - sum;
    printf("%.15f\n", x / tot);
    return 0;
}

