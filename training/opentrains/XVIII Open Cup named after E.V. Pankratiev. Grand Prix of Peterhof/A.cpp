#include<bits/stdc++.h>

typedef long long ll;

int main(){
    ll n;
    scanf("%lld", &n);
    int min = INT_MAX;
    for (int i = 1; i <= 100000; ++ i){
        for (int j = std::max(1, i - 10); j <= i + 10; ++ j){
            ll s1 = 1ll * (i + i + j - 1) * j - (i + j - 1);
            if (s1 >= n){
                min = std::min(min, 2 * i + 4 * j);
            }
            ll s2 = (1ll * (i + 1 + i + 1 + j - 1) * j + 1ll * (i + i + j) * (j + 1)) / 2 - (i + j);
            if (s2 >= n){
                min = std::min(min, 2 * i + 1 + 2 * (2 * j + 1));
            }
        }
    }
    printf("%d\n", min);
    return 0;
}
