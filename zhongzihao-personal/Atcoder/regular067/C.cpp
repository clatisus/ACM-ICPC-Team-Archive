#include<bits/stdc++.h>

const int N = 1010;
const int moder = 1e9 + 7;

int min[N], n;
std::vector <int> prime;

int main(){
	for (int i = 2; i < N; ++ i){
		if (!min[i]){
			min[i] = i;
			prime.push_back(i);
		}
		for (int j = 0; j < prime.size() && prime[j] <= i; ++ j){
			if (prime[j] * i >= N)
				break;
			min[prime[j] * i] = prime[j];
		}
	}
	scanf("%d", &n);
	int ans = 1;
	for (int i = 0; i < prime.size(); ++ i){
		if (prime[i] > n){
			break;
		}
		int x = n, cnt = 0;
		while (x){
			cnt += x / prime[i];
			x /= prime[i];
		}
		ans = 1ll * ans * (cnt + 1) % moder;
	}
	printf("%d\n", ans);
	return 0;
}
