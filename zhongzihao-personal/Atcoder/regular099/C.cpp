#include<bits/stdc++.h>

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0, x; i < n; ++ i){
        scanf("%d", &x);
    }
    printf("%d\n", (n - 1 - 1) / (k - 1) + 1);
    return 0;
}
