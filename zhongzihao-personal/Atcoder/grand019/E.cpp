// 多项式模板（取模）
// 使用方法见多项式模板 

#include<bits/stdc++.h>

typedef long long ll;

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

void NTT(int *a, int length, int type, int moder, int root){
	if (length == 1) return;
	int len = -1;
	for (int x = length; x; ++ len, x >>= 1);
	for(int i = 1, j = 0; i < length - 1; ++ i){
		for(int s = length; j ^= s >>= 1, ~j & s; )
			;
		if(i < j){
			std::swap(a[i], a[j]);
		}
	}
	int *w = new int [length];
	w[0] = 1, w[1] = powermod(root, moder - 1 >> len, moder);
	for (int i = 2; i < length; ++ i){
		w[i] = 1ll * w[i - 1] * w[1] % moder;
	}
	for (int i = 1; i <= len; ++ i){
		for (int j = 0, szk = 1 << i - 1, szw = length >> i; j < length; j += 1 << i){
			for (int k = j, noww = 0; k < j + szk; ++ k, noww += szw){
				int s = a[k], t = 1ll * w[noww] * a[k + szk] % moder;
				a[k] = s + t >= moder ? s + t - moder : s + t;
				a[k + szk] = s - t < 0 ? s - t + moder : s - t;
			}
		}
	}
	delete [] w;
	if (type == 1) return;
	int inv = powermod(length, moder - 2, moder);
	for (int i = 0; i < length; ++ i){
		a[i] = (ll) a[i] * inv % moder;
	}
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
};

const int N = 10010;
const int moder = 119 << 23 | 1;
const int root = 3;
const int invroot = 332748118;

char a[N], b[N];
int fac[N], inv[N];

int powermod(int a, int exp){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

poly powermod(poly a, int exp){
	int length = a.getlength();
	poly ret(length, moder, root, invroot);
	ret[0] = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret *= a;
			ret.setlength(length);
		}
		a *= a;
		a.setlength(length);
	}
	return ret;
}

int main(){
	fac[0] = 1;
	for (int i = 1; i < N; ++ i){
		fac[i] = 1ll * i * fac[i - 1] % moder;
	}
	inv[N - 1] = powermod(fac[N - 1], moder - 2);
	for (int i = N - 1; i; -- i){
		inv[i - 1] = 1ll * inv[i] * i % moder;
	}
	scanf("%s%s", a, b);
	int n = strlen(a);
	int m = 0, e = 0;
	for (int i = 0; i < n; ++ i){
		m += a[i] == '1' && b[i] == '1';
		e += a[i] == '1' && b[i] == '0';
	}
	poly p(m, moder, root, invroot);
	for (int i = 0; i <= m; ++ i){
		p[i] = inv[i + 1];
	}
	p = powermod(p, e);
	int ans = 0;
	for (int i = 0; i <= m; ++ i){
		ans += p[i];
		ans -= ans >= moder ? moder : 0;
	}
	ans = 1ll * ans * fac[m] % moder * fac[e] % moder * fac[m + e] % moder;
	printf("%d\n", ans);
	return 0;
}
