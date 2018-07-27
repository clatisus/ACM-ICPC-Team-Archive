// 多项式模板（取模）
// 使用方法见多项式模板 

#include<bits/stdc++.h>
#include"crt.cpp"
#include"ntt.cpp"

typedef long long ll;

// 据说会快 orz 
inline int multmod(int x,int y, int MOD) {
  int ret; 
  __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(MOD));
  return ret;
}

// 如果模数不是质数，那么基本就只能做加减乘和求导了orz 
class poly{
private:
	int *a;
	int length, size;
	int moder, root, invroot;
	// 常用的两组模数为 ((119 << 23) + 1, 3, 332748118) 和 ((479 << 21) + 1, 3, 334845270)
	
	void apply(int size){
		if (!size) return;
		a = new int [size]();
		this -> size = size;
	}
	
	void resize(int size){
		if (!size) return;
		int *aux = a;
		a = new int [size]();
		memcpy(a, aux, sizeof(int) * (length + 1));
		if (this -> size) delete [] aux;
		this -> size = size;
	}
	
	void initpoly(const poly &p, int length){
		clear();
		apply(length + 2 << 1);
		memcpy(a, p.a, sizeof(int) * (std::min(length, p.length) + 1));
		this -> length = length;
		moder = p.moder, root = p.root, invroot = p.invroot;
	}

public:
	poly():a(nullptr), length(-1), moder(0), root(0), invroot(0){}
	// 如果模数非NTT质数 root 和 invroot 随便设就好辣~ 
	poly(int length, int moder, int root, int invroot):a(nullptr), length(length), moder(moder), root(root), invroot(invroot){apply(length + 2 << 1);}
	poly(const poly &p):a(nullptr){initpoly(p, p.length);}
	poly(const poly &p, int length):a(nullptr){initpoly(p, length);}
	~poly(){clear();}
	void clear(){delete [] a; a = nullptr; size = length = moder = root = invroot = 0;}
	int &operator [](int n){return a[n];}
	int getlength(){return length;}
	void setmoder(int moder, int root, int invroot){this -> moder = moder, this -> root = root, this -> invroot = invroot;}
	int getmoder(){return moder;}
	
	void setlength(int length){
		if (length >= size) resize(length + 2 << 1);
		if (length >= this -> length){
			this -> length = length;
			return;
		}
		memset(a + length + 1, 0, sizeof(int) * (this -> length - length));
		this -> length = length;
	}
	
	poly &operator = (const poly &p){
		if (&p != this) initpoly(p, p.length);
		return *this;
	}
	
	// 相当于乘以 x ^ dis
	poly operator << (const int &dis)const{
		poly ret(length + dis, moder, root, invroot);
		memcpy(ret.a + dis, a, sizeof(int) * (length + 1));
		return ret;
	}
	
	// 相当于除以 x ^ dis
	poly operator >> (const int &dis)const{
		if (dis > length) return poly(-1, moder, root, invroot);
		poly ret(length - dis, moder, root, invroot);
		memcpy(ret.a, a + dis, sizeof(int) * (ret.length + 1));
		return ret;
	}
	
	int value(int x){
		int now = 1, ret = 0;
		for (int i = 0; i <= length; ++ i){
			ret = (ret + 1ll * a[i] * now) % moder;
			now = 1ll * now * x % moder;
		}
		return ret;
	}
	
	poly operator + (const poly &p)const{
		if (!~length) return p;
		if (!~p.length) return *this;
		poly ret(*this, std::max(length, p.length));
		for (int i = 0; i <= p.length; ++ i){
			ret.a[i] += p.a[i];
			ret.a[i] -= ret.a[i] >= moder ? moder : 0;
		}
		for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
			;
		return ret;
	}
	
	poly operator - (const poly &p)const{
		if (!~length) return p;
		if (!~p.length) return *this;
		poly ret(*this, std::max(length, p.length));
		for (int i = 0; i <= p.length; ++ i){
			ret.a[i] -= p.a[i];
			ret.a[i] += ret.a[i] < 0 ? moder : 0;
		}
		for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
			;
		return ret;
	}
	
	poly operator - ()const{
		poly ret(length, moder, root, invroot);
		for (int i = 0; i <= length; ++ i){
			ret.a[i] = a[i] ? moder - a[i] : 0;
		}
		return ret;
	}
	
	poly operator * (const poly &p)const{
		if (!~length || !~p.length) return poly(-1, moder, root, invroot);
		int n = length + p.length;
		int lengthret = 1;
		for ( ; lengthret <= n; lengthret <<= 1)
			;
		int *aux = new int [lengthret]();
		int *aux1 = new int [lengthret]();
		memcpy(aux, a, sizeof(int) * (length + 1));
		memcpy(aux1, p.a, sizeof(int) * (p.length + 1));
		NTT(aux, lengthret, 1, moder, root);
		NTT(aux1, lengthret, 1, moder, root);
		for (int i = 0; i < lengthret; ++ i){
			aux[i] = 1ll * aux[i] * aux1[i] % moder;
		}
		NTT(aux, lengthret, -1, moder, invroot);
		poly ret(n, moder, root, invroot);
		memcpy(ret.a, aux, sizeof(int) * (n + 1));
		delete [] aux;
		delete [] aux1;
		return ret;
	}
	
	/*------------ 这是模数非NTT质数的模板，请按需取用~ ----------------------
	poly operator *(const poly &p)const{
		const int multmoder[2] = {(119 << 23) + 1, (479 << 21) + 1};
		const int multroot[2] = {3, 3};
		const int multinvroot[2] = {332748118, 334845270};
		if (!~length || !~p.length) return poly(-1, moder, root, invroot);
		int n = length + p.length;
		int lengthret = 1;
		for ( ; lengthret <= n; lengthret <<= 1)
			;
		int *aux = new int [lengthret]();
		int *aux1 = new int [lengthret]();
		int *aux2 = new int [lengthret]();
		memcpy(aux, a, sizeof(int) * (length + 1));
		memcpy(aux2, p.a, sizeof(int) * (p.length + 1));
		NTT(aux, lengthret, 1, multmoder[0], multroot[0]);
		NTT(aux2, lengthret, 1, multmoder[0], multroot[0]);
		for (int i = 0; i < lengthret; ++ i){
			aux[i] = 1ll * aux[i] * aux2[i] % multmoder[0];
		}
		NTT(aux, lengthret, -1, multmoder[0], multinvroot[0]);
		memcpy(aux1, a, sizeof(int) * (length + 1));
		memset(aux2, 0, sizeof(int) * lengthret);
		memcpy(aux2, p.a, sizeof(int) * (p.length + 1));
		NTT(aux1, lengthret, 1, multmoder[1], multroot[1]);
		NTT(aux2, lengthret, 1, multmoder[1], multroot[1]);
		for (int i = 0; i < lengthret; ++ i){
			aux1[i] = 1ll * aux1[i] * aux2[i] % multmoder[1];
		}
		NTT(aux1, lengthret, -1, multmoder[1], multinvroot[1]);
		poly ret(n, moder, root, invroot);
		for(int i = 0; i <= n; ++ i){
			modequa <ll> equa(aux[i], multmoder[0]), equb(aux1[i], multmoder[1]);
			ret.a[i] = equa.crt(equb).getremain() % moder;
		}
		delete [] aux;
		delete [] aux1;
		delete [] aux2;
		return ret;
	}
	------------------------------------------------------------------------*/
	
	poly operator * (const int &p)const{
		int q = (p % moder + moder) % moder;
		if (!q) return poly(-1, moder, root, invroot);
		poly ret(length, moder, root, invroot);
		for (int i = 0; i <= length; ++ i){
			ret.a[i] = 1ll * a[i] * q % moder;
		}
		return ret;
	}
	
	friend poly operator * (const int &q, const poly &p){return p * q;}
	poly &operator += (const poly &p){*this = *this + p; return *this;}
	poly &operator -= (const poly &p){*this = *this - p; return *this;}
	poly &operator *= (const poly &p){*this = *this * p; return *this;}
	poly &operator *= (const int &p){*this = *this * p; return *this;}
	
	poly inv(int n)const{
		if (!a[0]) assert(("Invalid polynomial inv!", 0));
		poly ret(1, moder, root, invroot);
		ret.a[0] = powermod(a[0], moder - 2, moder);
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
		if (!~length) return poly(-1, moder, root, invroot);
		poly ret(length - 1, moder, root, invroot);
		for (int i = 0; i < length; ++ i){
			ret.a[i] = 1ll * a[i + 1] * (i + 1) % moder;
		}
		return ret;
	}
	
	poly integral()const{
		int *aux = new int [length + 3];
		aux[0] = 0, aux[1] = 1;
		for (int i = 2; i <= length + 1; ++ i){
			aux[i] = (moder - 1ll * (moder / i) * aux[moder % i] % moder) % moder;
		}
		poly ret(length + 1, moder, root, invroot);
		for (int i = length + 1; i; -- i){
			ret.a[i] = 1ll * a[i - 1] * aux[i] % moder;
		}
		delete [] aux;
		return ret;
	}
	
	poly operator / (const poly &p)const{
		if (!~p.length) assert(("Invalid polynomial division!", 0));
		if (p.length > length) return poly(-1, moder, root, invroot);
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
		if (a[0] != 1) assert(("Invalid polynomial log!", 0));
		poly aux(*this, n - 1);
		poly ret(aux.der() * aux.inv(n));
		ret.setlength(n - 2);
		return ret.integral();
	}
	
	poly exp(int n)const{
		if (a[0]) assert(("Invalid polynomial exp!", 0));
		poly ret(0, moder, root, invroot);
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
		poly ret(0, moder, root, invroot), aux(*this);
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
