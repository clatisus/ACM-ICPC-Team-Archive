#include<bits/stdc++.h>

const int N = 2010;
typedef long long ll;

int min[N], a[N];

int main(){
	int n, x;
	scanf("%d%d", &n, &x);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
		min[i] = a[i];
	}
	ll ans = LLONG_MAX;
	for (int i = 0; i < n; ++ i){
		ll sum = 1ll * i * x;
		for (int j = 0; j < n; ++ j){
			sum += min[j];
		}
		ans = std::min(sum, ans);
		for (int j = 0; j < n; ++ j){
			min[j] = std::min(min[j], a[(j - i - 1 + n) % n]);
		}
	}
	printf("%lld\n", ans);
}
