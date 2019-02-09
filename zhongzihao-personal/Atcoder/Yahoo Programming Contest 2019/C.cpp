#include<bits/stdc++.h>

int main(){
    int k, a, b;
    scanf("%d%d%d", &k, &a, &b);
    if (b - a > 2){
        if (k < a){
            printf("%d\n", k);
        }
        else{
            printf("%lld\n", a + 1ll * (b - a) * ((k - a + 1) / 2) + ((k - a + 1) & 1));
        }
    }
    else{
        printf("%d\n", k + 1);
    }
    return 0;
}
