#include <bits/stdc++.h>

typedef __int128 ll;
const int N = 5;

inline ll sqr(ll n){return n * n;}

int a[N];

void solve(){
    for (int i = 0; i < 3; ++ i){
        scanf("%d", &a[i]);
    }
    int x;
    scanf("%d", &x);
    std::sort(a, a + 3);
    ll max = 0;
    for (int i = 0; i < 3; ++ i){
        if (i < 2 && a[i] == a[i + 1]){
            continue;
        }
        ll sum = 0;
        for (int j = 0; j <= i; ++ j){
            sum += a[j];
        }
        ll k = - (i + 1), b = x + sum;
        ll left = a[i], right = i == 2 ? LLONG_MAX : a[i + 1];
        right = std::min(right, b / -k);
        if (i == 2){
            ++ k;
        }
        else{
            b += a[2];
        }
        ll aa = sqr(k), bb = 2 * k * b, cc = sqr(b);
        bb += 7;
        if (i >= 1){
            aa += 1;
        }
        else{
            cc += sqr(a[1]);
        }
        if (i >= 0){
            aa += 1;
        }
        else{
            cc += sqr(a[0]);
        }
        if (left <= right){
            max = std::max(max, aa * sqr(left) + bb * left + cc);
            max = std::max(max, aa * sqr(right) + bb * right + cc);
        }
    }
    printf("%lld\n", (long long) max);
}

int main(){
    int n;
    scanf("%d", &n);
    while (n --){
        solve();
    }
    return 0;
}
