// 中国剩余定理模板
// 求方程组 x = remain1(mod moder1), x = remain2(mod moder2) 的解
// p.crt(q) 返回方程 p, q 的解 

#include<bits/stdc++.h>

typedef long long ll;

// x, y 满足 |x|+|y| 最小 
template <typename T>
T ex_euc(T a, T b, T &x, T &y){
	if (!b){
		x = 1, y = 0;
		return a;
	}
	T ret = ex_euc(b, a % b, x, y), tmp = y;
	y = x - a / b * y;
	x = tmp;
	return ret;
}

template <typename T> 
class modequa{
private:
	T remain, moder;
	
	ll getone(int n)const{return 1;}
	
public:
	modequa <T>(){}
	modequa <T>(T remain, T moder) : remain(remain), moder(moder){}
	T getremain(){return remain;}
	T getmoder(){return moder;}
	
	modequa <T> crt(const modequa <T> &p)const{ // 保证所有运算在 lcm + max(p.moder, moder) 的数据范围内实现，注意不要让模数为 0
		auto one = getone(remain);
		modequa <T> p1 = *this, p2 = p;
		if (p1.moder < p2.moder) std::swap(p1, p2); 
		T x, y;
		T gcd = ex_euc(p1.moder, p2.moder, x, y);
		if ((p2.remain - p1.remain) % gcd) return modequa <T>(0, 0);
		T lcm = p1.moder / gcd * p2.moder;
		T ans = (p2.remain - p1.remain) / gcd;
		ans = one * ans * x % (p2.moder / gcd) * p1.moder;
		ans += p1.remain;
		ans += ans < 0 ? lcm : ans >= lcm ? -lcm : 0;
		return modequa <T>(ans, lcm);
	}
};

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

int main(){
	int a, b, p;
	ll x;
	scanf("%d%d%d%I64d", &a, &b, &p, &x);
	ll ans = 0;
	for (int i = 0; i < p - 1; ++ i){
		int y = 1ll * b * powermod(powermod(a, i, p), p - 2, p) % p;
		modequa <ll> eq1(y, p), eq2(i, p - 1);
		eq1 = eq1.crt(eq2);
		ll moder = eq1.getmoder(), remain = eq1.getremain();
		ans += x / moder;
		ans += remain > 0 && remain <= x % moder;
	}
	printf("%I64d\n", ans);
	return 0;
}
