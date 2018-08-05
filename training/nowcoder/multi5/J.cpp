#include<bits/stdc++.h>
 
typedef long long ll;
 
int main(){
    int n, p2, p3;
    while (scanf("%d%d%d", &n, &p2, &p3) != EOF){
        ll min = LLONG_MAX;
        for (int i = 0; i < 10; ++ i){
            int num3 = (std::max(0, n - i * 2) + 2) / 3;
            min = std::min(min, 1ll * p2 * i + 1ll * p3 * num3);
        }
        for (int i = 0; i < 10; ++ i){
            int num2 = (std::max(0, n - i * 3) + 1) / 2;
            min = std::min(min, 1ll * p2 * num2 + 1ll * p3 * i);
        }
        printf("%lld\n", min);
    }
    return 0;
}
