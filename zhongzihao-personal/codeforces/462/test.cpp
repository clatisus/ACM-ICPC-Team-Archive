#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair <int, int> pii;

int powermod(int a, int exp, int moder){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

struct poly{
	static const int N = 1000;
	
	int a[N];
	int length, moder;
	
	poly():length(-1), moder(0){memset(a, 0, sizeof(a));}
	poly(int moder):length(-1), moder(moder){memset(a, 0, sizeof(a));}
	
	int &operator [](int sit){return a[sit];}
	
	poly value(int x){
		int ret = 0;
		for (int i = 0, now = 1; i <= length; ++ i){
			ret = (ret + 1ll * a[i] * now) % moder;
			now = 1ll * now * x % moder;
		}
		return ret;
	}
	
	poly operator + (const poly &p)const{
		poly ret(moder);
		ret.length = std::max(length, p.length);
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = a[i] + p.a[i];
			ret.a[i] -= ret.a[i] >= moder ? moder : 0;
		}
		for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
			;
		return ret;
	}
	
	poly operator - ()const{
		poly ret(moder);
		ret.length = length;
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = a[i] ? moder - a[i] : 0;
		}
		return ret;
	}
	
	poly operator - (const poly &p)const{
		poly ret(moder);
		ret.length = std::max(length, p.length);
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = a[i] - p.a[i];
			ret.a[i] -= ret.a[i] < 0 ? moder : 0;
		}
		for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
			;
		return ret;
	}
	
	poly operator * (const poly &p)const{
		poly ret(moder);
		if (!~length || !~p.length) return ret;
		ret.length = length + p.length;
		for (int i = 0; i <= length; ++ i){
			for (int j = 0; j <= p.length; ++ j){
				ret.a[i + j] = (ret.a[i + j] + 1ll * a[i] * p.a[j]) % moder;
			}
		}
		return ret;
	}
	
	poly operator * (const int &p)const{
		poly ret(moder);
		ret.length = length;
		for (int i = 0; i <= ret.length; ++ i){
			ret.a[i] = 1ll * a[i] * p % moder;
		}
		return ret;
	}
	
	poly operator / (const poly &p)const{
		poly ret(moder);
		if (!~p.length) assert(("division by zero!", 0));
		if (length < p.length) return ret;
		ret.length = length - p.length;
		poly aux = *this;
		while (aux.length >= p.length){
			int x = 1ll * aux.a[aux.length] * powermod(p.a[p.length], moder - 2, moder) % moder;
			ret.a[aux.length - p.length] = x;
			for (int j = 0; j <= p.length; ++ j){
				int &u = aux.a[aux.length + j - p.length];
				u = (u - 1ll * x * p.a[j]) % moder;
				u += u < 0 ? moder : 0;
			}
			for ( ; ~aux.length && !aux.a[aux.length]; -- aux.length)
				;
		}
		return ret;
	}
	
	poly operator % (const poly &p)const{
		if (!~p.length) assert(("division by zero!", 0));
		poly ret = p;
		while (ret.length >= p.length){
			int x = 1ll * ret.a[ret.length] * powermod(p.a[p.length], moder - 2, moder) % moder;
			for (int j = 0; j <= p.length; ++ j){
				int &u = ret.a[ret.length + j - p.length];
				u = (u - 1ll * x * p.a[j]) % moder;
				u += u < 0 ? moder : 0;
			}
			for ( ; ~ret.length && !ret.a[ret.length]; -- ret.length)
				;
		}
		return ret;
	}
	
	static poly interpolation(std::vector <pii> vec, int moder){
		int n = vec.size() - 1;
		poly aux(moder); aux.length = 0; aux.a[0] = 1;
		for (int i = 0; i <= n; ++ i){
			poly aux1(moder); aux1.length = 1;
			aux1.a[1] = 1; aux1.a[0] = moder - vec[i].first;
			aux1.a[0] -= aux1.a[0] >= moder ? moder : 0;
			aux = aux * aux1;
		}
		poly ret(moder);
		for (int i = 0; i <= n; ++ i){
			poly aux1(moder); aux1.length = 1;
			aux1.a[1] = 1; aux1.a[0] = moder - vec[i].first;
			aux1.a[0] -= aux1.a[0] >= moder ? moder : 0;
			poly aux2 = aux / aux1;
			int x = 1;
			for (int j = 0; j <= n; ++ j){
				if (i == j) continue;
				x = 1ll * x * (vec[i].first - vec[j].first) % moder;
				x += x < 0 ? moder : 0;
			}
			x = powermod(x, moder - 2, moder);
			ret = ret + (aux2 * x) * vec[i].second;
		}
		return ret;
	}
};

inline int sqr(int n){return n * n;}

int f(int n){
	int ans = 0;
	for (int x = -n; x <= n; ++ x){
		for (int y = -n; y <= n; ++ y){
			int z = sqr(x) + sqr(y);
			if (z <= n){
				for (int i = z; i <= n; ++ i){
					ans += i;
				}
			}
		}
	}
	return ans;
}

const int moder = 1e9 + 7;

int main(){
	printf("%d\n", f(5));
	std::vector <pii> vec;
	for (int i = 1; i <= 30; ++ i){
		int sum = 0;
		for (int j = 1; j <= i; ++ j){
			sum += f(j);
		}
		vec.push_back({i, sum});
	}
	poly p = poly::interpolation(vec, moder);
	printf("%d\n", p.length);
	for (int i = 0; i <= p.length; ++ i){
		printf("%d%c", p[i], " \n"[i == p.length]);
	}
	return 0;
}
