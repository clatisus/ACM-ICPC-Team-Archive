#include<bits/stdc++.h>

const int N = 100010;
const int M = std::exp(std::log(1e10) / 3) + 10;
typedef std::pair <int, int> pii;
typedef long long ll;

int min[N];
std::vector <int> prime;

inline int sqrt(ll n){
	int x = std::sqrt(n) + 3;
	while (1ll * x * x > n){
		-- x;
	}
	return x;
}

int main(){
	for (int i = 2; i < N; ++ i){
		if (!min[i]){
			min[i] = i;
			prime.push_back(i);
		}
		for (int j = 0, sz = prime.size(); j < sz && prime[j] * i < N; ++ j){
			min[i * prime[j]] = prime[j];
			if (i % prime[j] == 0){
				break;
			}
		}
	}
	std::map <std::vector <pii>, int> Hash;
	int n;
	scanf("%d", &n);
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		ll x;
		scanf("%lld", &x);
		std::vector <int> fact;
		for (auto u : prime){
			if (u > M) break;
			while (x % u == 0){
				x /= u;
				fact.push_back(u);
			}
		}
		if (x != 1){
			int y = sqrt(x);
			if (1ll * y * y == x){
				fact.push_back(y);
				fact.push_back(y);
			}
			else if (x < N && min[x] == x){
				fact.push_back(x);
			}
			else{
				++ ans;
				continue;
			}
		}
		std::vector <pii> vec;
		for (int i = 0, pre = 0, sz = fact.size(); i <= sz; ++ i){
			if (i == sz || fact[i] != fact[i - 1]){
				int y = (i - pre) % 3;
				if (y) vec.push_back({fact[i - 1], y});
				pre = i;
				if (i == sz) break;
			}
		}
		++ Hash[vec];
	}
	auto u = Hash.begin();
	if (!(u -> first).size()){
		++ ans;
		Hash.erase(u);
	}
	while (Hash.size()){
		auto u = Hash.begin();
		std::vector <pii> tmp;
		for (auto v : u -> first){
			tmp.push_back({v.first, 3 - v.second});
		}
		int x = Hash.count(tmp) ? Hash[tmp] : 0;
		ans += std::max(u -> second, x);
		Hash.erase(u);
		Hash.erase(tmp);
	}
	printf("%d\n", ans);
	return 0;
}
