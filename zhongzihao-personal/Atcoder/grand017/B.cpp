#include<bits/stdc++.h>

typedef long long ll;

int n, a, b, c, d;

int main(){
	scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
	if (a > b){
		std::swap(a, b);
	}
	for (int i = 0; i <= n - 1; ++ i){
		ll left = 1ll * c * i - 1ll * d * (n - 1 - i);
		ll right = 1ll * d * i - 1ll * c * (n - 1 - i);
		if (b - a >= left && b - a <= right){
			return printf("YES\n"), 0;
		}
	}
	return printf("NO\n"), 0;
}
