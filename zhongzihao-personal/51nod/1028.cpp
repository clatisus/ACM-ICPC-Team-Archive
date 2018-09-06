#include<bits/stdc++.h>

typedef long long ll;
const int MAX = 20;
const int moder = 998244353;
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

struct Big{
    static const int base = 10;

    std::vector <int> a;
    int len, sig;
    
    Big():len(0), sig(0){}

    Big(const Big &b, const int &len):len(len), sig(b.sig){
        a.resize(len);
        for (int i = 0; i < len; ++ i){
            a[i] = i < b.len ? b.a[i] : 0;
        }
    }

    int operator [](int n){return n >= len ? 0 : a[n];}

    void resize(int len){
        this -> len = len;
        a.resize(len);
    }

    void read(){
        a.clear();
        len = 0;
        char ch;
        while (!isdigit(ch = getchar()) && ch != '-')
            ;
        if (ch == '-'){
            sig = -1;
        }
        else{
            sig = 1;
            a.push_back(ch - '0');
            ++ len;
        }
        while (isdigit(ch = getchar())){
            a.push_back(ch - '0');
            ++ len;
        }
        std::reverse(a.begin(), a.end());
        for ( ; len && !a[len - 1]; -- len)
            ;
        if (!len) sig = 0;
    }

    void write(){
        if (!sig) return (void) putchar('0');
        if (sig < 0) putchar('-');
        for (int i = len - 1; i >= 0; -- i){
            putchar(a[i] + '0');
        }
    }
    
    Big operator * (const Big &p)const{
        if (!sig || !p.sig) return Big();
        int n = len + p.len;
        int lenret = 1;
        for ( ; lenret < n; lenret <<= 1)
            ;
        Big ret(*this, lenret);
        std::vector <int> aux(lenret);
        std::copy(p.a.begin(), p.a.begin() + p.len, aux.begin());
        NTT(ret.a, lenret, 0);
        NTT(aux, lenret, 0);
        for (int i = 0; i < lenret; ++ i){
            ret.a[i] = 1ll * ret.a[i] * aux[i] % moder;
        }
        NTT(ret.a, lenret, 1);
        for (int i = 0; i < n - 1; ++ i){
            ret.a[i + 1] += ret.a[i] / base;
            ret.a[i] %= base;
        }
        for ( ; n && !ret.a[n - 1]; -- n)
            ;
        ret.len = n;
        ret.sig = sig * p.sig;
        return ret;
    }
};

int main(){
    init();
    Big a, b;
    a.read(), b.read();
    (a * b).write();
    putchar('\n');
    return 0;
}
