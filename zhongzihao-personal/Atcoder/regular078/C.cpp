#include<bits/stdc++.h>

const int N = 200010;
typedef long long ll;

ll pre[N];
int n;

int main(){
	scanf("%d", &n);
	for (int i = 1, x; i <= n; ++ i){
		scanf("%d", &x);
		pre[i] = pre[i - 1] + x;
	}
	ll ans = LLONG_MAX;
	for (int i = 1; i < n; ++ i){
		ans = std::min(ans, std::abs(pre[i] - (pre[n] - pre[i])));
	}
	return printf("%lld\n", ans), 0;
}
