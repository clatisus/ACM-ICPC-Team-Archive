#include<bits/stdc++.h>

class frac{
public:
    int zero, one;

    frac(int zero = 0, int one = 0):zero(zero), one(one){}

    bool operator <(const frac &f)const{
        return 1ll * one * f.zero < 1ll * zero * f.one;
    }

    frac operator +(const frac &f)const{
        return frac(zero + f.zero, one + f.one);
    }
};

const int N = 200010;
typedef std::pair <frac, int> pfi;
typedef long long ll;

int fa[N], last[N], suf[N], v[N], p[N];
frac f[N];

int find(int u){
    if (fa[u] == u) return u;
    fa[u] = find(fa[u]);
    f[u] = f[fa[u]];
    last[u] = last[fa[u]];
    return fa[u];
}

void unite(int u, int v){
    int _u = find(u), _v = find(v);
    if (_u == _v) return;
    fa[_u] = _v;
    f[_v] = f[_v] + f[_u];
    suf[last[_v]] = _u;
    last[_v] = last[_u];
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++ i){
        scanf("%d", &p[i]);
    }
    std::set <pfi> set;
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &v[i]);
        f[i] = frac(v[i] == 0, v[i] == 1);
        fa[i] = last[i] = i;
        if (i > 1){
            set.insert({f[i], i});
        }
    }
    while (set.size()){
        int u = set.begin() -> second;
        set.erase(set.begin());
        int v = p[u];
        if (find(v) > 1){
            set.erase({f[find(v)], find(v)});
        }
        unite(u, v);
        if (find(v) > 1){
            set.insert({f[find(v)], find(v)});
        }
    }
    ll ans = 0;
    int one = 0, x = 1;
    while (x){
        ans += v[x] ? 0 : one;
        one += v[x] == 1;
        x = suf[x];
    }
    printf("%lld\n", ans);
    return 0;
}
