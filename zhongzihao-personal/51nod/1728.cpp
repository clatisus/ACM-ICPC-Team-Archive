#include<bits/stdc++.h>

typedef long long ll;
const int MAX = 22;
const int moder = 985661441;
const int root = 3;
const int invroot = (moder + 1) / root;
const int inv2 = (moder + 1) >> 1;
const int N = 1000010;

int w[2][1 << MAX];
int inv[N], fac[N], invf[N];

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

void init(){
    w[0][0] = w[1][0] = 1;
    w[0][1] = powermod(root, (moder - 1) >> MAX);
    for (int i = 2; i < (1 << MAX); ++i){
        w[0][i] = 1ll * w[0][i - 1] * w[0][1] % moder;
    }
    for (int i = 1; i < (1 << MAX); ++i){
        w[1][(1 << MAX) - i] = w[0][i];
    }
    invf[0] = fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
        fac[i] = 1ll * fac[i - 1] * i % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
}

void NTT(std::vector <int> &a, int len, int type){
    for(int i = 1, j = 0; i < len - 1; ++i){
        for(int s = len; j ^= (s >>= 1), ~j & s; )
            ;
        if(i < j){
            std::swap(a[i], a[j]);
        }
    }
    for (int i = 2, d = 1; i <= len; i <<= 1, ++d){
        for (int j = 0; j < len; j += i){
            auto u = a.begin() + j;
            for (int k = 0; k < i / 2; ++k){
                int t = 1ll * w[type][k << (MAX - d)] * u[k + i / 2] % moder;
                u[k + i / 2] = u[k] - t + (u[k] - t < 0 ? moder : 0);
                u[k] += t; u[k] -= u[k] >= moder ? moder : 0;
            }
        }
    }
    if (type == 0) return;
    int inv = powermod(len, moder - 2);
    for (int i = 0; i < len; ++i){
        a[i] = 1ll * a[i] * inv % moder;
    }
}

struct poly{
    std::vector<int> a;
    int len;
    
    poly() : len(-1) {}
    poly(int len) : len(len) { a.resize(len + 1); }
    poly(const poly &p, int len) : len(len) { 
        a.resize(len + 1); 
        for (int i = 0; i <= len; ++i) {
            a[i] = i > p.len ? 0 : p.a[i];
        }
    }
    
    int &operator [] (int n) { assert(n >= 0 && n <= len); return a[n]; }
    
    void setlen(int len) {
        a.resize(len + 1);
        this->len = len;
    }
    
    poly operator + (const poly &p) const {
        poly ret(*this, std::max(len, p.len));
        for (int i = 0; i <= p.len; ++i) {
            ret.a[i] += p.a[i];
            ret.a[i] -= ret.a[i] >= moder ? moder : 0;
        }
        for ( ; ~ret.len && !ret.a[ret.len]; --ret.len)
            ;
        return ret;
    }
    
    poly operator - (const poly &p) const {
        poly ret(*this, std::max(len, p.len));
        for (int i = 0; i <= p.len; ++i) {
            ret.a[i] -= p.a[i];
            ret.a[i] += ret.a[i] < 0 ? moder : 0;
        }
        for ( ; ~ret.len && !ret.a[ret.len]; --ret.len)
            ;
        return ret;
    }
    
    poly operator * (const poly &p) const {
        if (!~len || !~p.len) return poly(-1);
        int n = len + p.len;
        int lenret = 1;
        for ( ; lenret <= n; lenret <<= 1)
            ;
        poly ret(*this, lenret);
        std::vector<int> aux(lenret);
        std::copy(p.a.begin(), p.a.begin() + p.len + 1, aux.begin());
        NTT(ret.a, lenret, 0);
        NTT(aux, lenret, 0);
        for (int i = 0; i < lenret; ++i) {
            ret.a[i] = 1ll * ret.a[i] * aux[i] % moder;
        }
        NTT(ret.a, lenret, 1);
        ret.len = n;
        return ret;
    }
    
    //表示求最高次为n的inv，log和exp同理
    poly inv(int n) const {
        assert(~len && a[0]);
        poly ret(1);
        ret.a[0] = powermod(a[0], moder - 2);
        for (int noweps = 0; noweps < n; ) {
            noweps = noweps << 1 | 1;
            poly aux(*this, noweps), aux1 = ret;
            ret = ret *ret;
            ret.setlen(noweps);
            aux = aux * ret, aux.setlen(noweps);
            ret = aux1 + aux1 - aux;
        }
        ret.setlen(n);
        return ret;
    }

    poly der() const {
        if (!~len) return poly(-1);
        poly ret(len - 1);
        for (int i = 0; i < len; ++i){
            ret.a[i] = 1ll * a[i + 1] * (i + 1) % moder;
        }
        return ret;
    }

    poly integral() const {
        poly ret(len + 1);
        for (int i = len + 1; i; --i){
            ret.a[i] = 1ll * a[i - 1] * ::inv[i] % moder;
        }
        return ret;
    }

    poly log(int n) const {
        assert(~len && a[0] == 1);
        poly aux(*this, n);
        poly ret = aux.der() * aux.inv(n - 1);
        ret.setlen(n - 1);
        return ret.integral();
    }

    poly exp(int n) const {
        assert(!~len || !a[0]);
        poly ret(0), invaux(0);
        ret.a[0] = invaux.a[0] = 1;
        poly unit = ret;
        for (int noweps = 0; noweps < n; ){
            noweps = noweps << 1 | 1;
            //inv
            poly aux1 = invaux * invaux;
            poly aux = ret * aux1;
            aux.setlen(noweps);
            aux = invaux + invaux - aux;
            //log
            aux = aux * ret.der();
            aux.setlen(noweps - 1);
            aux = aux.integral();
            //exp
            ret = ret * (unit - aux + poly(*this, noweps));
            ret.setlen(noweps);
            //real inv
            aux = ret * aux1;
            aux.setlen(noweps);
            invaux = invaux + invaux - aux;
        }
        ret.setlen(n);
        return ret;
    }
};

int main(){
    init();
    for (int i = 2; i * i <= moder; ++ i){
        if ((moder - 1) % i == 0){
            assert(powermod(root, i) != 1);
            assert(powermod(root, (moder - 1) / i) != 1);
        }
    }
    poly p1(N);
    for (int i = 1; i <= N; ++ i){
        p1[i] = invf[i - 1];
    }
    p1 = p1.exp(p1.len);
    poly p2 = p1;
    for (int i = p2.len; i >= 1; -- i){
        p2[i] = p2[i - 1];
    }
    p2[0] = 0;
    p2 = p2.exp(N * 2 / 3);
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        int s, k;
        scanf("%d%d", &s, &k);
        printf("Case #%d: %lld\n", i, k == 1 ? 1 : k == 2 ? 1ll * fac[s] * p1[s] % moder : 1ll * fac[s] * p2[s] % moder);
    }
    return 0;
}
