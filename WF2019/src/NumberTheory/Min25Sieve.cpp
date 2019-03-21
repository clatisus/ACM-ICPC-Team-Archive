//这份模板中，f和g分别是0次函数和1次函数

#include<bits/stdc++.h>

//这里N要尽量开大，至少要比根号n后的一个质数大
const int N = 1000010;
const int moder = (int) 1e9 + 7;
typedef long long ll;
const int inv2 = (moder + 1) >> 1;

int min[N];
std::vector <int> prime;
std::vector <int> preg;

void init(){
	preg.push_back(1);
	for (int i = 2; i < N; ++ i){
		if (!min[i]){
			min[i] = i;
			prime.push_back(i);
			preg.push_back((preg.back() + i) % moder);
		}
		for (int j = 0, sz = prime.size(); j < sz && i * prime[j] < N; ++ j){
			min[i * prime[j]] = prime[j];
			if (i % prime[j] == 0){
				break;
			}
		}
	}
}

int f[N], g[N];
int sqroot;
ll n;

inline int sum0(ll n){return n % moder;}
inline int sum1(ll n){n %= moder; return n * (n + 1) % moder * inv2 % moder;}
inline int getsit(ll x){
	if (x > INT_MAX) return sqroot + n / x;
	return x * x > n ? sqroot + n / x : x;
}

void calcf(){
	sqroot = std::sqrt(n);
	std::vector <ll> vec;
	std::vector <int> id;
	for (ll i = 1, j; i <= n; i = j + 1){
		ll x = n / i;
		int sit = getsit(x);
		j = n / x;
		f[sit] = sum0(x), g[sit] = sum1(x);
		vec.push_back(x);
		id.push_back(sit);
	}
	for (int k = 0, szk = prime.size(); k < szk; ++ k){
		int p = prime[k];
		if (1ll * p * p > n) break;
		for (int i = 0, szi = vec.size(); i < szi; ++ i){
			ll x = vec[i];
			if (x < 1ll * p * p) break;
			int sit = getsit(x / p);
			int &u = f[id[i]];
			u = (u - f[sit] + k + 1) % moder;
			u += u < 0 ? moder : 0;
			int &v = g[id[i]];
			v = (v - 1ll * p * (g[sit] - preg[k])) % moder;
			v += v < 0 ? moder : 0;
		} 
	}
}

int calcsum(ll n, int sit){
	if (prime[sit] > n) return 0;
	int id = getsit(n);
	int ret = (g[id] - f[id] - (preg[sit] - sit - 1)) % moder;
	if (sit == 0) ret += 2;
	for (int i = sit, sz = prime.size(); i < sz; ++ i){
		int p = prime[i];
		ll now1 = p, now2 = 1ll * p * p;
		if (now2 > n) break;
		for (int j = 1; now2 <= n; ++ j, now1 = now2, now2 *= p){
			ret = (ret + 1ll * (p ^ j) * calcsum(n / now1, i + 1) + (p ^ (j + 1))) % moder;
		}
	}
	ret += ret < 0 ? moder : 0;
	return ret;
}

int main(){
	init();
	scanf("%lld", &n);
	calcf();
	int ret = calcsum(n, 0) + 1;
	ret -= ret >= moder ? moder : 0;
	printf("%d\n", ret);
	return 0;
}
