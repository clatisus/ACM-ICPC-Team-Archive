#include<bits/stdc++.h>

const double PI = acos(-1.0);
inline double sqr(double n){return n * n;}
const int MAX = 20;
typedef long long ll;

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
};

comp w[2][1 << MAX];

void init(){
    for (int i = 0; i < 1 << MAX; ++i){
        double angle = 1.0 * i / (1 << (MAX - 1)) * PI;
        for (int type = -1; type <= 1; type += 2){
            w[!~type][i] = comp(std::cos(angle), type * std::sin(angle));
        }
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

struct poly{
    int len;
    std::vector <comp> a;

    poly():len(0){}
    poly(int len):len(len){a.resize(len + 1);}

    comp &operator [] (const int &n){return a[n];}

    poly operator * (const poly &p)const{
        int lenret = p.len;
        std::vector <comp> aux(lenret);
        for (int i = 0; i < lenret; ++i){
            aux[i] = i > len ? 0 : a[i];
        }
        FFT(aux, lenret, 0);
        for (int i = 0; i < lenret; ++i){
            aux[i] = aux[i] * p.a[i];
        }
        FFT(aux, lenret, 1);
        poly ret(len << 1);
        for (int i = 0; i <= len << 1; ++i){
            ret.a[i] = aux[i];
        }
        return ret;
    }
};

const int N = 100100;

double a[N], b[N];
int Log[3][N], inv[3][N];
int p; 
poly pp[3];

void init2(){
    int ps[] = {13, 103, 100003};
    pp[0] = poly(1 << 5);
    pp[1] = poly(1 << 8);
    pp[2] = poly(1 << 18);
    memset(Log, -1, sizeof(Log));
    for (int j = 0; j < 3; ++ j){
        for (int i = 0, now = 1; Log[j][now] == -1; ++ i, now = (!j ? 2 : 5) * now % ps[j]){
            Log[j][now] = i;
            inv[j][i] = now;
        }
    }
    for (int i = 0; i < 3; ++ i){
        for (int j = 1; j < ps[i]; ++ j){
            pp[i][Log[i][j]] = std::pow(2, std::pow(std::sin(2 * PI * j / ps[i]), 3));
        }
    }
    FFT(pp[0].a, 1 << 5, 0);
    FFT(pp[1].a, 1 << 8, 0);
    FFT(pp[2].a, 1 << 18, 0);
}

void solve(){
    for (int i = 0; i < p; ++ i){
        scanf("%lf", &a[i]);
    }
    int sit = p == 13 ? 0 : p == 103 ? 1 : 2;
    for (int i = 0; i <= p; ++ i) b[i] = 0;
    poly q(p - 2);
    for (int i = 1; i <= p - 1; ++ i){
        q[Log[sit][i]] = comp(a[i], 0);
    }
    std::reverse(q.a.begin() + 1, q.a.begin() + p - 1);
    q = q * pp[sit];
    for (int i = p - 1; i <= q.len; ++ i){
        q[i % (p - 1)] = q[i % (p - 1)] + q[i];
    }
    for (int i = 0; i < p - 1; ++ i){
        b[inv[sit][i]] = q[i].real;
    }
    for (int i = 1; i < p; ++ i){
        b[i] += a[0];
    }
    for (int i = 0; i < p; ++ i){
        b[0] += a[i];
    }
    for (int i = 0; i < p; ++ i){
        printf("%.3f ", b[i]);
    }
    putchar('\n');
}

int main(){
    init();
    init2();
    while (scanf("%d", &p) != EOF){
        solve();
    }
    return 0;
}
