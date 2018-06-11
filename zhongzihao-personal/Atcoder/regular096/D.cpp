#include<bits/stdc++.h>

typedef long long ll;
const int N = 100010;

ll x[N];
int v[N];
ll clockmax[N], countermax[N];
ll clockmax2[N], countermax2[N];
ll clockpre[N], counterpre[N];

int main(){
	int n;
	ll c;
	scanf("%d%lld", &n, &c);
	for (int i = 1; i <= n; ++ i){
		scanf("%lld%d", &x[i], &v[i]);
	}
	for (int i = 1; i <= n; ++ i){
		clockpre[i] = clockpre[i - 1] + v[i];
		counterpre[i] = counterpre[i - 1] + v[n + 1 - i];
	}
	clockmax[0] = countermax[0] = LLONG_MIN;
	clockmax2[0] = countermax2[0] = LLONG_MIN;
	for (int i = 1; i <= n; ++ i){
		clockmax[i] = std::max(clockmax[i - 1], clockpre[i] - x[i]);
		countermax[i] = std::max(countermax[i - 1], counterpre[i] - (c - x[n + 1 - i]));
		clockmax2[i] = std::max(clockmax2[i - 1], clockpre[i] - 2 * x[i]);
		countermax2[i] = std::max(countermax2[i - 1], counterpre[i] - 2 * (c - x[n + 1 - i]));
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++ i){
		ans = std::max(ans, std::max(clockmax[i], countermax[i]));
	}
	for (int i = 1; i <= n - 1; ++ i){
		ans = std::max(ans, clockmax2[i] + countermax[n - i]);
		ans = std::max(ans, countermax2[i] + clockmax[n - i]);
	}
	printf("%lld\n", ans);
	return 0;
}
