// 线性筛模板 
// sigma 是约数个数函数 

#include<bits/stdc++.h>

const int N = 1000010;

int min[N], mu[N], phi[N], sigma[N], cnt[N];
std::vector <int> prime;

int main(){
	phi[1] = sigma[1] = mu[1] = 1;
	for (int i = 2; i < N; ++ i){
		if (!min[i]){
			min[i] = i;
			prime.push_back(i);
			sigma[i] = 2;
			phi[i] = i - 1;
			cnt[i] = 1;
			mu[i] = -1;
		}
		for (int j = 0, k, sz = (int) prime.size(); j < sz && i * prime[j] < N; ++ j){
			min[k = i * prime[j]] = prime[j];
			if (i % prime[j] == 0){
				phi[k] = phi[i] * prime[j];
				cnt[k] = cnt[i] + 1;
				sigma[k] = sigma[i] / (cnt[k]) * (cnt[k] + 1);
				mu[k] = 0;
				break;
			}
			phi[k] = phi[i] * (prime[j] - 1);
			sigma[k] = sigma[i] * 2;
			cnt[k] = 1;
			mu[k] = -mu[i];
		}
	}
	return 0;
}
