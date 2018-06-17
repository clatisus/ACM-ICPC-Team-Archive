// 多项式模板
// std::complex 比手写的复数类慢很多，卡常时记得修改！ 

#include<bits/stdc++.h>
#include"fft.cpp"

class poly{
private:
	constexpr const static double eps = 1e-9;
	
	double *a;
	int length, size;
	
	void apply(int size){
		if (!size) return;
		a = new double [size]();
		this -> size = size;
	}
	
	void resize(int size){
		if (!size) return;
		double *aux = a;
		a = new double [size]();
		memcpy(a, aux, sizeof(double) * (length + 1));
		if (this -> size) delete [] aux;
		this -> size = size;
	}
	
	void initpoly(const poly &p, int length){
		clear();
		apply(length + 2 << 1);
		memcpy(a, p.a, sizeof(double) * (std::min(length, p.length) + 1));
		this -> length = length;
	}
	
public:
	poly():a(nullptr), length(-1), size(0){}
	poly(int length):a(nullptr), length(length){apply(length + 2 << 1);}
	poly(const poly &p):a(nullptr){initpoly(p, p.length);}
	poly(const poly &p, int length):a(nullptr){initpoly(p, length);}
	~poly(){clear();}
	void clear(){delete [] a; a = nullptr; size = length = 0;}
	double &operator [](int n){return a[n];}
	int getlength(){return length;}
	
	// 将多项式的次数设为 length，如果次数减小则截断多余部分 
	void setlength(int length){
		if (length >= size) resize(length + 2 << 1);
		if (length >= this -> length){
			this -> length = length;
			return;
		}
		memset(a + length + 1, 0, sizeof(double) * (this -> length - length));
		this -> length = length;
	}
	
	poly &operator = (const poly &p){
		if (&p != this) initpoly(p, p.length);
		return *this;
	}
	
	// 相当于乘以 x ^ dis
	poly operator << (const int &dis)const{
		poly ret(length + dis);
		memcpy(ret.a + dis, a, sizeof(double) * (length + 1));
		return ret;
	}
	
	// 相当于除以 x ^ dis
	poly operator >> (const int &dis)const{
		if (dis > length) return poly(-1);
		poly ret(length - dis);
		memcpy(ret.a, a + dis, sizeof(double) * (ret.length + 1));
		return ret;
	}
	
	double value(double x){
		double now = 1, ret = 0;
		for (int i = 0; i <= length; ++ i){
			ret += a[i] * now;
			now *= x;
		}
		return ret;
	}
	
	poly operator + (const poly &p)const{
		if (!~length) return p;
		if (!~p.length) return *this;
		poly ret(*this, std::max(length, p.length));
		for (int i = 0; i <= p.length; ++ i){
			ret.a[i] += p.a[i];
		}
		for ( ; ~ret.length && std::abs(ret.a[ret.length]) < eps; -- ret.length)
			;
		return ret;
	}
	
	poly operator - (const poly &p)const{
		if (!~length) return p;
		if (!~p.length) return *this;
		poly ret(*this, std::max(length, p.length));
		for (int i = 0; i <= p.length; ++ i){
			ret.a[i] -= p.a[i];
		}
		for ( ; ~ret.length && std::abs(ret.a[ret.length]) < eps; -- ret.length)
			;
		return ret;
	}
	
	poly operator - ()const{
		poly ret(length);
		for (int i = 0; i <= length; ++ i){
			ret.a[i] = -a[i];
		}
		return ret;
	}
	
	poly operator * (const poly &p)const{
		if (!~length || !~p.length) return poly(-1);
		int n = length + p.length;
		int lengthret = 1;
		for ( ; lengthret <= n; lengthret <<= 1)
			;
		std::complex <double> *aux = new std::complex <double> [lengthret];
		std::complex <double> *aux1 = new std::complex <double> [lengthret];
		//---------------------- 本方法常数小但精度差 -----------------------------
		for (int i = 0; i < lengthret; ++ i){
			aux[i] = std::complex <double>(i > length ? 0 : a[i], i > p.length ? 0 : p.a[i]);
		}
		FFT(aux, lengthret, 1);
		for (int i = 0; i < lengthret; ++ i){
			aux1[i] = std::conj(aux[i ? lengthret - i : 0]);
		}
		for (int i = 0; i < lengthret; ++ i){
			aux[i] = (aux[i] + aux1[i]) * (aux[i] - aux1[i]) * std::complex <double>(0, -0.25);
		}
		/*--------------------- 本方法常数大但精度好 ------------------------------
		for (int i = 0; i < lengthret; ++ i){
			aux[i] = i > length ? 0 : a[i];
			aux1[i] = i > p.length ? 0 : b[i];
		}
		FFT(aux, lengthret, 1);
		FFT(aux1, lengthret, 1);
		for (int i = 0; i < lengthret; ++ i){
			aux[i] *= aux1[i];
		}
		*/ 
		FFT(aux, lengthret, -1);
		poly ret(n);
		for (int i = 0; i <= n; ++ i){
			ret.a[i] = aux[i].real();
		}
		delete [] aux;
		delete [] aux1;
		return ret;
	}
	
	poly operator * (const double &p)const{
		poly ret(length);
		for (int i = 0; i <= length; ++ i){
			ret.a[i] = a[i] * p;
		}
		return ret;
	}
	
	friend poly operator * (const double &q, const poly &p){return p * q;}
	poly &operator += (const poly &p){*this = *this + p; return *this;}
	poly &operator -= (const poly &p){*this = *this - p; return *this;}
	poly &operator *= (const poly &p){*this = *this * p; return *this;}
	poly &operator *= (const double &p){*this = *this * p; return *this;}
	
	poly inv(int n)const{
		if (std::abs(a[0]) < eps) assert(("Invalid polynomial inv!", 0));
		poly ret(1);
		ret.a[0] = 1 / a[0];
		for (int nowprecision = 0; nowprecision < n; ){
			nowprecision = nowprecision << 1 | 1;
			poly aux(*this, nowprecision), aux1(ret);
			ret *= ret;
			ret.setlength(nowprecision);
			aux *= ret, aux.setlength(nowprecision);
			ret = 2 * aux1 - aux;
		}
		ret.setlength(n - 1);
		return ret;
	}
	
	poly der()const{
		if (!~length) return poly(-1);
		poly ret(length - 1);
		for (int i = 0; i < length; ++ i){
			ret.a[i] = a[i + 1] * (i + 1);
		}
		return ret;
	}
	
	poly integral()const{
		poly ret(length + 1);
		for (int i = 1; i <= length + 1; ++ i){
			ret.a[i] = a[i - 1] / i;
		}
		return ret;
	}
	
	poly operator / (const poly &p)const{
		if (!~p.length) assert(("Invalid polynomial division!", 0));
		if (p.length > length) return poly(-1);
		poly a(*this), b(p);
		std::reverse(a.a, a.a + a.length + 1);
		std::reverse(b.a, b.a + b.length + 1);
		poly ret(p.inv(length - p.length + 1));
		ret *= *this;
		ret.setlength(length - p.length);
		std::reverse(ret.a, ret.a + ret.length + 1);
		return ret;
	}
	
	poly operator % (const poly &p)const{return *this - *this / p * p;}
	poly &operator /= (const poly &p){*this = *this / p; return *this;}
	poly &operator %= (const poly &p){*this = *this % p; return *this;}
	
	poly log(int n)const{
		if (std::abs(a[0] - 1) >= eps) assert(("Invalid polynomial log!", 0));
		poly aux(*this, n - 1);
		poly ret(aux.der() * aux.inv(n));
		ret.setlength(n - 2);
		return ret.integral();
	}
	
	poly exp(int n)const{
		if (std::abs(a[0]) >= eps) assert(("Invalid polynomial exp!", 0));
		poly ret(0);
		ret.a[0] = 1;
		poly unit(ret);
		for (int nowprecision = 0; nowprecision < n; ){
			nowprecision = nowprecision << 1 | 1;
			poly aux(*this, nowprecision);
			ret *= unit - ret.log(nowprecision + 1) + aux;
			ret.setlength(nowprecision);
		}
		ret.setlength(n - 1);
		return ret;
	}
	
	template <typename T>
	poly power(T exp)const{
		poly ret(0), aux(*this);
		ret.a[0] = 1;
		for ( ; exp; exp >>= 1){
			if (exp & 1){
				ret *= aux;
			}
			aux *= aux;
		}
		return ret;
	}
};

int main(){
	return 0;
}
