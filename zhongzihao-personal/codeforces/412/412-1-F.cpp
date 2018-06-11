#include<bits/stdc++.h>
#define ll long long

const int N = 100;
const double PI = acos(-1);

int moder;

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
		if (ans % moder != remain || ans % p.moder != p.remain){
			//printf("%I64d %I64d %I64d %I64d %I64d\n", ans, remain, moder, p.remain, p.moder);
			//assert(0);
		}//210169508 998244353 197586596 1004535809
		return modequa <T>(ans, lcm);
	}
};

struct Poly{
	const static int MAX = 17;
	
	int a[1 << MAX];
	int length;
	
	Poly () : length(-1){
		memset(a, 0, sizeof(a));
	}
	
	void setlength(int length){
		if (length >= this -> length){
			this -> length = length;
			return;
		}
		memset(a + length + 1, 0, sizeof(int) * (this -> length - length));
		this -> length = length;
	}
	
	void clear(){
		memset(a, 0, sizeof(int) * (length + 1));
		length = -1;
	}
};

void assign(Poly &p, Poly &q){
	memset(p.a, 0, sizeof(int) * (p.length + 1));
	memcpy(p.a, q.a, sizeof(int) * (q.length + 1));
	p.length = q.length;
}

void add(Poly &p, Poly &q){
	if (!~p.length){
		p = q;
		return;
	}
	if (!~q.length){
		return;
	}
	p.length = std::max(p.length, q.length);
	for (int i = 0; i <= p.length; ++ i){
		p.a[i] = (p.a[i] + q.a[i]) % moder;
	}
	for ( ; ~p.length && !p.a[p.length]; -- p.length);
}

void minus(Poly &p, Poly &q){
	if (!~p.length){
		p = q;
		return;
	}
	if (!~q.length){
		return;
	}
	p.length = std::max(p.length, q.length);
	for (int i = 0; i <= p.length; ++ i){
		p.a[i] = (p.a[i] - q.a[i] + moder) % moder;
	}
	for ( ; ~p.length && !p.a[p.length]; -- p.length);
}

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

const int MAX = 17;

void mult(Poly &p, Poly &q){
	static int multmoder[2] = {(119 << 23) + 1, (479 << 21) + 1};
	static int multroot[2] = {3, 3};
	static int multinvroot[2] = {332748118, 334845270};
	static int aux[1 << MAX], aux1[1 << MAX];
	int n = p.length + q.length;
	int lengthans = 1;
	for ( ; lengthans <= n; lengthans <<= 1)
		;
	memcpy(aux, q.a, sizeof(int) * lengthans);
	memcpy(aux1, q.a, sizeof(int) * lengthans);
	NTT(p.a, lengthans, 1, multmoder[0], multroot[0]);
	NTT(aux, lengthans, 1, multmoder[0], multroot[0]);
	for (int i = 0; i < lengthans; ++ i){
		aux[i] = 1ll * aux[i] * p.a[i] % multmoder[0];
	}
	NTT(p.a, lengthans, -1, multmoder[0], multinvroot[0]);
	NTT(aux, lengthans, -1, multmoder[0], multinvroot[0]);
	NTT(p.a, lengthans, 1, multmoder[1], multroot[1]);
	NTT(aux1, lengthans, 1, multmoder[1], multroot[1]);
	for (int i = 0; i < lengthans; ++ i){
		aux1[i] = 1ll * aux1[i] * p.a[i] % multmoder[1];
	}
	NTT(aux1, lengthans, -1, multmoder[1], multinvroot[1]);
	memset(p.a, 0, sizeof(int) * lengthans);
	p.length = n;
	for(int i = 0; i <= p.length; ++ i){
		modequa <ll> equa(aux[i], multmoder[0]), equb(aux1[i], multmoder[1]);
		equa = equa.crt(equb);
		p.a[i] = equa.getremain() % moder;
	}
}

int maxn, maxa;
Poly a, b, ret1, ret2;
int q[N];

int main(){
	scanf("%d%d%d", &maxn, &maxa, &moder);
	if (maxa == 1){
		return printf("0\n"), 0;
	}
	int cnt = 0;
	for (maxa >>= 1; maxa; maxa >>= 1){
		q[cnt ++] = maxa;
	}
	std::reverse(q, q + cnt);
	int ans = 1;
	a.a[0] = b.a[1] = 1;
	a.length = b.length = maxn;
	for (int i = 0; i < cnt - 1; ++ i){
		assign(ret1, a);
		add(ret1, b);
		mult(ret1, q[i] & 1 ? b : a);
		if (q[i] & 1 ? b.a[0] : a.a[0]){
			minus(ret1, b);
		}
		else{
			add(ret1, a);
		}
		ret1.setlength(maxn);
		assign(ret2, a);
		add(ret2, b);
		mult(ret2, q[i] & 1 ? a : b);
		if (q[i] & 1 ? a.a[0] : b.a[0]){
			minus(ret2, a);
		}
		else{
			add(ret2, b);
		}
		ret2.setlength(maxn);
		if (q[i + 1] & 1){
			assign(a, ret1);
			for (int i = 1; i <= maxn; ++ i){
				b.a[i] = (ret2.a[i] + ret1.a[i - 1] + ret2.a[i - 1]) % moder;
			}
		}
		else{
			assign(a, ret1);
			assign(b, ret2);
		}
		for (int i = 1; i <= maxn; ++ i){
			if (i & 1){
				ans = (ans + b.a[i]) % moder;
			}
		}
	}
	return printf("%d\n", ans), 0;
}
