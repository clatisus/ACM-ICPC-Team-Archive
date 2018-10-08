#include<bits/stdc++.h>

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        int n;
        scanf("%d", &n);
        printf("Case #%d: %d\n", i, n / 3);
    }
    return 0;
}
