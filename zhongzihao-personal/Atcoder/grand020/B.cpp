#include<bits/stdc++.h>

typedef long long ll;
const int N = 100010;

int a[N];
int n;

ll calc(ll x){
	for (int i = 0; i < n; ++ i){
		x = x / a[i] * a[i];
	}
	return x;
}

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	ll left = 1, right = 1e15;
	while (left < right){
		ll mid = left + right + 1 >> 1;
		ll x = calc(mid);
		if (x < 2){
			left = mid;
		}
		else{
			right = mid - 1;
		}
	}
	if (calc(left + 1) != 2){
		puts("-1");
		return 0;
	}
	printf("%lld ", left + 1);
	left = 1, right = 1e15;
	while (left < right){
		ll mid = left + right >> 1;
		ll x = calc(mid);
		if (x > 2){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	printf("%lld\n", left - 1);
	return 0;
}
