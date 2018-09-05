// 多项式模板（取模）
// 使用方法见多项式模板 

#include<bits/stdc++.h>
#include"ntt.cpp"

typedef long long ll;

// 据说会快 orz 
inline int multmod(int x,int y, int MOD) {
    int ret; 
    __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(MOD));
    return ret;
}

// const int moder = 998244353;
// const int root = 3;
// const int invroot = (moder + 1) / root;
const int N = 1000010;

int invn[N];

/*
void init(){
    invn[0] = 0, invn[1] = 1;
    for (int i = 2; i < N; ++i) {
        invn[i] = (moder - 1ll * (moder / i) * invn[moder % i] % moder) % moder;
    }
}
*/

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
    
    // 相当于乘以 x ^ dis
    poly operator << (const int &dis) const {
        poly ret(len + dis);
        std::copy(a.begin(), a.begin() + len + 1, ret.a.begin() + dis);
        return ret;
    }
    
    // 相当于除以 x ^ dis
    poly operator >> (const int &dis) const {
        if (dis > len) return poly(-1);
        int retlen = len - dis;
        poly ret(retlen);
        std::copy(a.begin(), a.begin() + retlen + 1, ret.a.begin());
        return ret;
    }
    
    int value(int x) {
        int now = 1, ret = 0;
        for (int i = 0; i <= len; ++i) {
            ret = (ret + 1ll * a[i] * now) % moder;
            now = 1ll * now * x % moder;
        }
        return ret;
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
    
    poly operator - () const {
        poly ret(len);
        for (int i = 0; i <= len; ++i){
            ret.a[i] = a[i] ? moder - a[i] : 0;
        }
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
    
    poly operator * (const int &p) const {
        int q = (p % moder + moder) % moder;
        if (!q) return poly(-1);
        poly ret(len);
        for (int i = 0; i <= len; ++i) {
            ret.a[i] = 1ll * a[i] * q % moder;
        }
        return ret;
    }
    
    friend poly operator * (const int &q, const poly &p) { return p * q; }
    poly &operator += (const poly &p) { return *this = *this + p; }
    poly &operator -= (const poly &p) { return *this = *this - p; }
    poly &operator *= (const poly &p) { return *this = *this * p; }
    poly &operator *= (const int &p) { return *this = *this * p; }
    
    //表示求最高次为n的inv，log和exp同理
    poly inv(int n) const {
        assert(~len && a[0]);
        poly ret(1);
        ret.a[0] = powermod(a[0], moder - 2);
        for (int nowprecision = 0; nowprecision < n; ) {
            nowprecision = nowprecision << 1 | 1;
            poly aux(*this, nowprecision), aux1 = ret;
            ret *= ret;
            ret.setlen(nowprecision);
            aux *= ret, aux.setlen(nowprecision);
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
            ret.a[i] = 1ll * a[i - 1] * invn[i] % moder;
        }
        return ret;
    }

    poly operator / (const poly &p) const {
        assert(~p.len);
        if (p.len > len) return poly(-1);
        poly a(*this), b(p);
        std::reverse(a.a.begin(), a.a.begin() + a.len + 1);
        std::reverse(b.a.begin(), b.a.begin() + b.len + 1);
        poly ret(b.inv(len - p.len));
        ret *= a;
        int retlen = len - p.len;
        ret.setlen(retlen);
        std::reverse(ret.a.begin(), ret.a.begin() + retlen + 1);
        return ret;
    }

    poly operator % (const poly &p) const { return *this - *this / p * p; }
    poly &operator /= (const poly &p) { return *this = *this / p; }
    poly &operator %= (const poly &p) { return *this = *this % p; }

    poly log(int n) const {
        assert(~len && a[0] == 1);
        poly aux(*this, n);
        poly ret = aux.der() * aux.inv(n - 1);
        ret.setlen(n - 1);
        return ret.integral();
    }

    poly exp(int n) const {
        assert(!~len || !a[0]);
        poly ret(0);
        ret.a[0] = 1;
        poly unit = ret;
        for (int nowprecision = 0; nowprecision < n; ){
            nowprecision = nowprecision << 1 | 1;
            poly aux(*this, nowprecision);
            ret *= unit - ret.log(nowprecision) + aux;
            ret.setlen(nowprecision);
        }
        ret.setlen(n);
        return ret;
    }

    template <typename T>
    poly power(T exp) const {
        poly ret(0), aux = this;
        ret.a[0] = 1;
        for ( ; exp; exp >>= 1){
            if (exp & 1){
                ret *= aux;
            }
            aux *= aux;
        }
        return ret;
    }
};
