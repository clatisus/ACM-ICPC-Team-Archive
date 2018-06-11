#include <bits/stdc++.h>
 
using ll = long long;
 
const int max_N = (int)1e5 + 21;
 
int N;
 
ll C, x[max_N], _x[max_N], v[max_N];
 
ll sv[max_N], _sv[max_N];
 
ll f[max_N], g[max_N];
 
int main(){
    scanf("%d%lld", &N, &C);
    for(int i=1;i<=N;++i){
        scanf("%lld%lld", x+i, v+i);
        sv[i] = sv[i-1] + v[i];
    }
    for(int i=1;i<=N;++i){
        _x[i] = C - x[N-i+1];
        _sv[i] = _sv[i-1] + v[N-i+1]; 
    }
    ll ans = 0;
    for(int i=1;i<=N;++i){
        ans = std::max(ans, sv[i] - x[i]);
        ans = std::max(ans, _sv[i] - _x[i]);
    }
    for(int i=1;i<=N;++i){
        f[i] = std::max(f[i-1], sv[i] - 2*x[i]);
        g[i] = std::max(g[i-1], _sv[i] - 2*_x[i]); 
    }
    for(int i=1;i<=N;++i){
        ans = std::max(ans, f[N-i] + _sv[i] - _x[i]);
        ans = std::max(ans, g[N-i] + sv[i] - x[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
