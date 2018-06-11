#include<bits/stdc++.h>

const int N = 100010;
const int moder = 1e9 + 7;

int powermod(int a, int exp){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

int n;
int a[N], e[N];

int main(){
	scanf("%d", &n);
	int sum = 0;
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		sum += a[i];
	}
	for (int i = 1, max = std::min(N - 1, sum); i <= max; ++ i){
		e[i] = (e[i - 1] + powermod(sum - i + 1, moder - 2)) % moder;
	}
	for (int i = 1, max = std::min(N - 1, sum); i <= max; ++ i){
		e[i] = 1ll * e[i] * (sum - 1) % moder * (sum - i) % moder;
	}
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		ans = (ans + e[a[i]]) % moder;
	}
	return printf("%d\n", ans), 0;
}
