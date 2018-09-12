#include<bits/stdc++.h>

typedef long long ll;
typedef __int128 i128;
const ll base1 = 1ll << 50;
const ll base2 = 298023223876953125ll;
int tot;

struct Big{ // 仅支持非负整数
    static ll base; // 修改它时记得修改输入输出格式 
    static int type;
    static int maxbit;

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
        for (int i = len - 1; i >= 0; -- i){
            a.push_back(s[i] - '0');
        }
        this -> len = a.size();
        normal();
    }
    
    ll operator [] (int sit)const{return sit >= len || sit < 0 ? 0 : a[sit];}
    
    void normal(){
        for ( ; len && !a[len - 1]; -- len)
            ;
    }

    void resize(int len){
        a.resize(len);
        this -> len = len;
        normal();
    }
    
    bool operator < (const Big &q)const{
        if (len != q.len) return len < q.len;
        for (int i = len - 1; ~i; -- i){
            if (a[i] != q.a[i]) return a[i] < q.a[i];
        }
        return false;
    }
    
    Big operator + (const Big &p)const{
        if (type){
            Big ret(maxbit, -1);
            for (int i = 0; i < maxbit; ++ i){
                ret.a[i] += (*this)[i] + p[i];
                if (ret.a[i] >= base){
                    ret.a[i] -= base;
                    if (i < maxbit - 1){
                        ++ ret.a[i + 1];
                    }
                }
            }
            return ret;
        }
        Big ret(std::max(len, p.len) + 1, -1);
        for (int i = 0; i < ret.len - 1; ++ i){
            ret.a[i] += (*this)[i] + p[i];
            if (ret.a[i] >= base) ret.a[i] -= base, ++ ret.a[i + 1];
        }
        ret.normal();
        return ret;
    }
    
    Big operator - (const Big &p)const{
        if (type){
            Big ret(maxbit, -1);
            for (int i = 0; i < maxbit; ++ i){
                ret.a[i] += (*this)[i] - p[i];
                if (ret.a[i] < 0){
                    ret.a[i] += base;
                    if (i < maxbit - 1){
                        -- ret.a[i + 1];
                    }
                } } return ret;
        }
        Big ret(std::max(len, p.len) + 1, -1);
        for (int i = 0; i < ret.len - 1; ++ i){
            ret.a[i] += (*this)[i] - p[i];
            if (ret.a[i] < 0) ret.a[i] += base, -- ret.a[i + 1];
        }
        ret.normal();
        return ret;
    }
    
    Big operator * (const Big &p)const{ // 注意长度太长可能会爆 __int128，视情况需要将 18 位调小 
        if (type){
            int begin = clock();
            std::vector <__int128> vec(maxbit);
            for (int i = 0; i < maxbit; ++ i){
                for (int j = 0; i + j < maxbit; ++ j){
                    vec[i + j] += (__int128) (*this)[i] * p[j];
                }
            }
            Big ret(maxbit, -1);
            for (int i = 0; i < maxbit; ++ i){
                ret.a[i] = vec[i] % base;
                if (i < maxbit - 1) vec[i + 1] += vec[i] / base;
            }
            tot += clock() - begin;
            return ret;
        }
        std::vector <i128> vec(len + p.len);
        for (int i = 0; i < len; ++ i){
            for (int j = 0; j < p.len; ++ j){
                vec[i + j] += (i128) a[i] * p.a[j];
            }
        }
        Big ret(len + p.len, -1);
        for (int i = 0; i < ret.len; ++ i){
            ret.a[i] = vec[i] % base;
            vec[i + 1] += vec[i] / base;
        }
        ret.normal();
        return ret;
    }

    Big operator * (ll p)const{
        if (!len || !p) return Big();
        i128 remain = 0;
        Big ret;
        for (int i = 0; i < len || remain; ++ i){
            remain += (i128) (*this)[i] * p;
            ret.a.push_back(remain % base);
            remain /= base;
        }
        ret.len = ret.a.size();
        return ret;
    }
    
    static ll divide(Big &b, const ll &p){
        assert(p);
        i128 remain = 0;
        for (int i = b.len - 1; ~i; -- i){
            remain = remain * base + b.a[i];
            b.a[i] = remain / p;
            remain %= p;
        }
        b.normal();
        return remain;
    }

    Big operator / (const ll &p)const{
        Big ret = *this;
        divide(ret, p);
        return ret;
    }

    ll operator % (const ll &p)const{
        Big ret = *this;
        return divide(ret, p);
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

    ll toint(){
        ll ret = 0;
        for (int i = len - 1; i >= 0; -- i){
            ret = ret * base + a[i];
        }
        return ret;
    }
};

ll Big::base = 10;
int Big::type = 1;
int Big::maxbit = 4;

const int N = 1010;
typedef std::pair <Big, Big> pbb;
typedef std::pair <Big, int> pbi;

Big s[N][N];
Big inv[N];
int invcnt[N];
Big power[N];
Big poly[N];
Big inter[N];

Big powermod(Big a, Big exp){
    Big ret(1);
    for ( ; exp.len; exp = exp / 2){
        int tot = 0;
        if (Big::base & 1){
            for (int i = 0; i < exp.len; ++ i){
                tot += exp[i] & 1;
            }
        }
        else{
            tot = 1;
        }
        if (tot & 1){
            ret = ret * a;
        }
        a = a * a;
    }
    return ret;
}

Big getinv(Big x, int p, int e){
    return powermod(x, power[e - 1] * (p - 1) - Big(1));
}

void initpower(int p, int e){
    Big::type = 0;
    power[0] = Big(1);
    for (int i = 1; i < e; ++ i){
        power[i] = power[i - 1] * p;
    }
    Big::type = 1;
}

void inits(int p, int e){
    s[0][0] = Big(1);
    for (int i = 1; i <= p; ++ i){
        for (int j = 1, sz = std::min(p, e); j <= sz; ++ j){
            s[i][j] = j > i ? Big() : s[i - 1][j] * (i - 1) + s[i - 1][j - 1];
        }
    }
}

void initinv(int p, int e){
    inv[0] = Big(1);
    for (int i = 1, sz = std::max(2 * e - 2, p - 1); i <= sz; ++ i){
        int x = i;
        invcnt[i] = 0;
        while (x % p == 0){
            ++ invcnt[i];
            x /= p;
        }
        invcnt[i] += invcnt[i - 1];
        inv[i] = inv[i - 1] * getinv(Big(x), p, e);
    }
}

Big calcinter(Big u, int v, int p, int e){
    Big ans(0), now(1);
    Big mult = u * p;
    for (int i = 0, sz = std::min(v, e - 1); i <= sz; ++ i){
        ans = ans + now * s[v + 1][i + 1];
        now = now * mult;
    }
    return ans;
}

void initpoly(int p, int e){
    poly[0] = Big(1);
    for (int i = 1; i <= 2 * e - 2; ++ i){
        poly[i] = poly[i - 1] * calcinter(Big(i - 1), p - 1, p, e) * inv[p - 1];
    }
    for (int i = 0; i <= 2 * e - 2; ++ i){
        inter[i] = poly[i] * inv[i] * inv[2 * e - 2 - i];
    }
}

Big tobase(Big a, ll base){
    Big ret;
    while (a.len){
        ret.a.push_back(a % base);
        a = a / base;
    }
    ret.len = ret.a.size();
    return ret;
}

pbb solve(Big n, int p, int e){
    int max = e + invcnt[2 * e - 2];
    Big ans(1), cnt;
    while (n.len){
        Big u = n / p;
        int v = n % p;
        n = u;
        Big::type = 0;
        cnt = cnt + u;
        Big::type = 1;
        ans = ans * calcinter(u, v, p, e);
        int sz = 2 * e - 2;
        if (!(Big(sz) < u)){
            ans = ans * poly[u.toint()];
            continue;
        }
        std::vector <pbi> pre(sz + 1), suf(sz + 1);
        pre[0] = suf[sz] = {Big(1), 0};
        for (int i = 1; i <= sz; ++ i){
            Big::type = 0;
            Big x = u - Big(i - 1);
            Big::type = 1;
            while (x % p == 0 && pre[i].second < max){
                ++ pre[i].second;
                x = x / p;
            }
            pre[i].second += pre[i - 1].second;
            pre[i].first = pre[i - 1].first * x;
        }
        for (int i = sz - 1; i >= 0; -- i){
            Big::type = 0;
            Big x = u - Big(i + 1);
            Big::type = 1;
            while (x % p == 0 && suf[i].second < max){
                ++ suf[i].second;
                x = x / p;
            }
            suf[i].second += suf[i + 1].second;
            suf[i].first = suf[i + 1].first * x;
        }
        Big sum(0);
        for (int i = 0; i <= sz; ++ i){
            int cnt = pre[i].second + suf[i].second - invcnt[i] - invcnt[sz - i];
            if (cnt >= e) continue;
            Big tmp = power[cnt] * pre[i].first * suf[i].first * inter[i];
            //<==>(2 * e - 2 - i & 1 ? -1ll : 1ll)
            sum = i & 1 ? sum - tmp : sum + tmp;
        }
        ans = ans * sum;
    }
    ans = ans * powermod(s[p][1], cnt);
    return {ans, cnt};
}

Big combmoder(Big n, Big m, int p){
    ll base = p == 2 ? base1 : base2;
    Big::base = 10;
    n = tobase(n, base);
    m = tobase(m, base);
    Big::base = base;
    Big::maxbit = p == 2 ? 2 : 4;
    Big::type = 0;
    Big x = n - m;
    Big::type = 1;
    initpower(p, 100);
    inits(p, 100);
    initinv(p, 100);
    initpoly(p, 100);
    pbb p1 = solve(n, p, 100);
    pbb p2 = solve(m, p, 100);
    pbb p3 = solve(x, p, 100);
    Big::type = 0;
    Big cnt = p1.second - p2.second - p3.second;
    Big::type = 1;
    if (!(cnt < Big(100))){
        return Big();
    }
    return p1.first * getinv(p2.first, p, 100) * getinv(p3.first, p, 100) * power[cnt.toint()];
}

char str[N];

int main(){
    scanf("%s", str);
    Big n(str, strlen(str));
    scanf("%s", str);
    Big m(str, strlen(str));
    Big ans1 = combmoder(n, m, 2);
    Big x1(1);
    for (int i = 0; i < 100; ++ i){
        x1 = x1 * 5;
    }
    Big x2 = getinv(x1, 2, 100);
    ans1 = tobase(ans1, 10);
    x1 = tobase(x1, 10);
    x2 = tobase(x2, 10);
    Big ans2 = combmoder(n, m, 5);
    Big x3(1);
    for (int i = 0; i < 100; ++ i){
        x3 = x3 * 2;
    }
    Big x4 = getinv(x3, 5, 100);
    ans2 = tobase(ans2, 10);
    x3 = tobase(x3, 10);
    x4 = tobase(x4, 10);
    Big::type = 0;
    Big::base = 10;
    Big ans = ans1 * x1 * x2 + ans2 * x3 * x4;
    int k;
    scanf("%d", &k);
    ans.resize(k);
    if (!ans.len){
        puts("0");
        return 0;
    }
    for (int i = ans.len - 1; i >= 0; -- i){
        putchar('0' + ans[i]);
    }
    puts("");
    return 0;
}
