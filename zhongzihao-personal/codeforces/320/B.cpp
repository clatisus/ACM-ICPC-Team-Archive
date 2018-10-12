#include<bits/stdc++.h>

const int N = 200010;
const int BIT = 62;
typedef long long ll;

int pre[N], suf[N];
int a[N];

int main(){
    int n, k, x;
    scanf("%d%d%d", &n, &k, &x);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++ i){
        pre[i] = pre[i - 1] | a[i];
    }
    for (int i = n; i >= 1; -- i){
        suf[i] = suf[i + 1] | a[i];
    }
    ll max = 0;
    for (int i = 1; i <= n; ++ i){
        ll ans = a[i];
        for (int j = 0; j < k; ++ j){
            ans *= x;
        }
        ans |= pre[i - 1] | suf[i + 1];
        max = std::max(max, ans);
    }
    printf("%lld\n", max);
    return 0;
}
