#include<bits/stdc++.h>

typedef long long ll;

struct BigInteger{ // 仅支持非负整数 
	static const int N = 1000;
	static const ll base = 1000000000000000000ll; // 修改它时记得修改输入输出格式 
	ll a[N];
	int length;
	
	BigInteger():length(0){memset(a, 0, sizeof(a));}
	
	BigInteger(ll p){
		memset(a, 0, sizeof(a));
		length = 0;
		if (!p) return;
		for (ll x = std::abs(p); x; x /= base){
			a[length ++] = x % base;
		}
	}
	
	ll &operator [](int sit){return a[sit];}
	
	bool operator < (const BigInteger &q)const{
		if (length != q.length) return length < q.length;
		for (int i = length - 1; ~i; -- i){
			if (a[i] != q.a[i]) return a[i] < q.a[i];
		}
		return false;
	}
	
	BigInteger operator + (const BigInteger &p)const{
		BigInteger ret;
		ret.length = std::max(length, p.length) + 1;
		for (int i = 0; i < ret.length; ++ i){
			ret.a[i] += a[i] + p.a[i];
			if (ret.a[i] >= base) ret.a[i] -= base, ++ ret.a[i + 1];
		}
		for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		return ret;
	}
	
	BigInteger operator - (const BigInteger &p)const{
		BigInteger ret;
		ret.length = length;
		for (int i = 0; i < ret.length; ++ i){
			ret.a[i] += a[i] - p.a[i];
			if (ret.a[i] < 0) ret.a[i] += base, -- ret.a[i + 1];
		}
		for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		return ret;
	}
	
	BigInteger operator * (const BigInteger &p)const{ // 注意长度太长可能会爆 __int128，视情况需要将 18 位调小 
		static __int128 aux[N << 1];
		memset(aux, 0, sizeof(__int128) * (length + p.length));
		for (int i = 0; i < length; ++ i){
			for (int j = 0; j < p.length; ++ j){
				aux[i + j] += (__int128) a[i] * p.a[j];
			}
		}
		BigInteger ret;
		ret.length = p.length + length;
		for (int i = 0; i < ret.length; ++ i){
			aux[i + 1] += aux[i] / base;
			aux[i] %= base;
		}
		for ( ; ret.length && !aux[ret.length - 1]; -- ret.length)
			;
		for (int i = 0; i < ret.length; ++ i) ret.a[i] = aux[i];
		return ret;
	}
	
	BigInteger operator * (ll p)const{
		if (!p) return BigInteger();
		__int128 remain = 0;
		BigInteger ret;
		for (int i = 0; i < length; ++ i){
			remain += (__int128) a[i] * p;
			ret.a[i] = remain % base;
			remain /= base;
		}
		for (ret.length = length, ret.a[ret.length] = remain; ret.a[ret.length]; ++ ret.length){
			ret.a[ret.length + 1] = ret.a[ret.length] / base;
			ret.a[ret.length] %= base;
		}
		for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		return ret;
	}

	BigInteger operator / (ll p)const{
		if (!p) assert(("Division by zero!", 0));
		__int128 remain = 0;
		BigInteger ret;
		for (int i = length - 1; ~i; -- i){
			remain = remain * base + a[i];
			ret.a[i] = remain / p;
			remain %= p;
		}
		for (ret.length = length; ret.length && !ret.a[ret.length - 1]; -- ret.length)
			;
		return ret;
	}
	
	void read(){
		memset(a, 0, sizeof(a));
		length = 0;
		static char s[N * 20];
		scanf("%s", s);
		int len = strlen(s);
		ll now = 1;
		for (int i = len - 1; ~i; -- i){
			a[length] += now * (s[i] - '0');
			if (now * 10 == base){
				now = 1;
				++ length;
			}
			else{
				now *= 10;
			}
		}
		++ length;
		for ( ; length && !a[length - 1]; -- length)
			;
	}
	
	void write(){
		if (!length) return (void) printf("0");
		printf("%I64d", a[length - 1]);
		for (int i = length - 2; ~i; -- i){
			printf("%018I64d", a[i]);
		}
	}
};

int main(){
}
