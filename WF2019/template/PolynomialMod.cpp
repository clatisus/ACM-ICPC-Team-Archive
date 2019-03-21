// 多项式模板（取模）
// 使用方法见多项式模板 

#include<bits/stdc++.h>
#include"ntt.cpp"

typedef long long ll;

const int N = 1000010;

int invn[N];

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
    
    poly operator * (const int &p) const {
        int q = (p % moder + moder) % moder;
        if (!q) return poly(-1);
        poly ret(len);
        for (int i = 0; i <= len; ++i) {
            ret.a[i] = 1ll * a[i] * q % moder;
        }
        return ret;
    }

    //表示求最高次为n的inv，log和exp同理
    poly inv(int n) const {
        assert(~len && a[0]);
        poly ret(0);
        ret.a[0] = powermod(a[0], moder - 2);
        for (int noweps = 0; noweps < n; ) {
            noweps = noweps << 1 | 1;
            poly aux = poly(*this, noweps) * (ret * ret);
            aux.setlen(noweps);
            ret = ret + ret - aux;
        }
        ret.setlen(n);
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
        for (int noweps = 0; noweps < n; ){
            noweps = noweps << 1 | 1;
            ret *= unit - ret.log(noweps) + poly(*this, noweps);
            ret.setlen(noweps);
        }
        ret.setlen(n);
        return ret;
    }
};

poly aux[N];

void dfs(int l, int r, int id, std::vector <int> &vec){
    if (l == r){
        aux[id] = poly(1);
        aux[id][1] = 1;
        aux[id][0] = vec[l] ? moder - vec[l] : 0;
        return;
    }
    int mid = (l + r) >> 1;
    dfs(l, mid, id << 1, vec);
    dfs(mid + 1, r, id << 1 | 1, vec);
    aux[id] = aux[id << 1] * aux[id << 1 | 1];
}

std::vector <int> solve1(int l, int r, int id, poly p){
    if (l == r){
        return {p[0]};
    }
    int mid = (l + r) >> 1;
    std::vector <int> vec1 = solve1(l, mid, id << 1, p % aux[id << 1]);
    std::vector <int> vec2 = solve1(mid + 1, r, id << 1 | 1, p % aux[id << 1 | 1]);
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    return vec1;
}

std::vector <int> multivalue(poly p, std::vector <int> vec){
    int n = vec.size();
    dfs(0, n - 1, 1, vec);
    return solve1(0, n - 1, 1, p);
}

poly solve2(int l, int r, int id, std::vector <int> &vec){
    if (l == r){
        poly p(0);
        p[0] = vec[l];
        return p;
    }
    int mid = (l + r) >> 1;
    poly p1 = solve2(l, mid, id << 1, vec);
    poly p2 = solve2(mid + 1, r, id << 1 | 1, vec);
    return p1 * aux[id << 1 | 1] + p2 * aux[id << 1];
}

poly interpolation(std::vector <int> vecx, std::vector <int> vecy){
    int n = vecx.size() - 1;
    dfs(0, n, 1, vecx);
    poly p = aux[1].der();
    std::vector <int> vec = multivalue(p, vecx);
    for (int i = 0; i <= n; ++ i){
        vec[i] = 1ll * vecy[i] * powermod(vec[i], moder - 2) % moder;
    }
    return solve2(0, n, 1, vec);
}
