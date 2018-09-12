#include<bits/stdc++.h>

typedef long long ll;
typedef __int128 i128;

struct Big{ // 仅支持非负整数
    static const int exp = 12;
    static const ll base = 1000000000000ll; // 修改它时记得修改输入输出格式 

    std::vector <ll> a;
    int len;
    
    Big():len(0){}
    Big(ll len, int mark):len(len){a.resize(len);}
    
    explicit Big(ll p){
        for ( ; p; p /= base){
            a.push_back(p % base);
        }
        len = a.size();
    }

    Big(char *s, int len){
        ll x = 0, now = 1;
        for (int i = 0; i < len; ++ i){
            x += (s[len - i - 1] - '0') * now;
            if (i % exp == exp - 1){
                a.push_back(x);
                x = 0;
                now = 1;
            }
            else{
                now *= 10;
            }
        }
        if (x){
            a.push_back(x);
        }
        this -> len = a.size();
        normal();
    }
    
    ll operator [] (int sit)const{return sit >= len || sit < 0 ? 0 : a[sit];}
    
    void normal(){
        for ( ; len && !a[len - 1]; -- len)
            ;
    }
    
    static Big divide(Big &b, const Big &p){
        assert(p.len);
        if (b.len < p.len) return Big();
        b.a.resize(b.len + 1);
        Big ret(b.len - p.len + 1, -1);
        for (int i = b.len - p.len; i >= 0; -- i){
            i128 num = 0, den = 0;
            for (int j = 0; j <= 2; ++ j){
                num = num * base + b[i + p.len - j];
            }
            for (int j = 1; j <= 2; ++ j){
                den = den * base + p[p.len - j];
            }
            ll x = num / den;
            if (!x) continue;
            i128 remain = 0;
            for (int j = 0; j < p.len; ++ j){
                remain = remain + b.a[i + j] - (i128) p.a[j] * x;
                b.a[i + j] = remain % base;
                remain /= base;
                if (b.a[i + j] < 0) b.a[i + j] += base, -- remain;
            }
            b.a[i + p.len] += remain;
            if (b.a[i + p.len] < 0){
                -- x;
                for (int j = 0; j < p.len; ++ j){
                    b.a[i + j] += p.a[j];
                    if (b.a[i + j] >= base) b.a[i + j] -= base, ++ b.a[i + j + 1];
                }
            }
            ret.a[i] = x;
        }
        b.normal();
        ret.normal();
        return ret;
    }

    Big operator / (const Big &p)const{
        Big ret = *this;
        return divide(ret, p);
    }
    
    Big operator % (const Big &p)const{
        Big ret = *this;
        divide(ret, p);
        return ret;
    }

    void write(){
        if (!len) return (void) printf("0");
        printf("%lld", a[len - 1]);
        for (int i = len - 2; ~i; -- i){
            printf("%012lld", a[i]);
        }
    }
};

const int N = 100010;

char s1[N], s2[N];

int main(){
    scanf("%s%s", s1, s2);
    int len1 = strlen(s1), len2 = strlen(s2);
    Big a(s1, len1), b(s2, len2);
    Big div = Big::divide(a, b);
    div.write();
    putchar('\n');
    a.write();
    putchar('\n');
    return 0;
}
