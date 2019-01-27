#include<bits/stdc++.h>

int main(){
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    printf("%d %d\n", std::min(a, b), (a + b) - std::min(n, a + b));
    return 0;
}
