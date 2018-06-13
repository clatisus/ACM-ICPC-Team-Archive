#include<bits/stdc++.h>

int main(){
    int n = 200000;
    printf("%d\n", n);
    for (int i = 0; i < n; ++ i){
        printf("%d%c", 166320, " \n"[i == n - 1]);
    }
    for (int i = 0; i < n - 1; ++ i){
        printf("%d %d\n", i + 1, i + 2);
    }
    return 0;
}
