#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int a[N], n, A, B;

int main(){
	scanf("%d%d%d", &n, &A, &B);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	ll ans = 0;
	for (int i = 0; i < n - 1; ++ i){
		ans += std::min(1ll * (a[i + 1] - a[i]) * A, 1ll * B);
	}
	printf("%lld\n", ans), 0;
	return 0;
}
