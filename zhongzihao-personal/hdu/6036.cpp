#include<bits/stdc++.h>

typedef long long ll;

const int N = 300010;
const int MAX = 20;
const int moder = 985661441;
const int root = 3;
const int invroot = (moder + 1) / root;

int fac[N], inv[N], invf[N];
int e[N], ans[N], ret[N], aux1[N], aux2[N];
int m, k;

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

int comb(int n, int m){
    return 1ll * fac[n] * invf[m] % moder * invf[n - m] % moder;
}

int w[2][1 << MAX];

void init(){
    w[0][0] = w[1][0] = 1;
    w[0][1] = powermod(root, (moder - 1) >> MAX);
    for (int i = 2; i < (1 << MAX); ++i){
        w[0][i] = 1ll * w[0][i - 1] * w[0][1] % moder;
    }
    for (int i = 1; i < (1 << MAX); ++i){
        w[1][(1 << MAX) - i] = w[0][i];
    }
    fac[0] = invf[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
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
    
    friend poly operator * (const int &q, const poly &p) { return p * q; }
    poly &operator += (const poly &p) { return *this = *this + p; }
    poly &operator -= (const poly &p) { return *this = *this - p; }
    poly &operator *= (const poly &p) { return *this = *this * p; }
    poly &operator *= (const int &p) { return *this = *this * p; }
    
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
    
    poly der() const {
        if (!~len) return poly(-1);
        poly ret(len - 1);
        for (int i = 0; i < len; ++i){
            ret.a[i] = 1ll * a[i + 1] * (i + 1) % moder;
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

std::vector <int> randvec(int len){
    while (true){
        std::vector <int> ret;
        for (int i = 0; i < len; ++ i){
            ret.push_back(((ll) rand() << 30 | rand()) % moder);
        }
        std::sort(ret.begin(), ret.end());
        bool flag = true;
        for (int i = 0; i < len - 1; ++ i){
            if (ret[i] == ret[i + 1]){
                flag = false;
                break;
            }
        }
        if (flag) return ret;
    }
    return {};
}

poly mult(poly f, poly g){
    int len = f.len + g.len;
    std::vector <int> vec = randvec(len + 1);
    std::vector <int> vec1 = multivalue(f, vec);
    std::vector <int> vec2 = multivalue(g, vec);
    for (int i = 0; i <= len; ++ i){
        vec1[i] = 1ll * vec1[i] * vec2[i] % moder;
    }
    return interpolation(vec, vec1);
}

int main(){
    srand((unsigned) time(NULL));
    init();
    int cnt = 0;
    while (scanf("%d%d", &m, &k) != EOF){
        int n = 0;
        for (int i = 0, p; i < m; ++ i){
            scanf("%d%d", &p, &e[i]);
            n += e[i];
        }
        poly f(n), g(n);
        for (int i = 1; i <= n; ++ i){
            int x = 1;
            for (int j = 0; j < m; ++ j){
                x = 1ll * x * comb(e[j] + i - 1, i - 1) % moder;
            }
            f[i] = 1ll * x * invf[i] % moder;
        }
        for (int i = 0; i <= n; ++ i){
            int x = i & 1 ? moder - invf[i] : invf[i];
            g[i] = x % moder;
        }
        if (cnt <= 40){
            f = mult(f, g);
        }
        else{
            f = f * g;
        }
        for (int i = 1; i <= n; ++ i){
            ans[i] = 1ll * f[i] * fac[i] % moder;
        }
        ans[n + 1] = 0;
        for (int i = 0; i < k; ++ i){
            ret[i] = 0;
        }
        for (int i = 1; i <= n; ++ i){
            aux1[0] = 1;
            for (int j = 1; j < k; ++ j){
                aux1[j] = 1ll * aux1[j - 1] * ans[i + 1] % moder;
            }
            aux2[k] = 1;
            for (int j = k - 1; ~j; -- j){
                aux2[j] = 1ll * aux2[j + 1] * ans[i] % moder;
            }
            for (int j = 0; j < k; ++ j){
                ret[j] = (ret[j] + 1ll * aux1[j] * aux2[j]) % moder;
            }
        }
        printf("Case #%d: ", ++ cnt);
        for (int j = 0; j < k; ++ j){
            printf("%d%c", ret[j], " \n"[j == k - 1]);
        }
    }
    return 0;
}
