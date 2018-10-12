#include<bits/stdc++.h>

const int N = 200010;

int a[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        a[i] -= i;
    }
    std::sort(a + 1, a + n + 1);
    long long ans = 0;
    for (int i = 1; i <= n; ++ i){
        ans += std::abs(a[i] - a[n + 1 >> 1]);
    }
    printf("%lld\n", ans);
    return 0;
}
