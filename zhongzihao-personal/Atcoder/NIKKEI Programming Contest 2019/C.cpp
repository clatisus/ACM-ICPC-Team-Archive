#include<bits/stdc++.h>

typedef long long ll;
const int N = 100010;
typedef std::pair <int, int> pii;

int a[N], b[N];
pii p[N];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d%d", &a[i], &b[i]);
        p[i] = {a[i] + b[i], i};
    }
    std::sort(p, p + n, std::greater <pii>());
    ll ans = 0;
    for (int i = 0; i < n; ++ i){
        if (i & 1){
            ans -= b[p[i].second];
        }
        else{
            ans += a[p[i].second];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
