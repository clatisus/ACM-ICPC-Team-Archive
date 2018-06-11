#include<bits/stdc++.h>

const int N = 200010;
typedef long long ll;

int a[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    if (a[0]){
        printf("-1\n");
        return 0;
    }
    for (int i = 0; i < n - 1; ++ i){
        if (a[i] < a[i + 1] - 1){
            printf("-1\n");
            return 0;
        }
    }
    ll ans = 0;
    for (int i = n - 1; i >= 0; -- i){
        if (i < n - 1 && a[i] == a[i + 1] - 1) continue;
        ans += a[i];
    }
    printf("%lld\n", ans);
    return 0;
}
