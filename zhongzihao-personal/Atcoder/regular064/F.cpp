#include<bits/stdc++.h>

const int N = 3000;
const int moder = 1e9 + 7;

int power_mod(int a, int index){
	int ans = 1;
	while (index){
		if (index & 1)
			ans = 1ll * ans * a % moder;
		a = 1ll * a * a % moder;
		index >>= 1;
	}
	return ans;
}

std::vector <int> fact;
int num[N];

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	int cnt = 0;
	for (int i = 1; i * i <= n; ++ i){
		if (!(n % i)){
			fact.push_back(i);
			fact.push_back(n / i);
		}
	}
	sort(fact.begin(), fact.end());
	fact.erase(unique(fact.begin(), fact.end()), fact.end());
	int ans = 0;
	for (int i = 0; i < fact.size(); ++ i){
		num[i] = power_mod(k, (fact[i] + 1) / 2);
		for (int j = 0; j < i; ++ j){
			if (!(fact[i] % fact[j])){
				num[i] = (num[i] - num[j] + moder) % moder;
			}
		}
		if (fact[i] & 1){
			ans = (ans + 1ll * num[i] * fact[i]) % moder;
		}
		else{
			ans = (ans + 1ll * num[i] * fact[i] % moder * power_mod(2, moder - 2)) % moder;
		}
	}
	printf("%d\n", ans);
	return 0;
}
