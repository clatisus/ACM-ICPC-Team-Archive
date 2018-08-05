#include<bits/stdc++.h>
 
typedef long long ll;
 
struct BigInteger{ // 仅支持非负整数
    static const int N = 300;
    static const int base = 1e6; // 修改它时记得修改输入输出格式
    int a[N];
    int length;
 
    BigInteger():length(0){memset(a, 0, sizeof(a));}
 
    BigInteger(int p){
        memset(a, 0, sizeof(a));
        length = 0;
        if (!p) return;
        for (ll x = std::abs(p); x; x /= base){
            a[length ++] = x % base;
        }
    }
 
    int &operator [](int sit){return a[sit];}
 
    bool operator < (const BigInteger &q)const{
        if (length != q.length) return length < q.length;
        for (int i = length - 1; ~i; -- i){
            if (a[i] != q.a[i]) return a[i] < q.a[i];
        }
        return false;
    }
 
    BigInteger operator + (const BigInteger &p)const{
        BigInteger ret;
        ret.length = std::max(length, p.length) + 1;
        for (int i = 0; i < ret.length; ++ i){
            ret.a[i] += a[i] + p.a[i];
            if (ret.a[i] >= base) ret.a[i] -= base, ++ ret.a[i + 1];
        }
        for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
            ;
        return ret;
    }
 
    BigInteger operator * (int p)const{
        if (!p) return BigInteger();
        ll remain = 0;
        BigInteger ret;
        for (int i = 0; i < length; ++ i){
            remain += (ll) a[i] * p;
            ret.a[i] = remain % base;
            remain /= base;
        }
        for (ret.length = length, ret.a[ret.length] = remain; ret.a[ret.length]; ++ ret.length){
            ret.a[ret.length + 1] = ret.a[ret.length] / base;
            ret.a[ret.length] %= base;
        }
        for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
            ;
        return ret;
    }
 
    void read(){
        memset(a, 0, sizeof(a));
        length = 0;
        static char s[N * 20];
        scanf("%s", s);
        int len = strlen(s);
        ll now = 1;
        for (int i = len - 1; ~i; -- i){
            a[length] += now * (s[i] - '0');
            if (now * 10 == base){
                now = 1;
                ++ length;
            }
            else{
                now *= 10;
            }
        }
        ++ length;
        for ( ; length && !a[length - 1]; -- length)
            ;
    }
 
    void write(){
        if (!length) return (void) printf("0");
        printf("%d", a[length - 1]);
        for (int i = length - 2; ~i; -- i){
            printf("%06d", a[i]);
        }
    }
};
 
const int N = 10010;
 
BigInteger ans[N];
 
int main(){
    int cnt = 0;
    BigInteger c1(7), c2(2);
    for (int i = 0; i < 1000; ++ i){
        ans[++ cnt] = c2 * 3;
        BigInteger tmp = c1 * 7 + c2 * 24;
        c2 = c1 * 2 + c2 * 7;
        c1 = tmp;
    }
    c1 = BigInteger(3), c2 = BigInteger(2);
    for (int i = 0; i < 2000; ++ i){
        ans[++ cnt] = c2;
        BigInteger tmp = c1 * 3 + c2 * 4;
        c2 = c1 * 2 + c2 * 3;
        c1 = tmp;
    }
    std::sort(ans, ans + cnt);
    BigInteger a;
    a.read();
    std::lower_bound(ans, ans + cnt, a) -> write();
    putchar('\n');
    return 0;
}
