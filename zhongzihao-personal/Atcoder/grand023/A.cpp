#include<bits/stdc++.h>

typedef long long ll;

const int N = 200010;

int a[N];
ll pre[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        pre[i] = pre[i - 1] + a[i];
    }
    std::map <ll, int> Hash;
    for (int i = 0; i <= n; ++ i){
        ++ Hash[pre[i]];
    }
    ll ans = 0;
    for (auto u : Hash){
        ans += 1ll * u.second * (u.second - 1) >> 1;
    }
    printf("%lld\n", ans);
    return 0;
}
