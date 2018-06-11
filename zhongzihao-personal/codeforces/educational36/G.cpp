#include<bits/stdc++.h>

const int N = 2000010;
const int moder = 1e9 + 7;

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

std::vector <int> prime;
int min[N], mu[N], power[N];
int ans[N];

int main(){
	mu[1] = 1;
	for (int i = 2; i < N; ++ i){
		if (!min[i]){
			min[i] = i;
			prime.push_back(i);
			mu[i] = -1;
		}
		for (int j = 0, k, sz = prime.size(); j < sz && i * prime[j] < N; ++ j){
			min[k = i * prime[j]] = prime[j];
			if (i % prime[j] == 0){
				mu[k] = 0;
				break;
			}
			mu[k] = -mu[i];
		}
	}
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < N; ++ i){
		power[i] = powermod(i, n);
	}
	for (int i = 1; i <= k; ++ i){
		for (int j = 0; j <= k; j += i){
			ans[j] += mu[i] * power[j / i];
			ans[j] -= ans[j] >= moder ? moder : 0;
			ans[j] += ans[j] < 0 ? moder : 0;
			if (j + i < N){
				ans[j + i] -= mu[i] * power[j / i];
				ans[j + i] -= ans[j + i] >= moder ? moder : 0;
				ans[j + i] += ans[j + i] < 0 ? moder : 0;
			}
		}
	}
	for (int i = 1; i < N; ++ i){
		ans[i] += ans[i - 1];
		ans[i] -= ans[i] >= moder ? moder : 0;
	}
	int ret = 0;
	for (int i = 1; i <= k; ++ i){
		ret += ans[i] ^ i;
		ret -= ret >= moder ? moder : 0;
	}
	return printf("%d\n", ret), 0;
}
