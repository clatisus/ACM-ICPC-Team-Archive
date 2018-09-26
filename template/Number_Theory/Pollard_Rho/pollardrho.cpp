// Pollard-Rho 模板

#include<bits/stdc++.h>
#include"millerrabin.cpp"

template <typename T>
class pollardrho{
private:    
    T a;
    std::vector <T> fact;
    
    T solve(T n){
        T c = random(n - 1) + 1, x = random(n), y = x, i = 0, k = 1;
        auto one = getone(n);
        for ( ; ; ){
            ++ i;
            x = (one * x * x + c) % n;
            T d = std::__gcd(std::abs(y - x), n);
            if (d != 1 && d != n) return d;
            if (x == y) return n;
            if (i == k){
                y = x;
                k <<= 1;
            }
        }
    }
    
    void Solve(T n){
        if (n <= 1) return;
        if (millerrabin <T> (n).solve()){
            fact.push_back(n);
            return;
        }
        T x = solve(n);
        Solve(x);
        Solve(n / x);
    }

public:
    pollardrho(){}
    pollardrho(T a):a(a){Solve(a);}
    
    // 返回 a 的所有质因子，每个质因子的指数是多少，就在 vector 中出现多少次，该 vector 无序 
    std::vector <T> solve(){
        return fact;
    }
};
