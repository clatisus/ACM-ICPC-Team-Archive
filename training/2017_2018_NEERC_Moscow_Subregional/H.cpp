#include<bits/stdc++.h>

typedef long long ll;
const int N = 100010;

ll sum(ll l, ll r){
    if (l > r){
        return 0;
    }
    l = std::max(l, 0ll);
    r = std::max(r, 0ll);
    return (l + r) * (r - l + 1) / 2;
}

ll getmax(ll l, ll r, ll n){
    if (l > r){
        std::swap(l, r);
    }
    if (r - l + 1 > n) return -1;
    ll high = (l + r + n - 1) >> 1;
    if (!(l + r + n & 1)){
        return sum(l + 1, high) + sum(r + 1, high);
    }
    else{
        ll ret = sum(l + 1, high) + sum(r + 1, high - 1);

        if (high == r){
            ret -= r;
        }
        return ret;
    }
}

ll getmin(ll l, ll r, ll n){
    if (l > r){
        std::swap(l, r);
    }
    if (r - l + 1 > n) return -1;
    ll low = (l + r - n + 2) >> 1;
    if (!(l + r + n & 1)){
        return sum(low, l - 1) + sum(low, r - 1);
    }
    else{
        ll ret = sum(low, l - 1) + sum(low + 1, r - 1);
        return ret;
    }
}

ll a[N], b[N];

int main(){
    ll t, n, m;
    scanf("%lld%lld%lld", &t, &n, &m);
    ll max = 0, min = 0;
    for (int i = 0; i < m; ++ i){
        scanf("%lld%lld", &a[i], &b[i]);
        max += b[i];
        min += b[i];
    }
    for (int i = 0; i < m - 1; ++ i){
        ll x = getmax(b[i], b[i + 1], a[i + 1] - a[i] + 1);
        if (x == -1){
            puts("No");
            return 0;
        }
        max += x;
        x = getmin(b[i], b[i + 1], a[i + 1] - a[i] + 1);
        if (x == -1){
            puts("No");
            return 0;
        }
        min += x;
    }
    max += sum(b[0] + 1, b[0] + a[0] - 1) + sum(b[m - 1] + 1, b[m - 1] + (n - a[m - 1]));
    min += sum(b[0] - (a[0] - 1), b[0] - 1) + sum(b[m - 1] - (n - a[m - 1]), b[m - 1] - 1);
    puts(max >= t && t >= min ? "Yes" : "No");
    return 0;
}

