#include<bits/stdc++.h>

const int N = 1000010;
typedef long long ll;
typedef std::pair <ll, int> pli;

int min[N];
std::vector <int> prime;

ll power(ll a, int exp){
	ll ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1) ret *= a;
		a *= a;
	}
	return ret;
}

std::vector <pli> defact(ll n){
	std::vector <pli> ret;
	for (auto u : prime){
		if (n == 1) break;
		if (n % u == 0){
			int cnt = 0;
			while (n % u == 0){
				++ cnt;
				n /= u;
			}
			ret.push_back({u, cnt});
		}
	}
	if (n > 1){
		ret.push_back({n, 1});
	}
	return ret;
}

ll solve(ll d, pli p){
	if (p.first == 2){
		if (!d || d == power(p.first, p.second - 1)){
			return power(p.first, p.second);
		}
		while (!(d & 1)){
			d >>= 1;
		}
		return d % 4 == 3 ? 0 : power(p.first, p.second + 1);
	}
	else if (p.first % 4 == 1){
		if (d){
			int cnt = 0;
			while (d % p.first == 0){
				++ cnt;
				d /= p.first;
			}
			return (cnt + 1) * (p.first - 1) * power(p.first, p.second - 1);
		}
		return power(p.first, p.second) + p.second * (p.first - 1) * power(p.first, p.second - 1);
	}
	else{
		if (!d){
			return power(p.first, p.second >> 1 << 1);
		}
		int cnt = 0;
		while (d % p.first == 0){
			++ cnt;
			d /= p.first;
		}
		if (cnt & 1){
			return 0;
		}
		return power(p.first, p.second - 1) * (p.first + 1);
	}
}

int main(){
	for (int i = 2; i < N; ++ i){
		if (!min[i]){
			min[i] = i;
			prime.push_back(i);
		}
		for (int j = 0, k; j < prime.size() && i * prime[j] < N; ++ j){
			min[k = i * prime[j]] = prime[j];
			if (i % prime[j] == 0){
				break;
			}
		}
	}
	int test;
	scanf("%d", &test);
	while (test --){
		ll n;
		scanf("%lld", &n);
		std::vector <pli> fact = defact(n);
		std::vector <ll> vec;
		for (auto u : fact){
			vec.push_back(power(u.first, u.second));
		}
		int q;
		scanf("%d", &q);
		while (q --){
			ll d;
			scanf("%lld", &d);
			ll ans = 1;
			for (int i = 0, sz = fact.size(); i < sz; ++ i){
				ans *= solve(d % vec[i], fact[i]);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
