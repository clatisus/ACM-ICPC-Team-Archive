#include<bits/stdc++.h>
#define ll long long

int main(){
	ll a, b;
	scanf("%lld%lld", &a, &b);
	int sit = -1;
	for (int i = 60; ~i; -- i){
		if ((a >> i & 1) != (b >> i & 1)){
			sit = i;
			break;
		}
		else{
			if (a >> i & 1){
				a ^= 1ll << i;
				b ^= 1ll << i;
			}
		}
	}
	if (!~sit){
		return printf("1\n"), 0;
	}
	ll ans = (1ll << sit) - a;
	int sit1 = -1;
	for (int i = sit - 1; ~i; -- i){
		if (b >> i & 1){
			sit1 = i;
			break;
		}
	}
	ll l1 = 1ll << sit, r1 = (1ll << sit) + (1ll << sit1 + 1) - 1;
	ll l2 = 1ll << sit ^ a, r2 = (1ll << sit + 1) - 1;
	ans += r1 - l1 + r2 - l2 + 2;
	if (r1 >= l2){
		ans -= r1 - l2 + 1;
	}
	return printf("%lld\n", ans), 0;
}
