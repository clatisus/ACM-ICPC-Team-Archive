#include<bits/stdc++.h>
#define ll long long

int main(){
	ll x;
	scanf("%lld", &x);
	ll moder = x % 11, ans = x / 11;
	if (moder > 6){
		ans = 2 * ans + 2;
	}
	else if (!moder){
		ans *= 2;
	}
	else{
		ans = 2 * ans + 1;
	}
	return printf("%lld\n", ans), 0;
}
