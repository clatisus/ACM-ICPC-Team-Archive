// 大整数模板 

#include<bits/stdc++.h>

typedef long long ll;

struct Big{
    static const int base = 10;

    std::vector <int> a;
    int len, sig;
    
    Big():len(0), sig(0){}

    Big(ll p):len(0), sig((p > 0) - (p < 0)){
        for (ll x = std::abs(p); x; x /= base){
            a.push_back(x % base);
            ++ len;
        }
    }

    Big(const Big &b, const int &len):len(len), sig(b.sig){
        a.resize(len);
        for (int i = 0; i < len; ++ i){
            a[i] = i < b.len ? b.a[i] : 0;
        }
    }

    int operator [](int n){return n >= len ? 0 : a[n];}

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
    
    bool absge(const Big &q)const{
        if (len != q.len) return len > q.len;
        for (int i = len - 1; ~i; -- i){
            if (a[i] != q.a[i]) return a[i] > q.a[i];
        }
        return true;
    }

    Big operator + (const Big &p)const{
        if (!p.sig) return *this;
        if (!sig) return p;
        bool type = true, flag = sig > 0;
        const Big *aux = this, *aux1 = &p;
        if (sig != p.sig){
            type = false;
            if (!absge(p)){
                flag = !flag;
                std::swap(aux, aux1);
            }
        }
        Big ret(*aux, std::max(len, p.len) + 1);
        for (int i = 0; i < ret.len - 1; ++ i){
            ret.a[i] += i < aux1 -> len ? type ? aux1 -> a[i] : -aux1 -> a[i] : 0;
            ret.a[i] >= base ? (ret.a[i] -= base, ++ ret.a[i + 1]) : ret.a[i] < 0 ? (ret.a[i] += base, -- ret.a[i + 1]) : 0;
        }
        for ( ; ret.len && !ret.a[ret.len - 1]; -- ret.len)
            ;
        ret.sig = ret.len ? flag ? 1 : -1 : 0;
        return ret;
    }
};

int main(){
    Big a, b;
    a.read(), b.read();
    (a + b).write();
    putchar('\n');
    return 0;
}
