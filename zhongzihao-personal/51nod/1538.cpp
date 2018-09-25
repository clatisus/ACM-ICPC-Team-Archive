#include<bits/stdc++.h>

typedef long long ll;
const int N = 1000010;
const int MAX = 20;
const int moder = 104857601;
const int root = 3;
const int invroot = (moder + 1) / root;

int w[2][1 << MAX];

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
    static poly div;
    
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
            ret = ret * ret;
            ret.setlen(noweps);
            aux = aux * ret, aux.setlen(noweps);
            ret = aux1 + aux1 - aux;
        }
        ret.setlen(n);
        return ret;
    }

    poly operator / (const poly &p) const {
        assert(~p.len);
        if (p.len > len) return poly(-1);
        poly a(*this);
        std::reverse(a.a.begin(), a.a.begin() + a.len + 1);
        poly ret = div * a;
        int retlen = len - p.len;
        ret.setlen(retlen);
        std::reverse(ret.a.begin(), ret.a.begin() + retlen + 1);
        return ret;
    }
    
    poly operator % (const poly &p)const{return *this - *this / p * p;}
};

poly poly::div;

int main(){
    for (int i = 2; i * i <= moder - 1; ++ i){
        if ((moder - 1) % i == 0){
            assert(powermod(root, i) != 1);
            assert(powermod(root, (moder - 1) / i) != 1);
        }
    }
    init();
    ll n, m;
    scanf("%lld%lld", &n, &m);
    int a1, A, B;
    scanf("%d%d%d", &a1, &A, &B);
    poly p(25000);
    int max = 0;
    for (int i = 0; i < n; ++ i){
        if (a1 <= p.len){
            ++ p[a1];
            max = std::max(max, a1);
        }
        a1 = (a1 * A + B) % 23333 + 1;
    }
    p[0] = moder - 1;
    poly q = p.inv(max);
    poly a(1), ret(0);
    a[1] = ret[0] = 1;
    poly mod(max);
    mod[max] = 1;
    for (int i = 1; i <= max; ++ i){
        mod[max - i] = (moder - p[i]) % moder;
    }
    poly::div = mod;
    std::reverse(poly::div.a.begin(), poly::div.a.begin() + poly::div.len + 1);
    poly::div = poly::div.inv(25000);
    for ( ; m > 0; m >>= 1){
        if (m & 1){
            ret = ret * a % mod;
        }
        a = a * a % mod;
    }
    ret.setlen(max);
    int ans = 0;
    for (int i = 0; i < max; ++ i){
        ans = (ans - 1ll * ret[i] * q[i]) % moder;
    }
    ans += ans < 0 ? moder : 0;
    printf("%d\n", ans);
    return 0;
}
