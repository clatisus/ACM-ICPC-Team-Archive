#include<bits/stdc++.h>

typedef long long ll;

ll ans = 0;

void gcd(ll a, ll b){
	if (!b){
		ans -= a;
		return;
	}
	ans += a / b * b << 1;
	gcd(b, a % b);
}

int main(){
	ll n, x;
	scanf("%lld%lld", &n, &x);
	ll y = n - x;
	if (y > x){
		std::swap(x, y);
	}
	gcd(x, y);
	ans += n;
	printf("%lld\n", ans);
	return 0;
}
