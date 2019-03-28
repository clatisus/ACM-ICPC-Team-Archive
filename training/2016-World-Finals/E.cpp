#include<bits/stdc++.h>

typedef long long ll;
const int N = 1000010;
const ll INF = 2e18;

ll mult(ll a, ll b){
    if (!a || !b) return 0;
    return a <= INF / b ? a * b : INF;
}

ll add(ll a, ll b){
    return std::min(a + b, INF);
}

int digit[N];

ll calc(int dcnt, ll base){
    ll ret = 0;
    for (int i = 0; i < dcnt; ++ i){
        ret = add(mult(ret, base), digit[i]);
    }
    return ret;
}

int main(){
    ll y, l;
    scanf("%lld%lld", &y, &l);
    ll tmpl = l;
    int dcnt = 0;
    for ( ; tmpl; tmpl /= 10){
        digit[dcnt ++] = tmpl % 10;
    }
    std::reverse(digit, digit + dcnt);
    ll left = 10, right = INF;
    while (left < right){
        ll mid = (left + right + 1) >> 1;
        if (calc(dcnt, mid) <= y){
            left = mid;
        }
        else{
            right = mid - 1;
        }
    }
    ll ans = 0;
    for (int i = 10, sz = std::min(1000000ll, left); i <= sz; ++ i){
        ll tmpy = y;
        int dcnt = 0;
        for ( ; tmpy; tmpy /= i){
            digit[dcnt ++] = tmpy % i;
        }
        bool flag = true;
        for (int j = 0; j < dcnt; ++ j){
            if (digit[j] >= 10){
                flag = false;
                break;
            }
        }
        if (flag){
            ans = i;
        }
    }
    for (int i = 0; i < 10; ++ i){
        for (int j = 0; j < 10; ++ j){
            for (int k = 0; k < 10; ++ k){
                for (int u = 0; u < 10; ++ u){
                    digit[0] = i, digit[1] = j, digit[2] = k, digit[3] = u;
                    if (calc(dcnt, 10) < l){
                        continue;
                    }
                    ll left = 10, right = INF;
                    while (left < right){
                        ll mid = (left + right) >> 1;
                        if (calc(dcnt, mid) < y){
                            left = mid + 1;
                        }
                        else{
                            right = mid;
                        }
                    }
                    if (calc(dcnt, left) == y){
                        ans = std::max(ans, left);
                    }
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
