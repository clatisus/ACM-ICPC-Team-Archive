#include<bits/stdc++.h>

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);
        if (l > d){
            printf("%d\n", d);
        }
        else{
            printf("%d\n", (r / d + 1) * d);
        }
    }
    return 0;
}
