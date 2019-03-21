#include<bits/stdc++.h>

// 请自行保证乘除法的结果不超过定义的类型范围！！！ 
template <typename T>
class frac{
private:
    T x, y;

public:    
    frac <T>() : x(0), y(1){}
    frac <T>(T x) : x(x), y(1){}
    
    frac <T>(T x, T y){
        T gcd = std::__gcd(x, y);
        x /= gcd;
        y /= gcd;
        if (y < 0){
            x = -x;
            y = -y;
        }
        this -> x = x;
        this -> y = y;
    }
    
    frac <T> operator + (const frac <T> &f) const &{return frac <T> (x * f.y + y * f.x, y * f.y);}
    frac <T> operator - (const frac <T> &f) const &{return frac <T> (x * f.y - y * f.x, y * f.y);}
    frac <T> operator * (const frac <T> &f) const &{return frac <T> (x * f.x, y * f.y);}
    frac <T> operator / (const frac <T> &f) const &{if (!f.x) assert(("Division by zero!", 0)); return frac <T> (x * f.y, y * f.x);}
    bool operator < (const frac <T> &f) const &{return x * f.y < y * f.x;}
};

int main(){
    return 0;
}
