#include <bits/stdc++.h>

const int N = 1010;
typedef long long ll;
typedef std::pair <int, int> pii;

int n;
int r[N], c[N], a[N], b[N], p[N];
int g[N], flag[N];
std::map <pii, ll> dp;

bool arrive(int r, int c, int gcd, int flag){
    if (!gcd){
        return !r && !c;
    }
    if (r % gcd == 0 && c % gcd == 0){
        if (!flag || ((r / gcd & 1) ^ (c / gcd & 1)) == 0){
            return true;
        }
    }
    return false;
}

ll dfs(int gcd, int flagu){
    if (arrive(r[0], c[0], gcd, flagu)){
        return 0;
    }
    if (dp.count({gcd, flagu})){
        return dp[{gcd, flagu}];
    }
    ll ans = -1;
    for (int i = 0; i < n; ++ i){
        if (!arrive(r[i] - r[0], c[i] - c[0], gcd, flagu)){
            continue;
        }
        int ngcd = std::__gcd(gcd, g[i]);
        int nflag;
        if (!gcd){
            nflag = flag[i];
        }
        else if (flagu == flag[i]){
            nflag = flagu;
        }
        else{
            if ((gcd / ngcd % 2 + (flagu ? gcd : 0) / ngcd % 2) % 2 || (a[i] / ngcd % 2 + b[i] / ngcd % 2) % 2){
                nflag = 0;
            }
            else{
                nflag = 1;
            }
        }
        if (gcd == ngcd && flagu <= nflag){
            continue;
        }
        ll nans = dfs(ngcd, nflag);
        if (nans == -1){
            continue;
        }
        nans += p[i];
        if (ans == -1 || ans > nans){
            ans = nans;
        }
    }
    return dp[{gcd, flagu}] = ans;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        scanf("%d%d%d%d%d", &r[i], &c[i], &a[i], &b[i], &p[i]);
    }
    for (int i = 0; i < n; ++ i){
        g[i] = std::__gcd(a[i], b[i]);
        flag[i] = a[i] / g[i] % 2 && b[i] / g[i] % 2;
    }
    ll ans = dfs(0, 0);
    printf("%lld\n", ans);
    return 0;
}
