#include<bits/stdc++.h>

typedef long long ll;

ll sum(int a1, int an, int n){
    return 1ll * (a1 + an) * n / 2;
}

int J1, j2, b1, b2;

bool check(int j, int b){
    return J1 <= j && j <= j2 && b1 <= b && b <= b2;
}

void solve(){
    scanf("%d%d%d%d", &J1, &j2, &b1, &b2);
    ll big = 0;
    int min = std::max(J1, b1);
    int max = std::min(j2, b2);
    if (min <= max){
        big += sum(min - J1 + 1, max - J1 + 1, max - min + 1);
        big += 1ll * (b2 - max) * (j2 - J1 + 1);
    }
    else if (J1 < b1){
        big += 1ll * (j2 - J1 + 1) * (b2 - b1 + 1);
    }
    big -= check(2, 3);
    big += check(3, 2);
    if (J1 == 1){
        big -= b2 - std::max(2, b1) + 1;
    }
    if (b1 == 1){
        big += j2 - std::max(2, J1) + 1;
    }
    int l = std::max(b1, J1), r = std::min(b2, j2);
    if (l <= r){
        big -= r - l + 1;
    }
    big -= check(2, 4);
    ll total = 1ll * (b2 - b1 + 1) * (j2 - J1 + 1);
    if (l <= r){
        total -= r - l + 1;
    }
    total -= check(4, 2);
    total -= check(2, 4);
    ll gcd = std::__gcd(big, total);
    big /= gcd, total /= gcd;
    printf("%lld/%lld %lld/%lld\n", big, total, total - big, total);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

