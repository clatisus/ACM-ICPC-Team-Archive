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
	
	void setfrac(T x){this -> x = x; y = 1;};
	
	void setfrac(T x, T y){
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
	
	friend std::ostream &operator << (std::ostream &os, const frac &f){
		os << f.x << '/' << f.y;
		return os;
	}
	
	frac <T> operator + (const frac <T> &f) const &{return frac <T> (x * f.y + y * f.x, y * f.y);}
	frac <T> operator - (const frac <T> &f) const &{return frac <T> (x * f.y - y * f.x, y * f.y);}
	frac <T> operator * (const frac <T> &f) const &{return frac <T> (x * f.x, y * f.y);}
	frac <T> operator / (const frac <T> &f) const &{if (!f.x) assert(("Division by zero!", 0)); return frac <T> (x * f.y, y * f.x);}
	bool operator > (const frac <T> &f) const &{return x * f.y > y * f.x;}
	bool operator >= (const frac <T> &f) const &{return x * f.y >= y * f.x;}
	bool operator < (const frac <T> &f) const &{return x * f.y < y * f.x;}
	bool operator <= (const frac <T> &f) const &{return x * f.y <= y * f.x;}
	bool operator == (const frac <T> &f) const &{return x * f.y == y * f.x;}
	bool operator != (const frac <T> &f) const &{return x * f.y != y * f.x;}
	template <typename K> K toreal(){return (K) x / y;}
	T toint(){return x;}    
	bool isint(){return y == 1;}
};

int main(){
	return 0;
}
