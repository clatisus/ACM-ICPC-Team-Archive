#include<bits/stdc++.h>

typedef long long ll;

void solve(ll a, ll b, int test){
    ll ans1 = 0, ans2 = 0;
    for (int i = 0; i <= 60; ++ i){
        if (a >> (i + 1) != b >> (i + 1)){
            ans1 |= 1ll << i;
        }
        else{
            int abit = a >> i & 1, bbit = b >> i & 1;
            if (abit != bbit){
                ans1 |= 1ll << i;
            }
            else{
                ans1 |= (ll) abit << i;
                ans2 |= (ll) abit << i;
            }
        }
    }
    printf("Case %d: %lld %lld\n", test, ans1, ans2);
}

int main(){
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++ i){
        ll a, b;
        scanf("%lld%lld", &a, &b);
        solve(a, b, i);
    }
    return 0;
}

