#include<bits/stdc++.h>

const int N = 1000000;
const int moder = 1e6 + 3;
const double PI = std::acos(-1.0);
inline double sqr(double n){return n * n;}
const int MAX = 20;
typedef long long ll;

int fac[N], inv[N];
int l[N], t[N];

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

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int comb(int n, int m){
    return 1ll * fac[n] * inv[m] % moder * inv[n - m] % moder;
}

void init(){
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[N - 1] = powermod(fac[N - 1], moder - 2);
    for (int i = N - 1; i; -- i){
        inv[i - 1] = 1ll * inv[i] * i % moder;
    }
    for (int i = 0; i < 1 << MAX; ++ i){
        double angle = 1.0 * i / (1 << (MAX - 1)) * PI;
        for (int type = -1; type <= 1; type += 2){
            w[!~type][i] = comp(std::cos(angle), type * std::sin(angle));
        }
    }
}

void FFT(std::vector <comp> &a, int len, int type){
    for (int i = 1, j = 0; i < len - 1; ++ i){
        for (int s = len; j ^= s >>= 1, ~j & s; )
            ;
        if (i < j){
            std::swap(a[i], a[j]);
        }
    }
    for (int i = 2, d = 1; i <= len; i <<= 1, ++ d){
        for (int j = 0; j < len; j += i){
            auto u = a.begin() + j;
            for (int k = 0; k < i / 2; ++ k){
                comp s = u[k], t = w[type][k << (MAX - d)] * u[k + i / 2];
                u[k] = s + t, u[k + i / 2] = s - t;
            }
        }
    }
    if (type == 0) return;
    double inv = 1.0 / len;
    for (int i = 0; i < len; ++ i){
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
    std::vector <int> a;
    int len;

    poly():len(-1){}
    poly(int len):len(len){a.resize(len + 1);}

    int &operator [](const int &n){return a[n];}

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

int main(){
    init();
    int n, a, b, c;
    scanf("%d%d%d%d", &n, &a, &b, &c);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &l[i]);
    }
    for (int i = 0; i < n; ++ i){
        scanf("%d", &t[i]);
    }
    int ans = 0;
    for (int i = 0; i < n - 1; ++ i){
        ans = (ans + 1ll * comb(i + n - 2, i) * powermod(a, n - 1) % moder * powermod(b, i) % moder * l[n - i - 1]) % moder;
        ans = (ans + 1ll * comb(i + n - 2, i) * powermod(b, n - 1) % moder * powermod(a, i) % moder * t[n - i - 1]) % moder;
    }
    poly p(n - 2), q(n - 2);
    for (int i = 0; i <= n - 2; ++ i){
        p[i] = 1ll * powermod(a, i) * inv[i] % moder;
    }
    for (int i = 0; i <= n - 2; ++ i){
        q[i] = 1ll * powermod(b, i) * inv[i] % moder;
    }
    p = p * q;
    for (int i = 0; i <= (n - 2) << 1; ++ i){
        ans = (ans + 1ll * p[i] * c % moder * fac[i]) % moder;
    }
    printf("%d\n", ans);
    return 0;
}
