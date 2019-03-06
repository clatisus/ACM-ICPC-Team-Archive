#include <bits/stdc++.h>

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        int x, y, z, r, a, b, c, d;
        scanf("%d%d%d%d%d%d%d%d", &x, &y, &z, &r, &a, &b, &c, &d);
        printf("%.15f\n", r * r * std::acos(-1.0));
    }
    return 0;
}
