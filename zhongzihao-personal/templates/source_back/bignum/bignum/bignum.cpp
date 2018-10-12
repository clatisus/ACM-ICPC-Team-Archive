// 大整数模板 

#include<bits/stdc++.h>
#include"ntt.cpp"

class BigInteger{
private:
	const static int moder = (119 << 23) + 1, root = 3, invroot = 332748118;
	
	int *a;
	int length, sig, base;
	
	void apply(int length){
		if (!length) return;
		a = new int [length]();
		this -> length = length;
	}
	
	void destroy(){
		delete [] a;
		a = nullptr;
		length = sig = 0;
	}
	
	void resize(int length){
		if (length == this -> length) return;
		if (!length) return destroy();
		int *aux = a, prelength = this -> length;
		apply(length);
		memcpy(a, aux, sizeof(int) * std::min(length, prelength));
		delete [] aux;
	}
	
	void InitBigInteger(const BigInteger &p, int length){
		destroy();
		if (!p.sig || !length) return;
		sig = p.sig, base = p.base;
		apply(length);
		memcpy(a, p.a, sizeof(int) * std::min(p.length, length));
	}
	
	template <typename T>
	void InitInteger(const T &p, const int &base){
		destroy();
		sig = p ? p > 0 ? 1 : -1 : 0;
		int cnt = 0;
		for (T x = std::abs(p); x; x /= base){
			++ cnt;
		}
		apply(cnt);
		T x = std::abs(p);
		for (int i = 0; i < cnt; x /= base, ++ i){
			a[i] = x % base;
		}
		this -> base = base;
	}
	
	BigInteger(int length, int base, int type):a(nullptr), base(base), sig(1){apply(length);}
	BigInteger(const BigInteger &p, int length):a(nullptr){InitBigInteger(p, length);}
		
	bool absgreaterequal(const BigInteger &q)const{
		if (length != q.length) return length > q.length;
		for (int i = length - 1; ~i; -- i){
			if (a[i] > q.a[i]) return true;
			if (a[i] < q.a[i]) return false;
		}
		return true;
	}
	
	static int divide(BigInteger &p, const int &q){
		if (!q) assert(("Division by zero!", 0));
		if (!p.sig) return 0;
		ll remain = 0, x = std::abs(q);
		for (int i = p.length - 1; ~i; -- i){
			remain = remain * p.base + p.a[i];
			p.a[i] = remain / x;
			remain %= x;
		}
		for ( ; p.length && !p.a[p.length - 1]; -- p.length)
			;
		remain *= p.sig;
		p.sig *= q < 0 ? -1 : 1;
		if (!p.length){
			p.sig = 0;
		}
		return remain;
	}

public:
	BigInteger():a(nullptr), length(0), sig(0), base(10){}
	BigInteger(int base):a(nullptr), length(0), sig(0), base(base){}
	BigInteger(const BigInteger &p):a(nullptr){InitBigInteger(p, p.length);}
	template <typename T> BigInteger(const T &p, int base):a(nullptr){InitInteger(p, base);}
	BigInteger(int *a, int length, int sig, int base):a(nullptr), sig(sig), base(base){for ( ; length && !a[length - 1]; -- length); apply(length); memcpy(this -> a, a, sizeof(int) * length);}
	~BigInteger(){destroy();}
	int operator [](int n){return n >= length ? 0 : a[n];}
	int getlength(){return length;}
	int getsig(){return sig;}
	int getbase(){return base;}
	
	BigInteger &operator = (const BigInteger &p){
		if (this != &p) InitBigInteger(p, p.length);
		return *this;
	}
	
	template <typename T>
	BigInteger &operator = (const T &p){
		InitInteger(p, 10);
		return *this;
	}
	
	inline int check(char ch, int base){
		int ret = ch >= '0' && ch <= '9' ? ch - '0' : ch >= 'a' && ch <= 'z' ? ch - 'a' + 10 : ch >= 'A' && ch <= 'Z' ? ch - 'A' + 10 : 100;
		return ret < base ? ret : -1;
	}

	void read(int base){
		destroy();
		sig = 1;
		char ch = getchar();
		for ( ; !~check(ch, base); ch = getchar()){
			if (ch == '-') sig = -1;
		}
		resize(1);
		int nowlength = 0;
		for (int x; ~(x = check(ch, base)); ch = getchar()){
			a[nowlength ++] = x;
			if (nowlength == length) resize(length << 1);
		}
		std::reverse(a, a + nowlength);
		for ( ; nowlength && !a[nowlength - 1]; -- nowlength)
			;
		resize(nowlength);
		sig = length ? sig : 0;
		this -> base = base;
	}
	
	// type 为 0 小写，1 大写 
	void write(int type){
		if (!sig) return (void) putchar('0');
		if (sig < 0){
			putchar('-');
		}
		for (int i = length - 1; ~i; -- i){
			putchar(a[i] < 10 ? a[i] + '0' : a[i] - 10 + (type ? 'A' : 'a'));
		}
	}
	
	template <typename T>
	T tointeger(){
		T ret = 0;
		for (int i = length - 1; i >= 0; ++ i){
			ret = ret * base + a[i];
		}
		return ret * sig;
	}
	
	bool operator == (const BigInteger &p)const{
		if (sig != p.sig || length != p.length || base != p.base) return false;
		for (int i = 0; i < length; ++ i){
			if (a[i] != p.a[i])	return false;
		}
		return true;
	}
	
	bool operator > (const BigInteger &p)const{
		if (sig != p.sig) return sig > p.sig;
		if (length != p.length) return length > p.length ^ sig == -1;
		for (int i = length - 1; i >= 0; -- i){
			if (a[i] > p.a[i]) return sig > 0;
			if (a[i] < p.a[i]) return sig < 0;
		}
		return false;
	}

	BigInteger &operator ++ (){
		resize(length + 1);
		sig >= 0 ? ++ a[0] : -- a[0];
		for (int i = 0; i < length - 1; ++ i){
			if (a[i] < base && a[i] >= 0) break;
			a[i] >= base ? (a[i] -= base, ++ a[i + 1]) : (a[i] += base, -- a[i + 1]);
		}
		for ( ; length && !a[length - 1]; -- length)
			;
		resize(length);
		sig = length ? sig >= 0 ? 1 : -1 : 0;
		return *this;
	}
	
	BigInteger &operator -- (){
		sig = -sig;
		++ *this;
		sig = -sig;
		return *this;
	}
	
	// 右移和左移均为移动该大整数的进制位 
	BigInteger operator << (const int &dis)const{
		if (!sig) return *this;
		BigInteger ret(length + dis, base, 0);
		memcpy(ret.a + dis, a, sizeof(int) * length);
		ret.sig = sig;
		return ret;
	}
	
	BigInteger operator >>(const int &dis)const{
		if (dis >= length) return BigInteger();
		BigInteger ret(length - dis, base, 0);
		memcpy(ret.a, a + dis, sizeof(int) * ret.length);
		ret.sig = sig;
		return ret;
	}
	
	BigInteger operator + (const BigInteger &p)const{
		if (!p.sig) return *this;
		if (!sig) return p;
		bool type = true, flag = sig > 0;
		const BigInteger *aux = this, *aux1 = &p;
		if (sig != p.sig){
			type = false;
			if (!absgreaterequal(p)){
				flag = !flag;
				std::swap(aux, aux1);
			}
		}
		BigInteger ret(*aux, std::max(length, p.length) + 1);
		for (int i = 0; i < ret.length - 1; ++ i){
			ret.a[i] += i < aux1 -> length ? type ? aux1 -> a[i] : -aux1 -> a[i] : 0;
			ret.a[i] >= base ? (ret.a[i] -= base, ++ ret.a[i + 1]) : ret.a[i] < 0 ? (ret.a[i] += base, -- ret.a[i + 1]) : 0;
		}
		for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		ret.resize(ret.length);
		ret.sig = ret.length ? flag ? 1 : -1 : 0;
		return ret;
	}
	
	BigInteger operator - ()const{
		BigInteger ret(*this);
		ret.sig = -ret.sig;
		return ret;
	}
	
	BigInteger operator - (const BigInteger &p)const{
		return *this + (-p);
	}
	
	BigInteger operator * (const BigInteger &p)const{
		if (!sig || !p.sig) return BigInteger(base);
		int n = length + p.length;
		int lengthret = 1;
		for ( ; lengthret < n; lengthret <<= 1)
			;
		BigInteger ret(*this, lengthret);
		int *aux = new int [lengthret]();
		memcpy(aux, p.a, sizeof(int) * p.length);
		NTT(ret.a, lengthret, 1, moder, root);
		NTT(aux, lengthret, 1, moder, root);
		for (int i = 0; i < lengthret; ++ i){
			ret.a[i] = (ll) ret.a[i] * aux[i] % moder;
		}
		NTT(ret.a, lengthret, -1, moder, invroot);
		for (int i = 0; i < n - 1; ++ i){
			ret.a[i + 1] += ret.a[i] / base;
			ret.a[i] %= base;
		}
		for ( ; n && !ret.a[n - 1]; -- n)
			;
		ret.resize(n);
		ret.sig = sig * p.sig;
		return ret;
	}

	BigInteger operator * (const int &p)const{
		if (!p || !sig) return BigInteger(base);
		BigInteger ret(*this, length + 40);
		ll x = std::abs(p), remain = 0;
		for (int i = 0; i < length; ++ i){
			remain += ret.a[i] * x;
			ret.a[i] = remain % base;
			remain /= base;
		}
		int nowlength = length;
		for (ret.a[nowlength] = remain; ret.a[nowlength]; ++ nowlength){
			ret.a[nowlength + 1] = ret.a[nowlength] / base;
			ret.a[nowlength] %= base;
		}
		for ( ; nowlength && !ret.a[nowlength - 1]; -- nowlength)
			;
		ret.resize(nowlength);
		ret.sig = sig * (p < 0 ? -1 : 1);
		return ret;
	}
	
	BigInteger operator / (const BigInteger &p)const{
		if (!p.sig) assert(("Division by zero!", 0));
		if (!sig || length < p.length) return BigInteger(base);
		int num = 0, x = 1;
		for (int i = p.length - 1; i >= p.length - 3; -- i){
			(num *= base) += i >= 0 ? p.a[i] : 0;
		}
		for (int i = 0; i < 5; ++ i){
			x *= base;
		}
		BigInteger ret(x / num, base);
		int noweps = 1;
		for ( ; noweps <= length - p.length; noweps <<= 1){
			BigInteger aux((noweps << 1) + 3, base, 0);
			for (int i = p.length - aux.length; i < p.length; ++ i){
				aux.a[i - p.length + aux.length] = i >= 0 ? p.a[i] : 0;
			}
			aux = (aux * ret >> noweps + 2) * ret >> noweps + 2;
			ret = (ret * 2 << noweps) - aux;
		}
		ret = ret * *this >> p.length + noweps + 1;
		ret.sig = std::abs(ret.sig);
		BigInteger aux(p);
		aux.sig = std::abs(aux.sig);
		if (!absgreaterequal(ret * aux)) -- ret;
		else if (!absgreaterequal(++ ret * aux)) -- ret; 
		ret.sig *= sig * p.sig;
		return ret;
	}
	
	BigInteger operator / (const int &p)const{
		BigInteger ret(*this);
		divide(ret, p);
		ret.resize(ret.length);
		return ret;
	}
	
	BigInteger sqrt()const{
		if (sig < 0) assert(("Sqrt a negative number!", 0));
		if (!sig) return *this;
		ll num = 0, x = 1;
		for (int i = length - 1; i >= length - 8; -- i){
			(num *= 10) += i >= 0 ? a[i] : 0;
		}
		for (int i = 0, sz = length & 1 ? 13 : 14; i < sz; ++ i){
			x *= base;
		}
		BigInteger ret((ll) std::sqrt(1.0 * x / num), base);
		int noweps = 2;
		for ( ; noweps <= (length >> 1) + 1; noweps = (noweps << 1) - 1){
			BigInteger aux((noweps << 1) + 1 + (length & 1), base, 0);
			for (int i = length - aux.length; i < length; ++ i){
				aux.a[i - length + aux.length] = i >= 0 ? a[i] : 0;
			}
			aux = ((aux * ret >> noweps + 1) * ret >> noweps + 1) / 2;
			BigInteger aux1(noweps + 1 << 1, base, 0);
			aux1.a[aux1.length - 1] = 1, aux1.a[aux1.length - 2] = 5;
			ret = ret * (aux1 - aux) >> noweps + 2;
		}
		ret = ret * *this >> (length >> 1) + noweps + 1;
		if (!absgreaterequal(ret * ret)) -- ret;
		else {++ ret; if (!absgreaterequal(ret * ret)) -- ret;}
		return ret;
	}
	
	BigInteger operator % (const BigInteger &p)const{
		if (!p.sig) assert(("Division by zero!", 0));
		return *this - *this / p * p;
	}
	
	int operator % (const int &p)const{
		if (!p) assert(("Division by zero!", 0));
		BigInteger aux(*this);
		return divide(aux, p);
	}
	
	friend BigInteger operator * (const int &q, const BigInteger &p){return p * q;}
	BigInteger &operator += (const BigInteger &p){*this = *this + p; return *this;}
	BigInteger &operator -= (const BigInteger &p){*this = *this - p; return *this;}
	BigInteger &operator *= (const BigInteger &p){*this = *this * p; return *this;}
	BigInteger &operator *= (const int &p){*this = *this * p; return *this;}
	BigInteger &operator /= (const BigInteger &p){*this = *this / p; return *this;}
	BigInteger &operator /= (const int &p){*this = *this / p; return *this;}
	BigInteger &operator %= (const BigInteger &p){*this = *this % p; return *this;}
	BigInteger &operator %= (const int &p){*this = *this % p; return *this;}
	BigInteger &operator >>= (const int &dis){*this = *this >> dis; return *this;}
	BigInteger &operator <<= (const int &dis){*this = *this << dis; return *this;}
	BigInteger operator ++ (int){BigInteger aux(*this); ++ *this; return aux;}
	BigInteger operator -- (int){BigInteger aux(*this); -- *this; return aux;}
	
	BigInteger tobase(int base)const{
		if (this -> base == base) return *this;
		if (!this -> sig) return BigInteger(base);
		BigInteger *aux;
		aux = new BigInteger[this -> length];
		for (int i = 0; i < this -> length; ++ i){
			aux[i].InitInteger(this -> a[i], base);
		}
		BigInteger now(this -> base, base);
		for (int i = this -> length; i > 1; i = i + 1 >> 1){
			for (int j = 0; j < i >> 1; ++ j){
				aux[j] = aux[j << 1] + aux[j << 1 | 1] * now;
			}
			if (i & 1) aux[i >> 1] = aux[i - 1];
			now *= now;
		}
		BigInteger ret = aux[0];
		delete [] aux;
		return ret;
	}
};

int main(){
	return 0;
}
