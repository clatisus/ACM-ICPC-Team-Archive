#include<bits/stdc++.h>

typedef long long ll;

int ex_euc(int a, int b, int &x, int &y){
    if (!b){
        x = 1, y = 0;
        return a;
    }
    int ret = ex_euc(b, a % b, x, y), tmp = y;
    y = x - a / b * y;
    x = tmp;
    return ret;
}

inline ll divide(ll a, ll b){return a / b - ((a ^ b) < 0 && a % b);}

inline int solve(int l1, int r1, int d1, int l2, int r2, int d2){
    //if (r1 < l2 || l1 > r2) return 0;
    int n1 = (r1 - l1) / d1;
    int n2 = (r2 - l2) / d2;
    int x, y;
    int gcd = ex_euc(d1, -d2, x, y);
    if (gcd < 0){
        gcd = -gcd, x = -x, y = -y;
    }
    int z = l2 - l1;
    if (z % gcd) return 0;
    d1 /= gcd, d2 /= gcd, z /= gcd;
    ll left = std::max(divide(-1ll * x * z + d2 - 1, d2), divide(-1ll * y * z + d1 - 1, d1));
    ll right = std::min(divide(n1 - 1ll * x * z, d2), divide(-1ll * y * z + n2, d1));
    return std::max(0ll, right - left + 1);
}

int main(){
    int l1, r1, d1, l2, r2, d2;
    scanf("%d%d%d%d%d%d", &l1, &r1, &d1, &l2, &r2, &d2);
    printf("%d\n", solve(l1, r1, d1, l2, r2, d2));
}
