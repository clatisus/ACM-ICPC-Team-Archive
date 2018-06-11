#include<bits/stdc++.h>

const int N = 100010;
const int moder = 1e9 + 7;
typedef long long ll;
typedef std::pair <int, int> pii;

int min[N], phi[N];
ll pre[N];
std::vector <int> prime;
std::map <pii, ll> Hash;
int n, m, p;

ll calc(int n, int m){
	if (!m) return 0;
	if (n == 1) return pre[m];
	if (Hash.count({n, m})){
		return Hash[{n, m}];
	}
	int p = min[n];
	return Hash[{n, m}] = (p - 1) * calc(n / p, m) + calc(n, m / p);
}

int powermod(int a, int exp, int mod){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * a * ret % mod;
		}
		a = 1ll * a * a % mod;
	}
	return ret;
}

int solve(int k, int mod){
	if (mod == 1){
		return 0;
	}
	return powermod(k, solve(k, phi[mod]) + phi[mod], mod);
}

int main(){
	phi[1] = pre[1] = 1;
	for(int i = 2; i < N; ++ i){
		if(!min[i]){
			prime.push_back(i);
			phi[i] = i - 1;
			min[i] = i;
		}
		for(int j = 0, k, sz = (int) prime.size(); j < sz && i * prime[j] < N; ++ j){
			min[k = i * prime[j]] = prime[j];
			if(i % prime[j] == 0){
				phi[k] = phi[i] * prime[j];
				break;
			}
			phi[k] = phi[i] * (prime[j] - 1);
		}
		pre[i] += pre[i - 1] + phi[i];
	}
	for (int i = 2; i <= 20; ++ i){
		for (int j = 1; j < i; ++ j){
			printf("%d %d %d\n", i, j, powermod(j, phi[i], i));
		}
	}
	return 0;
}
