#include <bits/stdc++.h>

const int N = 100010;
const int BIT = 60;
typedef long long ll;

ll x[N];

void solve(){
    int n;
    scanf("%d", &n);
    ll sum = 0;
    for (int i = 0; i < n; ++ i){
        scanf("%lld", &x[i]);
        sum ^= x[i];
    }
    for (int i = 0; i < n; ++ i){
        x[i] &= sum;
    }
    int now = 0;
    for (int i = BIT; i >= 0; -- i){
        for (int j = now; j < n; ++ j){
            if (x[j] >> i & 1){
                std::swap(x[now], x[j]);
                break;
            }
        }
        if (!(x[now] >> i & 1)){
            continue;
        }
        for (int j = 0; j < n; ++ j){
            if (j == now){
                continue;
            }
            if (x[j] >> i & 1) {
                x[j] ^= x[now];
            }
        }
        ++ now;
    }
    ll tot = 0;
    for (int i = 1; i < now; ++ i) {
        tot ^= x[i];
    }
    printf("%lld\n", (sum ^ tot) - tot);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
