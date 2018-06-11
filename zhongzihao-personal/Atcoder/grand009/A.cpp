#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int n, a[N], b[N];

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d%d", &a[i], &b[i]);
	}
	ll ans = 0;
	for (int i = n - 1; i >= 0; -- i){
		ll now = ans + a[i];
		ans += (b[i] - now % b[i]) % b[i];
		
	}
	return printf("%lld\n", ans), 0;
}
