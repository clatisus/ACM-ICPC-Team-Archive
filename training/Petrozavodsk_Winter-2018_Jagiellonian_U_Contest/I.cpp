#include <bits/stdc++.h>

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        int x;
        scanf("%d", &x);
        puts(x & 1 ? "B" : "A");
    }
    return 0;
}
