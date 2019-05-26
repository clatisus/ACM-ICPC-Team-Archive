#include <bits/stdc++.h>

int main(){
    int n;
    scanf("%d", &n);
    if (n == 1 || n == 2){
        puts("1");
        return 0;
    }
    printf("%d\n", n - 2);
    return 0;
}
