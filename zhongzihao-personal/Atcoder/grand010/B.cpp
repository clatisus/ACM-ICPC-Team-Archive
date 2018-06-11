#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

ll n, a[N], cnt[N], pre[N];

int main(){
	scanf("%lld", &n);
	ll sum = 0, one = n * (n + 1) / 2;
	for (int i = 0; i < n; ++ i){
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	if (sum % one){
		return printf("NO\n"), 0;
	}
	ll times = sum / one;
	for (int i = n - 2; i >= 0; -- i){
		ll x = a[i] - (a[n - 1] - times * (n - 1 - i));
		if (x % n){
			return printf("NO\n"), 0;
		}
		cnt[i] = x / n - pre[i + 1];
		if (cnt[i] < 0){
			return printf("NO\n"), 0;
		}
		pre[i] = pre[i + 1] + cnt[i];
	}
	return printf("YES\n"), 0;
}
