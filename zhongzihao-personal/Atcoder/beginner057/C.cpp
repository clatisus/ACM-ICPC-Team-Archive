#include<bits/stdc++.h>

#define ll long long

ll n;

int main(){
	scanf("%lld", &n);
	int ans = INT_MAX;
	for (ll i = 1; i * i <= n; ++ i){
		if (n % i){
			continue;
		}
		ll x = n / i, y = i;
		int cnt1 = 0, cnt2 = 0;
		while (x){
			++ cnt1;
			x /= 10;
		}
		while (y){
			++ cnt2;
			y /= 10;
		}
		ans = std::min(ans, std::max(cnt1, cnt2));
	}
	return printf("%d\n", ans), 0;
}
