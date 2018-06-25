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
	
	int value(int x){
		int ret = 0;
		for (int i = 0, now = 1; i <= length; ++ i){
			ret = (ret + 1ll * a[i] * now) % moder;
			now = 1ll * now * x % moder;
		}
		return ret;
	}
	
	int &operator [](int sit){return a[sit];}
	
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
		for (int i = 0; i <= n; ++ i, ++ aux.length){
            int coe = moder - vec[i].first;
            coe -= coe >= moder ? moder : 0;
            for (int j = aux.length; j >= 0; -- j){
                aux.a[j + 1] += aux.a[j];
                aux.a[j + 1] -= aux.a[j + 1] >= moder ? moder : 0;
                aux.a[j] = 1ll * aux.a[j] * coe % moder;
            }
		}
		poly ret(moder);
		for (int i = 0; i <= n; ++ i){
            int coe = moder - vec[i].first;
            coe -= coe >= moder ? moder : 0;
            int x = 1;
            for (int j = 0; j <= n; ++ j){
                if (i == j) continue;
                x = 1ll * x * (vec[i].first - vec[j].first) % moder;
                x += x < 0 ? moder : 0;
            }
            x = 1ll * powermod(x, moder - 2, moder) * vec[i].second % moder;
            int left = aux.a[aux.length];
            for (int j = aux.length; j; -- j){
                ret.a[j - 1] = (ret.a[j - 1] + 1ll * left * x) % moder;
                left = (aux.a[j - 1] - 1ll * left * coe) % moder;
                left += left < 0 ? moder : 0;
            }
		}
        ret.length = n;
		return ret;
	}
};

int main(){
}
