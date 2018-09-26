// 中国剩余定理模板
// 求方程组 x = remain1(mod moder1), x = remain2(mod moder2) 的解
// p.crt(q) 返回方程 p, q 的解 

#include<bits/stdc++.h>
#include "euclidinv.cpp"

typedef long long ll;

// 如果没有 __int128 就只能这么写啦 
ll multmod(ll a, ll b, ll moder){
    return (a * b - (ll)((long double) a * b / moder) * moder) % moder;
}

template <typename T> 
class modequa{
private:
    T remain, moder;
    
    ll getone(int n)const{return 1;}
    __int128 getone(ll n)const{return 1;}
    
public:
    modequa <T>(){}
    modequa <T>(T remain, T moder) : remain(remain), moder(moder){}
    T getremain(){return remain;}
    T getmoder(){return moder;}
    
    modequa <T> crt(const modequa <T> &p)const{ // 保证所有运算在 lcm + max(p.moder, moder) 的数据范围内实现，注意不要让模数为 0
        auto one = getone(remain);
        modequa <T> p1 = *this, p2 = p;
        if (p1.moder < p2.moder) std::swap(p1, p2); 
        T x, y;
        T gcd = ex_euc(p1.moder, p2.moder, x, y);
        if ((p2.remain - p1.remain) % gcd) return modequa <T>(0, 0);
        T lcm = p1.moder / gcd * p2.moder;
        T ans = (p2.remain - p1.remain) / gcd;
        ans = one * ans * x % (p2.moder / gcd) * p1.moder;
        ans += p1.remain;
        ans += ans < 0 ? lcm : ans >= lcm ? -lcm : 0;
        return modequa <T>(ans, lcm);
    }
};
