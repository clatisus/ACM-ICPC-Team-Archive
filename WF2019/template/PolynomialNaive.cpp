#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair <int, int> pii;
const int moder = 998244353;

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

const int N = 1000010;

int inv[N], invf[N];

void init(){
    inv[1] = invf[0] = invf[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = (moder - 1ll * (moder / i) * inv[moder % i] % moder) % moder;
        invf[i] = 1ll * invf[i - 1] * inv[i] % moder;
    }
}

struct poly{
    static const int N = 1000;

    int a[N];
    int len;

    poly():len(-1){memset(a, 0, sizeof(a));}

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
        poly ret;
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
        poly ret;
        ret.len = len;
        for (int i = 0; i <= ret.len; ++i){
            ret.a[i] = a[i] ? moder - a[i] : 0;
        }
        return ret;
    }

    poly operator - (const poly &p)const{
        poly ret;
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
        poly ret;
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
        poly ret;
        ret.len = len;
        for (int i = 0; i <= ret.len; ++i){
            ret.a[i] = 1ll * a[i] * p % moder;
        }
        return ret;
    }

    poly operator / (const poly &p)const{
        poly ret;
        assert(~p.len);
        if (len < p.len) return ret;
        ret.len = len - p.len;
        poly aux = *this;
        while (aux.len >= p.len){
            int x = 1ll * aux.a[aux.len] * powermod(p.a[p.len], moder - 2) % moder;
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
        assert(~p.len);
        poly ret = p;
        while (ret.len >= p.len){
            int x = 1ll * ret.a[ret.len] * powermod(p.a[p.len], moder - 2) % moder;
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

    static poly interpolation(std::vector <pii> vec){
        int n = vec.size() - 1;
        poly aux; aux.len = 0; aux.a[0] = 1;
        for (int i = 0; i <= n; ++ i, ++aux.len){
            int coe = moder - vec[i].first;
            coe -= coe >= moder ? moder : 0;
            for (int j = aux.len; j >= 0; --j){
                aux.a[j + 1] += aux.a[j];
                aux.a[j + 1] -= aux.a[j + 1] >= moder ? moder : 0;
                aux.a[j] = 1ll * aux.a[j] * coe % moder;
            }
        }
        poly ret;
        for (int i = 0; i <= n; ++i){
            int coe = moder - vec[i].first;
            coe -= coe >= moder ? moder : 0;
            int x = 1;
            for (int j = 0; j <= n; ++j){
                if (i == j) continue;
                x = 1ll * x * (vec[i].first - vec[j].first) % moder;
                x += x < 0 ? moder : 0;
            }
            x = 1ll * powermod(x, moder - 2) * vec[i].second % moder;
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

    static int interpolation(std::vector <int> vec, int x){
        int n = vec.size() - 1;
        if (x >= 0 && x <= n) return vec[x];
        std::vector <int> pre(n + 1), suf(n + 1);
        pre[0] = suf[n] = 1;
        for (int i = 1; i <= n; ++ i){
            pre[i] = 1ll * pre[i - 1] * (x - i + 1) % moder;
            pre[i] += pre[i] < 0 ? moder : 0;
        }
        for (int i = n - 1; i >= 0; -- i){
            suf[i] = 1ll * suf[i + 1] * (x - i - 1) % moder;
            suf[i] += suf[i] < 0 ? moder : 0;
        }
        int ans = 0;
        for (int i = 0; i <= n; ++ i){
            ans = (ans + ((n - i) & 1 ? -1ll : 1ll) * vec[i] * pre[i] % moder * suf[i] % moder * invf[i] % moder * invf[n - i]) % moder;
        }
        ans += ans < 0 ? moder : 0;
        return ans;
    }
};

int main(){
}
