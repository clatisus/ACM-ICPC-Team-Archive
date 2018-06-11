#include <bits/stdc++.h>

template <class T> inline void read(T&x){
    static char buf[233], *stop;
    scanf("%s", buf);
    x = strtod(buf, &stop);
}

const int max_N = (int)2e5 + 21;
const int mod = (int)1e9 + 7;

inline int qpow(int x, int k){
    int res = 1;
    for(;k;x=1ll*x*x%mod,k>>=1)
        if(k & 1) res = 1ll*res*x%mod;
    return res;
}

int T, fac[max_N], inv[max_N], _fac[max_N], n, f[max_N], g[max_N];

bool vis[max_N];

void testCase(){
    read(n);
    for(int i=1;i<=n;++i) read(f[i]), vis[i] = false;
    int ans = fac[n];
    for(int i=1;i<=n;++i) if(!vis[i]){
        int cnt = 0;
        for(int j=i;j<=n;j=f[j]) ++ cnt, vis[j] = true;
        ans = 1ll*ans*_fac[cnt]%mod;
        ans = 1ll*ans*g[cnt]%mod;
    }
    printf("%d\n", ans);
}

int main(){
    inv[1] = 1;
    for(int i=2;i<max_N;++i){
        inv[i] = 1ll*(mod/i)*inv[mod%i]%mod;
        if(inv[i]) inv[i] = mod - inv[i];
    }
    fac[0] = _fac[0] = 1;
    for(int i=1;i<max_N;++i){
        fac[i] = 1ll*fac[i-1]*i%mod;
        _fac[i] = 1ll*_fac[i-1]*inv[i]%mod;
    }
    for(int i=1;i<max_N;++i) g[i] = qpow(i+1, i-1);
    for(read(T);T--;testCase());
    return 0;
}
