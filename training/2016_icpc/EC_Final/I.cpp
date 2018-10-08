#include<bits/stdc++.h>

const double PI = acos(-1.0);
inline double sqr(double n){return n * n;}
const int MAX = 20;
typedef long long ll;
const int moder = (int) 1e9 + 7;
const int N = 20010;

struct comp{
    double real, imag;

    comp(double real = 0, double imag = 0):real(real), imag(imag){}

    comp operator +(const comp &c)const{
        return comp(real + c.real, imag + c.imag);
    }

    comp operator -(const comp &c)const{
        return comp(real - c.real, imag - c.imag);
    }

    comp operator *(const comp &c)const{
        return comp(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
    }

    comp operator *(const double &c)const{
        return comp(real * c, imag * c);
    }

    comp conj()const{
        return comp(real, -imag);
    }
};

comp w[2][1 << MAX];
int inv[N];

void init(){
    for (int i = 0; i < 1 << MAX; ++i){
        double angle = 1.0 * i / (1 << (MAX - 1)) * PI;
        for (int type = -1; type <= 1; type += 2){
            w[!~type][i] = comp(std::cos(angle), type * std::sin(angle));
        }
    }
    for (int i = 1; i < N; ++ i){
        inv[i] = i == 1 ? 1 : moder - 1ll * (moder / i) * inv[moder % i] % moder;
    }
}

void FFT(std::vector <comp> &a, int len, int type){
    for (int i = 1, j = 0; i < len - 1; ++i){
        for (int s = len; j ^= s >>= 1, ~j & s; )
            ;
        if (i < j){
            std::swap(a[i], a[j]);
        }
    }
    for (int i = 2, d = 1; i <= len; i <<= 1, ++d){
        for (int j = 0; j < len; j += i){
            auto u = a.begin() + j;
            for (int k = 0; k < i / 2; ++k){
                comp s = u[k], t = w[type][k << (MAX - d)] * u[k + i / 2];
                u[k] = s + t, u[k + i / 2] = s - t;
            }
        }
    }
    if (type == 0) return;
    double inv = 1.0 / len;
    for (int i = 0; i < len; ++i){
        a[i] = a[i] * inv;
    }
}

void FFTcomb(std::vector <comp> &a, std::vector <comp> &b){
    int n = a.size();
    FFT(a, n, 0);
    for (int i = 0; i < n; ++ i){
        b[i] = a[i ? n - i : 0].conj();
    }
    for (int i = 0; i < n; ++ i){
        comp tmp1 = (a[i] + b[i]) * comp(0.5, 0);
        comp tmp2 = (a[i] - b[i]) * comp(0, -0.5);
        a[i] = tmp1, b[i] = tmp2;
    }
}

struct poly{
    int len;
    std::vector <int> a;

    poly():len(0){}
    poly(int len):len(len){a.resize(len + 1);}

    int &operator [](const int &n){assert(n >= 0 && n <= len); return a[n];}

    void resize(int n){
        a.resize(n + 1);
        len = n;
    }

    poly operator * (const poly &p)const{
        int mod = std::sqrt(moder) + 2;
        int n = len + p.len;
        int lenret = 1;
        for ( ; lenret <= n; lenret <<= 1)
            ;
        std::vector <comp> aux(lenret), aux1(lenret), aux2(lenret), aux3(lenret);
        for (int i = 0; i <= len; ++ i){
            aux[i] = comp(a[i] / mod, a[i] % mod);
        }
        for (int i = 0; i <= p.len; ++ i){
            aux2[i] = comp(p.a[i] / mod, p.a[i] % mod);
        }
        FFTcomb(aux, aux1);
        FFTcomb(aux2, aux3);
        for (int i = 0; i < lenret; ++ i){
            comp tmp1 = aux[i] * aux2[i] + comp(0, 1) * aux1[i] * aux3[i];
            comp tmp2 = aux1[i] * aux2[i] + comp(0, 1) * aux[i] * aux3[i];
            aux[i] = tmp1, aux1[i] = tmp2;
        }
        FFT(aux, lenret, 1);
        FFT(aux1, lenret, 1);
        poly ret(n);
        for (int i = 0; i <= n; ++ i){
            int x = (ll) std::round(aux[i].real) % moder;
            int y = (ll) std::round(aux[i].imag) % moder;
            int u = (ll) std::round(aux1[i].real) % moder;
            int v = (ll) std::round(aux1[i].imag) % moder;
            ret.a[i] = (1ll * x * mod * mod + y + 1ll * (u + v) * mod) % moder;
        }
        return ret;
    }
};

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

int c[N];
bool dp[N];
int last[N];

void add(int &a, int b){
    a += b;
    a -= a >= moder ? moder : 0;
}

poly mult(poly p, poly q, int sz){
    p = p * q;
    for (int i = sz; i <= p.len; ++ i){
        add(p[i % sz], p[i]);
    }
    p.resize(sz - 1);
    return p;
}

int solve(){
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    int gcd = 0;
    memset(dp, 0, sizeof(dp));
    dp[0] = true;
    for (int i = 0; i < m; ++ i){
        scanf("%d", &c[i]);
        gcd = std::__gcd(gcd, c[i]);
        for (int j = 0; j + c[i] < N; ++ j){
            dp[j + c[i]] = dp[j + c[i]] || dp[j];
        }
    }
    poly pol(1), ret(0);
    pol[0] = 100 - p, pol[1] = p;
    ret[0] = 1;
    int exp = n;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = mult(ret, pol, gcd);
        }
        pol = mult(pol, pol, gcd);
    }
    int ans = 0;
    for (int i = 1; i < gcd; ++ i){
        ans = (ans + 1ll * (gcd - i) * ret[i]) % moder;
    }
    if (m == 1){
        return ans;
    }
    std::sort(c, c + m, std::greater <int>());
    for (int i = c[0] * c[1]; i >= 0; -- i){
        last[i] = dp[i] ? i : last[i + 1];
    }
    int comb = 1, pow = powermod(100 - p, n);
    for (int i = 0; i < c[0] * c[1] && i <= n; ++ i){
        pow = p == 100 && i == n ? powermod(p, n) : pow;
        int coe = 1ll * comb * pow % moder;
        ans = (ans + 1ll * coe * ((last[i] - i) - (i % gcd ? (gcd - i % gcd) : 0))) % moder;
        comb = 1ll * comb * (n - i) % moder * inv[i + 1] % moder;
        pow = 1ll * pow * inv[100 - p] % moder * p % moder;
    }
    ans += ans < 0 ? moder : 0;
    return ans;
}

int main(){
    init();
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
