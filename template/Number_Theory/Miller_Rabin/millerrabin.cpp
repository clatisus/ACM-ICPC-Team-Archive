// Miller-Rabin 模板
// 该算法为随机算法，若要调整准确率，请修改 solve(T n) 中的 const int S 以调节判断次数，S 越大，准确率越高，速度越慢

#include<bits/stdc++.h>
#include"random.cpp"
    
ll getone(int n){return 1;}
__int128 getone(ll n){return 1;}

template <typename T>
T powermod(T a, T exp, T moder){
    T ret = 1;
    auto one = getone(a);
    for ( ; exp; exp >>= 1){
        if (exp & 1){
            ret = one * ret * a % moder;
        }
        a = one * a * a % moder;
    }
    return ret;
}

int random(int n){return randint(n);}
ll random(ll n){return randll(n);}

template <typename T>
class millerrabin{
private:    
    T a;
    bool isprime;
    
    bool solve(T n, int t, T u){
        T a = random(n);
        if(!a || a == 1) return true;
        T pre = powermod(a, u, n);
        auto one = getone(n);
        for (int i = 0; i < t; ++ i){
            T now = one * pre * pre % n;
            if (now == 1 && pre != 1 && pre != n - 1) return false;
            pre = now;
        }
        return pre == 1;
    }

    bool solve(T n){
        if (n <= 30) return n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17 || n == 19 || n == 23 || n == 29;
        if (!(n & 1)) return false;
        const int S = 7;
        int t = 0;
        T x = n - 1;
        for ( ; !(x & 1); x >>= 1, ++ t)
            ;
        for (int i = 0; i < S; ++ i){
            if (!solve(n, t, x)) return false;
        }
        return true;
    }
    
public:
    millerrabin():a(0), isprime(false){}
    millerrabin(T a):a(a){isprime = solve(a);}
    bool solve(){return isprime;}
};
