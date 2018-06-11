#include<bits/stdc++.h>
#define ll long long

template <typename T> 
struct modequa{
private:
	T remain, moder;
	
	// 这样可以保证 |x| <= |b|, |y| <= |a|
	T extendedeuclid(T a, T b, T &x, T &y){
		T p;
		if (b){
			T ret = extendedeuclid(b, a % b, x, y);
			p = y, y = x - a / b * y, x = p;
			return ret;
		}
		x = 1, y = 0;
		return a;
	}
	
	ll getone(int n){return 1;}
	__int128 getone(ll n){return 1;}
	
public:
	modequa <T>(){}
	modequa <T>(T remain, T moder) : remain(remain), moder(moder){}
	T getremain(){return remain;}
	T getmoder(){return moder;}
	
	void setcandidates(T remain, T moder){
		this -> remain = remain;
		this -> moder = moder;
	}
	
	modequa <T> crt(const modequa <T> &p){
		T x, y;
		auto one = getone(remain);
		T gcd = extendedeuclid(moder, p.moder, x, y);
		if ((p.remain - remain) % gcd) return modequa <T>(0, 0);
		T lcm = moder / gcd * p.moder;
		T ans = (p.remain - remain) / gcd;
		ans = one * ans * x % lcm * moder % lcm;
		ans += remain;
		ans += ans < 0 ? lcm : ans >= lcm ? -lcm : 0;
		return modequa <T>(ans, lcm);
	}
};

// 如果模数不是质数，那么基本就只能做加减乘和求导了orz 
struct Poly{
private:
	const static int MAX = 19;
	
	static int numinv[1 << MAX];
	int a[1 << MAX];
	int length;
	int moder, root, invroot;
	// 常用的两组模数为 ((119 << 23) + 1, 3, 332748118) 和 ((479 << 21) + 1, 3, 334845270)

	int powermod(int a, int exp, int moder){
		int ret = 1;
		for ( ; exp; exp >>= 1){
			if (exp & 1){
				ret = 1ll * a * ret % moder;
			}
			a = 1ll * a * a % moder;
		}
		return ret;
	}
	
	void initinv(){
		numinv[1] = 1;
		for (int i = 2; i < 1 << MAX; ++ i){
			numinv[i] = (moder - 1ll * (moder / i) * numinv[moder % i] % moder) % moder;
		}
	}
	
	void NTT(int *a, int length, int type, int moder, int root){
		int len = -1;
		for (int x = length; x; ++ len, x >>= 1);
		for(int i = 1, j = 0; i < length - 1; ++ i){
			for(int s = length; j ^= s >>= 1, ~j & s; );
			if(i < j){
				std::swap(a[i], a[j]);
			}
		}
		for (int i = 1; i <= len; ++ i){
			int unit = powermod(root, moder - 1 >> i, moder);
			for (int j = 0; j < length; j += 1 << i){
				int w = 1;
				for (int k = j, szk = 1 << i - 1; k < j + szk; ++ k){
					int s = a[k], t = 1ll * w * a[k + szk] % moder;
					a[k] = s + t >= moder ? s + t - moder : s + t;
					a[k + szk] = s - t < 0 ? s - t + moder : s - t;
					w = 1ll * w * unit % moder;
				}
			}
		}
		if (type == 1) return;
		int inv = powermod(length, moder - 2, moder);
		for (int i = 0; i < length; ++ i){
			a[i] = 1ll * a[i] * inv % moder;
		}
	}

public:
	Poly() : length(-1){
		memset(a, 0, sizeof(a));
	}
	
	// 如果模数非NTT质数 root 和 invroot 随便设就好辣~ 
	Poly(int moder, int root, int invroot):moder(moder), root(root), invroot(invroot), length(-1){
		memset(a, 0, sizeof(a));
	}
	
	void clear(){
		memset(a, 0, sizeof(int) * (length + 1));
		length = -1;
		moder = root = invroot = 0;
	}
	
	void setmoder(int moder, int root, int invroot){
		clear();
		this -> moder = moder, this -> root = root, this -> invroot = invroot;
	}
	
	void setlength(int length){
		if (length >= this -> length){
			this -> length = length;
			return;
		}
		memset(a + length + 1, 0, sizeof(int) * (this -> length - length));
		this -> length = length;
	}
	
	void setvalue(int sit, int value){
		a[sit] = (value % moder + moder) % moder;
		length = std::max(sit, length);
		for ( ; ~length && !a[length]; -- length)
			;
	}
	
	int getvalue(int sit){return a[sit];}
	int getlength(){return length;}
	int getmoder(){return moder;}
	
	// 相当于乘以 x ^ dis
	void leftshift(int dis){
		for (int i = length + dis; i >= dis; -- i){
			a[i] = a[i - dis];
		}
		memset(a, 0, sizeof(int) * dis);
		length += dis;
	}
	
	// 相当于除以 x ^ dis
	void rightshift(int dis){
		if (dis > length) return setmoder(moder, root, invroot);
		for (int i = 0; i <= length - dis; ++ i){
			a[i] = a[i + dis];
		}
		memset(a + length - dis + 1, 0, sizeof(int) * dis);
		length = length - dis >= 0 ? length - dis : -1;
	}
	
	int value(int x){
		int now = 1, ret = 0;
		for (int i = 0; i <= length; ++ i){
			ret = (ret + 1ll * a[i] * now) % moder;
			now = 1ll * now * x % moder;
		}
		return ret;
	}

	void assign(Poly &q){
		memset(a, 0, sizeof(int) * (length + 1));
		memcpy(a, q.a, sizeof(int) * (q.length + 1));
		length = q.length, moder = q.moder, root = q.root, invroot = q.invroot;
	}
	
	void neg(){
		for (int i = 0; i <= length; ++ i){
			a[i] = a[i] ? moder - a[i] : 0;
		}
	}
	
	void add(Poly &q){
		if (moder != q.moder) assert(("Invalid polynomial addition!", 0));
		if (!~length) return assign(q);
		if (!~q.length) return;
		length = std::max(length, q.length);
		for (int i = 0; i <= length; ++ i){
			a[i] = a[i] + q.a[i];
			a[i] -= a[i] >= moder ? moder : 0;
		}
		for ( ; ~length && !a[length]; -- length)
			;
	}
	
	void minus(Poly &q){
		if (moder != q.moder) assert(("Invalid polynomial subtraction!", 0));
		if (!~length) return assign(q);
		if (!~length) return;
		length = std::max(length, q.length);
		for (int i = 0; i <= length; ++ i){
			a[i] = a[i] - q.a[i];
			a[i] += a[i] < 0 ? moder : 0;
		}
		for ( ; ~length && !a[length]; -- length)
			;
	}
	
	void mult(Poly &q){
		static int multmoder[2] = {998244353, 1004535809};
		static int multroot[2] = {3, 3};
		static int multinvroot[2] = {332748118, 334845270};
		static int aux[1 << MAX], aux1[1 << MAX];
		if (moder != q.moder) assert(("Invalid polynomial multiplication!", 0));
		if (!~length || !~q.length) return setmoder(moder, root, invroot);
		int n = length + q.length;
		int lengthans = 1;
		for ( ; lengthans <= n; lengthans <<= 1)
			;
		memcpy(aux, q.a, sizeof(int) * lengthans);
		memcpy(aux1, q.a, sizeof(int) * lengthans);
		NTT(a, lengthans, 1, multmoder[0], multroot[0]);
		NTT(aux, lengthans, 1, multmoder[0], multroot[0]);
		for (int i = 0; i < lengthans; ++ i){
			aux[i] = 1ll * aux[i] * a[i] % multmoder[0];
		}
		NTT(a, lengthans, -1, multmoder[0], multinvroot[0]);
		NTT(aux, lengthans, -1, multmoder[0], multinvroot[0]);
		NTT(a, lengthans, 1, multmoder[1], multroot[1]);
		NTT(aux1, lengthans, 1, multmoder[1], multroot[1]);
		for (int i = 0; i < lengthans; ++ i){
			aux1[i] = 1ll * aux1[i] * a[i] % multmoder[1];
		}
		NTT(aux1, lengthans, -1, multmoder[1], multinvroot[1]);
		memset(a, 0, sizeof(int) * lengthans);
		length = n;
		for(int i = 0; i <= length; ++ i){
			modequa <ll> equa(aux[i], multmoder[0]), equb(aux1[i], multmoder[1]);
			equa.crt(equb);
			a[i] = equa.getremain() % moder;
		}
	}
	
	void mult(int q){
		for (int i = 0; i <= length; ++ i){
			a[i] = 1ll * a[i] * q % moder;
		}
	}
	
	void inv(int n){
		static Poly aux, aux1;
		if (!a[0]) assert(("Invalid polynomial inv!", 0));
		aux.setmoder(moder, root, invroot);
		aux.length = 1;
		aux.a[0] = powermod(a[0], moder - 2, moder);
		for (int nowprecision = 0; nowprecision < n; ){
			nowprecision = (nowprecision << 1) + 1;
			aux1.assign(*this);
			aux1.setlength(nowprecision);
			aux1.mult(aux), aux1.setlength(nowprecision);
			aux1.mult(aux), aux1.setlength(nowprecision);
			aux.mult(2);
			aux.minus(aux1);
		}
		aux.setlength(n - 1);
		assign(aux);
	}
	
	void der(){
		if (!~length) return;
		for (int i = 0; i < length; ++ i){
			a[i] = 1ll * a[i + 1] * (i + 1) % moder;
		}
		a[length --] = 0;
	}
	
	void integral(){
		if (!numinv[1]){
			initinv();
		}
		for (int i = length + 1; i; -- i){
			a[i] = 1ll * a[i - 1] * numinv[i] % moder;
		}
		a[0] = 0;
		++ length;
	}
	
	void divide(Poly &q){
		static Poly aux;
		if (!~q.length || moder != q.moder) assert(("Invalid polynomial division!", 0));
		if (q.length > length) return setmoder(moder, root, invroot);
		aux.assign(q);
		int lengthans = length - q.length;
		aux.inv(length - q.length + 1);
		mult(aux);
		setlength(lengthans);
		for (int i = 0; i <= length >> 1; ++ i){
			std::swap(a[i], a[length - i]);
		}
	}
	
	void log(int n){
		static Poly aux;
		if (a[0] != 1) assert(("Invalid polynomial log!", 0));
		aux.assign(*this);
		aux.der();
		inv(n);
		mult(aux);
		setlength(n - 2);
		integral();
	}
	
	void exp(int n){
		static Poly aux, aux1;
		if (a[0]) assert(("Invalid polynomial exp!", 0));
		aux.setmoder(moder, root, invroot);
		aux.length = aux.a[0] = 1;
		for (int nowprecision = 0; nowprecision < n; ){
			nowprecision = (nowprecision << 1) + 1;
			aux1.assign(aux);
			aux1.log(nowprecision + 1);
			aux1.neg();
			aux1.add(*this);
			aux1.setlength(nowprecision);
			aux1.mult(aux);
			aux1.setlength(nowprecision);
			aux.add(aux1);
		}
		aux.setlength(n - 1);
		assign(aux);
	}
	
	void power(int exp){
		static Poly aux;
		if (!~length) return;
		aux.setmoder(moder, root, invroot);
		aux.a[0] = 1;
		aux.length = 0;
		for ( ; exp; exp >>= 1){
			if (exp & 1){
				aux.mult(*this);
			}
			aux.mult(aux);
		}
		assign(aux);
	}
};

int Poly::numinv[1 << Poly::MAX] = {};

Poly a(10000, 0, 0), b(10000, 0, 0);

int main(){
	for (int i = 0; i < 20; ++ i){
		a.setvalue(i, i + 1);
		b.setvalue(i, i + 1);
	}
	a.mult(b);
	for (int i = 0; i <= 40; ++ i){
		printf("%d ", a.getvalue(i));
	}
	putchar('\n');
	a.clear();
	b.clear();
	a.setmoder(10000, 0, 0);
	b.setmoder(10000, 0, 0);
	for (int i = 0; i < 10; ++ i){
		a.setvalue(i, i + 1);
		b.setvalue(i, i + 1);
	}
	a.mult(b);
	for (int i = 0; i <= 20; ++ i){
		printf("%d ", a.getvalue(i));
	}
	return 0;
}
