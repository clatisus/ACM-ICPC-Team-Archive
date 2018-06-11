#include<bits/stdc++.h>

const int N = 100010;
const int moder = 1e9 + 7;

int fac[N];

int main(){
	fac[0] = 1;
	for (int i = 1; i < N; ++ i){
		fac[i] = 1ll * i * fac[i - 1] % moder;
	}
	int n, m;
	scanf("%d%d", &n, &m);
	if (n < m){
		std::swap(n, m);
	}
	if (n == m){
		return printf("%lld\n", 2ll * fac[n] * fac[m] % moder), 0;
	}
	if (n == m + 1){
		return printf("%lld\n", 1ll * fac[n] * fac[m] % moder), 0;
	}
	return printf("0\n"), 0;
}
