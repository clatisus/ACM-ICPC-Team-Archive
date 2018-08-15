#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair <int, int> pii;

int powermod(int a, int exp, int moder){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

struct poly{
    static const int N = 1000;

    int a[N];
    int len, moder;

    poly():len(-1), moder(0){memset(a, 0, sizeof(a));}
    poly(int moder):len(-1), moder(moder){memset(a, 0, sizeof(a));}

    int value(int x){
        int ret = 0;
        for (int i = 0, now = 1; i <= len; ++i){
            ret = (ret + 1ll * a[i] * now) % moder;
            now = 1ll * now * x % moder;
        }
        return ret;
    }

    int &operator [](int sit){return a[sit];}

    poly operator + (const poly &p)const{
        poly ret(moder);
        ret.len = std::max(len, p.len);
        for (int i = 0; i <= ret.len; ++i){
            ret.a[i] = a[i] + p.a[i];
            ret.a[i] -= ret.a[i] >= moder ? moder : 0;
        }
        for ( ; ~ret.len && !ret.a[ret.len]; --ret.len)
            ;
        return ret;
    }

    poly operator - ()const{
        poly ret(moder);
        ret.len = len;
        for (int i = 0; i <= ret.len; ++i){
            ret.a[i] = a[i] ? moder - a[i] : 0;
        }
        return ret;
    }

    poly operator - (const poly &p)const{
        poly ret(moder);
        ret.len = std::max(len, p.len);
        for (int i = 0; i <= ret.len; ++i){
            ret.a[i] = a[i] - p.a[i];
            ret.a[i] -= ret.a[i] < 0 ? moder : 0;
        }
        for ( ; ~ret.len && !ret.a[ret.len]; --ret.len)
            ;
        return ret;
    }

    poly operator * (const poly &p)const{
        poly ret(moder);
        if (!~len || !~p.len) return ret;
        ret.len = len + p.len;
        for (int i = 0; i <= len; ++i){
            for (int j = 0; j <= p.len; ++j){
                ret.a[i + j] = (ret.a[i + j] + 1ll * a[i] * p.a[j]) % moder;
            }
        }
        return ret;
    }

    poly operator * (const int &p)const{
        poly ret(moder);
        ret.len = len;
        for (int i = 0; i <= ret.len; ++i){
            ret.a[i] = 1ll * a[i] * p % moder;
        }
        return ret;
    }

    poly operator / (const poly &p)const{
        poly ret(moder);
        if (!~p.len) assert(("division by zero!", 0));
        if (len < p.len) return ret;
        ret.len = len - p.len;
        poly aux = *this;
        while (aux.len >= p.len){
            int x = 1ll * aux.a[aux.len] * powermod(p.a[p.len], moder - 2, moder) % moder;
            ret.a[aux.len - p.len] = x;
            for (int j = 0; j <= p.len; ++j){
                int &u = aux.a[aux.len + j - p.len];
                u = (u - 1ll * x * p.a[j]) % moder;
                u += u < 0 ? moder : 0;
            }
            for ( ; ~aux.len && !aux.a[aux.len]; --aux.len)
                ;
        }
        return ret;
    }

    poly operator % (const poly &p)const{
        if (!~p.len) assert(("division by zero!", 0));
        poly ret = p;
        while (ret.len >= p.len){
            int x = 1ll * ret.a[ret.len] * powermod(p.a[p.len], moder - 2, moder) % moder;
            for (int j = 0; j <= p.len; ++j){
                int &u = ret.a[ret.len + j - p.len];
                u = (u - 1ll * x * p.a[j]) % moder;
                u += u < 0 ? moder : 0;
            }
            for ( ; ~ret.len && !ret.a[ret.len]; --ret.len)
                ;
        }
        return ret;
    }

    static poly interpolation(std::vector <pii> vec, int moder){
        int n = vec.size() - 1;
        poly aux(moder); aux.len = 0; aux.a[0] = 1;
        for (int i = 0; i <= n; ++ i, ++aux.len){
            int coe = moder - vec[i].first;
            coe -= coe >= moder ? moder : 0;
            for (int j = aux.len; j >= 0; --j){
                aux.a[j + 1] += aux.a[j];
                aux.a[j + 1] -= aux.a[j + 1] >= moder ? moder : 0;
                aux.a[j] = 1ll * aux.a[j] * coe % moder;
            }
        }
        poly ret(moder);
        for (int i = 0; i <= n; ++i){
            int coe = moder - vec[i].first;
            coe -= coe >= moder ? moder : 0;
            int x = 1;
            for (int j = 0; j <= n; ++j){
                if (i == j) continue;
                x = 1ll * x * (vec[i].first - vec[j].first) % moder;
                x += x < 0 ? moder : 0;
            }
            x = 1ll * powermod(x, moder - 2, moder) * vec[i].second % moder;
            int left = aux.a[aux.len];
            for (int j = aux.len; j; --j){
                ret.a[j - 1] = (ret.a[j - 1] + 1ll * left * x) % moder;
                left = (aux.a[j - 1] - 1ll * left * coe) % moder;
                left += left < 0 ? moder : 0;
            }
        }
        ret.len = n;
        return ret;
    }
};

int main(){
}
