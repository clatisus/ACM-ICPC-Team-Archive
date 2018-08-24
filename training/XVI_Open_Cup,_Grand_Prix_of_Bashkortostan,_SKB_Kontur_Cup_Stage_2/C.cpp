#include<bits/stdc++.h>

typedef long long ll;

ll poweri(ll a, ll exp){
    ll ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret *= a;
        }
        a *= a;
    }
    return ret;
}

int main(){
    int n;
    scanf("%d", &n);
    if (n == 1){
        puts("0");
        return 0;
    }
    int ans = 0;
    for (int i = 1; i < n; ++ i){
        ans += n % i == 0;
    }
    for (int i = 2; i <= 30; ++ i){
        for (int j = 2; j <= n; ++ j){
            double dcoe = (pow(j, i) - 1) / (j - 1);
            if (dcoe > 1e9) continue;
            int coe = (poweri(j, i) - 1) / (j - 1);
            if (n % coe == 0){
                ++ ans;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
