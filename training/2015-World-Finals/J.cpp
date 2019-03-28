#include<bits/stdc++.h>

const int N = 500010;
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
        return comp(real * c.real - imag * c.imag, real * c.imag + c.real * imag);
    }

    comp operator *(const double &c)const{
        return comp(real * c, c * imag);
    }
};

comp w[2][1 << MAX];
ll ans[N];

typedef std::pair <ll, int> pii;
const int SMAX = 1 << 19;
pii seg[SMAX << 1];

pii query(int l, int r){
    pii ret = {-1, 0};
    for (l += SMAX, r += SMAX + 1; l < r; l >>= 1, r >>= 1){
        if (l & 1) ret = std::max(ret, seg[l ++]);
        if (r & 1) ret = std::max(ret, seg[-- r]);
    }
    return ret;
}

void init(){
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
    if (type == 0){
        return;
    }
    double inv = 1.0 / len;
    for (int i = 0; i < len; ++ i){
        a[i] = a[i] * inv;
    }
}

int min[N], fac[N], cnt[N];
std::vector <int> prime;

int main(){
    init();
    fac[1] = 1;
    for (int i = 2; i < N; ++ i){
        if (!min[i]){
            min[i] = i;
            prime.push_back(i);
            fac[i] = 2;
            cnt[i] = 1;
        }
        for (auto u : prime){
            int k = u * i;
            if (k >= N) break;
            min[k] = u;
            if (i % u == 0){
                cnt[k] = cnt[i] + 1;
                fac[k] = fac[i] / cnt[k] * (cnt[k] + 1);
                break;
            }
            cnt[k] = 1;
            fac[k] = fac[i] * 2;
        }
    }
    std::vector <comp> vec(1 << MAX);
    for (int i = 1; i < N; ++ i){
        vec[i] = comp(fac[i], 0);
    }
    FFT(vec, 1 << MAX, 0);
    for (int i = 0; i < 1 << MAX; ++ i){
        vec[i] = vec[i] * vec[i];
    }
    FFT(vec, 1 << MAX, 1);
    for (int i = 0; i < N; ++ i){
        ans[i] = (ll) std::round(vec[i].real);
        seg[SMAX + i] = {ans[i], -i};
    }
    for (int i = SMAX - 1; i; -- i){
        seg[i] = std::max(seg[i << 1], seg[i << 1 | 1]);
    }
    int n;
    scanf("%d", &n);
    while (n --){
        int l, r;
        scanf("%d%d", &l, &r);
        pii p = query(l, r);
        printf("%d %lld\n", -p.second, p.first);
    }
    return 0;
}
