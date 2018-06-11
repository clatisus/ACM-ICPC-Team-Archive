#include<bits/stdc++.h>

const int N = 5010000;

int min[N], mu[N];
std::vector <int> prime;

int main(){
	for(int i = 2; i < N; ++ i){
		if(!min[i]){
			prime.push_back(i);
			mu[i] = -1;
			min[i] = i;
		}
		for(int j = 0, k, sz = (int)(prime.size()); j < sz && i * prime[j] < N; ++ j){
			min[k = i * prime[j]] = prime[j];
			if(i % prime[j] == 0){
				mu[k] = 0;
				break;
			}
			mu[k] = mu[i] * -1;
		}
	}
	mu[1] = 1;
	for (int i = 2; i < N; ++ i){
		if (min[i] == i){
			continue;
		}
		bool flag = true;
		for (int j = 2; j * j <= i; ++ j){
			if (!(i % j)){
				int x = j + i / j;
				if (min[x - 1] != x - 1){
					flag = false;
					break;
				}
			}
		}
		if (flag){
			std::cout << i + 1 << std::endl;
		}
	}
	return 0;
			
}
