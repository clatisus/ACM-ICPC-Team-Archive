#include<bits/stdc++.h>
#define ll long long

ll max = 0, n, w, w0;
std::vector <ll> vec[10];

void dfs(ll n, ll weight, ll ans){
	if (n == 4){
		if (weight <= w){
			max = std::max(max, ans);
		}
		return;
	}
	ll sum = 0;
	for (ll i = 0, sz = vec[n].size(); i <= sz; ++ i){
		if (i){
			sum += vec[n][i - 1];
		}
		dfs(n + 1, weight + i * (w0 + n), ans + sum);
	}
}

int main(){
	scanf("%lld%lld", &n, &w);
	for (ll i = 0, x, y; i < n; ++ i){
		scanf("%lld%lld", &x, &y);
		if (!i){
			w0 = x;
		}
		vec[x - w0].push_back(y);
	}
	for (ll i = 0; i < 4; ++ i){
		sort(vec[i].begin(), vec[i].end(), std::greater <ll>());
	}
	dfs(0, 0, 0);
	return printf("%lld\n", max), 0;
}
