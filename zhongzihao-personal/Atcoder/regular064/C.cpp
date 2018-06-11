#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int a[N], n, x;

int main(){
	scanf("%d%d", &n, &x);
	for (int i = 0; i < n; ++ i)
		scanf("%d", &a[i]);
	ll ans = 0;
	if (a[0] > x){
		ans = a[0] - x;
		a[0] = x;
	}
	for (int i = 1; i < n; ++ i){
		if (a[i - 1] + a[i] > x){
			ans += a[i - 1] + a[i] - x;
			a[i] = x - a[i - 1];
		}
	}
	printf("%lld", ans);
	return 0;
}
