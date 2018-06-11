#include<bits/stdc++.h>
#define ll long long

class BigInteger{
private:
	const static int moder = (119 << 23) + 1;
	const static int root = 3;
	const static int invroot = 332748118;
	
	int *a;
	int length, sig;
	
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
	
	BigInteger(int length, int type):length(length), sig(0){apply(length);}
	BigInteger(const BigInteger &p, int length):length(length), sig(p.sig){apply(length), memcpy(a, p.a, sizeof(int) * std::min(p.length, length));}
		
	bool absgreaterequal(const BigInteger &q)const &{
		if (length != q.length) return length > q.length;
		for (int i = length - 1; ~i; -- i){
			if (a[i] > q.a[i]) return true;
			if (a[i] < q.a[i]) return false;
		}
		return true;
	}

	BigInteger operator << (const int &dis)const &{
		if (!sig) return *this;
		BigInteger ret(length + dis);
		memcpy(ret.a + dis, a, sizeof(int) * length);
		ret.sig = sig;
		return ret;
	}
	
	BigInteger operator >>(const int &dis)const &{
		if (dis >= length) return BigInteger();
		BigInteger ret(length - dis);
		memcpy(ret.a, a + dis, sizeof(int) * ret.length);
		ret.sig = sig;
		return ret;
	}
	
	int powermod(int a, int exp)const &{
		int ret = 1;
		for ( ; exp; exp >>= 1){
			if (exp & 1){
				ret = (ll) ret * a % moder;
			}
			a = (ll) a * a % moder;
		}
		return ret;
	}
	
	void NTT(int *a, int length, int type)const &{
		int len = -1;
		for (int x = length; x; ++ len, x >>= 1)
			;
		for(int i = 1, j = 0; i < length - 1; ++ i){
			for(int s = length; j ^= s >>= 1, ~j & s; )
				;
			if(i < j){
				std::swap(a[i], a[j]);
			}
		}
		for (int i = 1; i <= len; ++ i){
			for (int j = 0, unit = powermod(type == 1 ? root : invroot, moder - 1 >> i), szk = 1 << i - 1; j < length; j += 1 << i){
				for (int k = j, w = 1; k < j + szk; ++ k){
					int s = a[k], t = (ll) w * a[k + szk] % moder;
					a[k] = s + t; a[k] -= a[k] >= moder ? moder : 0;
					a[k + szk] = s - t; a[k + szk] += a[k + szk] < 0 ? moder : 0;
					w = (ll) w * unit % moder;
				}
			}
		}
		if (type == 1) return;
		int inv = powermod(length, moder - 2);
		for (int i = 0; i < length; ++ i){
			a[i] = (ll) a[i] * inv % moder;
		}
	}
	
	int divide(BigInteger &p, const int &q)const &{
		if (!q) assert(("Division by zero!", 0));
		if (!p.sig) return 0;
		ll remain = 0, x = std::abs(q);
		for (int i = length - 1; ~i; -- i){
			remain = remain * 10 + p.a[i];
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
	BigInteger():length(0), sig(0){a = nullptr;}
	BigInteger(const BigInteger &p):length(p.length), sig(p.sig){apply(length), memcpy(a, p.a, sizeof(int) * length);}
	~BigInteger(){destroy();}
	int getlength(){return length;}
	bool positive(){return sig > 0;}
	bool iszero(){return !sig;}
	bool negative(){return sig < 0;}
	bool even(){return !sig || !(a[0] & 1);}
	
	BigInteger &operator = (const BigInteger &p){
		destroy();
		apply(p.length);
		length = p.length;
		sig = p.sig;
		memcpy(a, p.a, sizeof(int) * length);
		return *this;
	}
	
	template <typename T>
	BigInteger &operator = (const T &p){
		destroy();
		sig = p ? p > 0 ? 1 : -1 : 0;
		apply(40);
		int cnt = 0;
		for (T x = std::abs(p); x; x /= 10){
			a[cnt ++] = x % 10;
		}
		resize(cnt);
		return *this;
	}

	void read(){
		destroy();
		sig = 1;
		char ch = getchar();
		for ( ; ch < '0' || ch > '9'; ch = getchar()){
			if (ch == '-') sig = -1;
		}
		resize(1);
		int nowlength = 0;
		for ( ; ch >= '0' && ch <= '9'; ch = getchar()){
			a[nowlength ++] = ch - '0';
			if (nowlength == length) resize(length << 1);
		}
		std::reverse(a, a + nowlength);
		for ( ; nowlength && !a[nowlength - 1]; -- nowlength)
			;
		resize(nowlength);
		sig = length ? sig : 0;
	}
	
	void write(){
		if (!sig) return (void) putchar('0');
		if (sig < 0){
			putchar('-');
		}
		for (int i = length - 1; ~i; i--){
			putchar(a[i] + '0');
		}
	}
	
	template <typename T>
	T tointeger(){
		T ret = 0;
		for (int i = length - 1; i >= 0; ++ i){
			ret = ret * 10 + a[i];
		}
		return ret * sig;
	}
	
	bool operator == (const BigInteger &p) const &{
		if (sig != p.sig || length != p.length)	return false;
		for (int i = 0; i < length; ++ i){
			if (a[i] != p.a[i])	return false;
		}
		return true;
	}
	
	bool operator > (const BigInteger &p) const &{
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
			if (a[i] < 10 && a[i] >= 0) break;
			a[i] >= 10 ? (a[i] -= 10, ++ a[i + 1]) : (a[i] += 10, -- a[i + 1]);
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
	
	BigInteger operator + (const BigInteger &p)const &{
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
			ret.a[i] >= 10 ? (ret.a[i] -= 10, ++ ret.a[i + 1]) : ret.a[i] < 0 ? (ret.a[i] += 10, -- ret.a[i + 1]) : 0;
		}
		for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		ret.resize(ret.length);
		ret.sig = ret.length ? flag ? 1 : -1 : 0;
		return ret;
	}
	
	BigInteger operator - ()const &{
		BigInteger ret(*this);
		ret.sig = -ret.sig;
		return ret;
	}
	
	BigInteger operator - (const BigInteger &p)const &{
		return *this + (-p);
	}
	
	BigInteger operator * (const BigInteger &p)const &{
		if (!sig || !p.sig) return BigInteger();
		int n = length + p.length;
		int lengthret = 1;
		for ( ; lengthret < n; lengthret <<= 1)
			;
		BigInteger ret(*this, lengthret);
		int *aux = new int [lengthret]();
		memcpy(aux, p.a, sizeof(int) * p.length);
		NTT(ret.a, lengthret, 1);
		NTT(aux, lengthret, 1);
		for (int i = 0; i < lengthret; ++ i){
			ret.a[i] = (ll) ret.a[i] * aux[i] % moder;
		}
		NTT(ret.a, lengthret, -1);
		for (int i = 0; i < n - 1; i++){
			ret.a[i + 1] += ret.a[i] / 10;
			ret.a[i] %= 10;
		}
		for ( ; n && !ret.a[n - 1]; -- n)
			;
		ret.resize(n);
		ret.sig = sig * p.sig;
		return ret;
	}

	BigInteger operator * (const int &p)const &{
		if (!p || !sig) return BigInteger();
		BigInteger ret(*this, length + 10);
		ll x = std::abs(p), remain = 0;
		for (int i = 0; i < length; ++ i){
			remain += ret.a[i] * x;
			ret.a[i] = remain % 10;
			remain /= 10;
		}
		int nowlength = length;
		for (ret.a[nowlength] = remain; ret.a[nowlength]; ++ nowlength){
			ret.a[nowlength + 1] = ret.a[nowlength] / 10;
			ret.a[nowlength] %= 10;
		}
		for ( ; nowlength && !ret.a[nowlength - 1]; -- nowlength)
			;
		ret.resize(nowlength);
		ret.sig = sig * (p < 0 ? -1 : 1);
		return ret;
	}
	
	BigInteger operator / (const BigInteger &p)const &{
		if (!p.sig) assert(("Division by zero!", 0));
		if (!sig || length < p.length) return BigInteger();
		int num = 0;
		for (int i = p.length - 1; i >= p.length - 3; -- i){
			(num *= 10) += i >= 0 ? p.a[i] : 0;
		}
		num = 100000 / num;
		int nowprecision = 1;
		BigInteger ret;
		ret = num;
		for ( ; nowprecision <= length - p.length; nowprecision <<= 1){
			BigInteger aux((nowprecision << 1) + 3);
			aux.sig = 1;
			for (int i = p.length - aux.length; i < p.length; ++ i){
				aux.a[i - p.length + aux.length] = i >= 0 ? p.a[i] : 0;
			}
			aux = (aux * ret >> nowprecision + 2) * ret >> nowprecision + 2;
			ret = (ret * 2 << nowprecision) - aux;
		}
		ret = ret * *this >> p.length + nowprecision + 1;
		ret.sig = std::abs(ret.sig);
		BigInteger aux(p);
		aux.sig = std::abs(aux.sig);
		if (!absgreaterequal(ret * aux)) -- ret;
		else if (!absgreaterequal(++ ret * aux)) -- ret; 
		ret.sig *= sig * p.sig;
		return ret;
	}
	
	BigInteger operator / (const int &p)const &{
		BigInteger ret(*this);
		divide(ret, p);
		ret.resize(ret.length);
		return ret;
	}
	
	BigInteger sqrt()const &{
		if (sig < 0) assert(("Sqrt a negative number!", 0));
		if (!sig) return *this;
		int num = 0;
		for (int i = length - 1; i >= length - 8; -- i){
			(num *= 10) += i >= 0 ? a[i] : 0;
		}
		ll x = length & 1 ? 10000000000000ll : 100000000000000ll;
		num = std::sqrt(1.0 * x / num);
		int nowprecision = 2;
		BigInteger ret;
		ret = num;
		for ( ; nowprecision <= (length >> 1) + 1; nowprecision = (nowprecision << 1) - 1){
			BigInteger aux((nowprecision << 1) + 1 + (length & 1));
			aux.sig = 1;
			for (int i = length - aux.length; i < length; ++ i){
				aux.a[i - length + aux.length] = i >= 0 ? a[i] : 0;
			}
			aux = ((aux * ret >> nowprecision + 1) * ret >> nowprecision + 1) / 2;
			BigInteger aux1(nowprecision + 1 << 1);
			aux1.sig = 1;
			aux1.a[aux1.length - 1] = 1, aux1.a[aux1.length - 2] = 5;
			ret = ret * (aux1 - aux) >> nowprecision + 2;
		}
		ret = ret * *this >> (length >> 1) + nowprecision + 1;
		if (!absgreaterequal(ret * ret)) -- ret;
		else {++ ret; if (!absgreaterequal(ret * ret)) -- ret;}
		return ret;
	}
	
	BigInteger operator % (const BigInteger &p)const &{
		if (!p.sig) assert(("Division by zero!", 0));
		return *this - *this / p * p;
	}
	
	int operator % (const int &p)const &{
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
};

BigInteger a, b;
/*
bool checker1(BigInteger &p){
	if (!p.length && p.sig){
		return false;
	}
	for (int i = p.length; i < 1 << BigInteger::MAX; ++ i){
		if (p.a[i]){
			return false;
		}
	}
	return true;
}

bool checker2(BigInteger &p, BigInteger &q){
	if (p.length != q.length){
		return false;
	}
	if (p.sig != q.sig){
		return false;
	}
	for (int i = 0; i < 1 << BigInteger::MAX; ++ i){
		if (p.a[i] != q.a[i]){
			return false;
		}
	}
	return true;
}
*/

int main(){
	a.read();
	b.read();
	(a + b).write();
	putchar('\n');
	(a - b).write();
	putchar('\n');
	(a * b).write();
	putchar('\n');
	(a / b).write();
	putchar('\n');
	if (!a.negative()){
		a.sqrt().write();
		putchar('\n');
	}
	if (!b.negative()){
		b.sqrt().write();
		putchar('\n');
	}
	return 0;
}
