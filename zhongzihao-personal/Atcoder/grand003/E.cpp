#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;
typedef std::pair <ll, int> pii;

ll a[N], b[N];
ll ans[N];

int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	a[1] = n;
	for (int i = 2; i <= q + 1; ++ i){
		scanf("%lld", &a[i]);
	}
	std::set <pii> set;
	for (int i = 0; i <= q + 1; ++ i){
		set.insert({a[i], i});
	}
	int cnt = 0;
	for (int now = 0; ; ){
		b[cnt ++] = a[now];
		auto u = set.upper_bound({a[now], INT_MAX});
		if (u == set.end()) break;
		for (int i = now; i < u -> second; ++ i){
			set.erase({a[i], i});
		}
		now = u -> second;
	}
	std::map <ll, ll, std::greater <ll>> Hash;
	Hash[b[cnt - 1]] = 1;
	while (true){
		auto u = Hash.begin();
		if (u -> first <= b[1]){
			break;
		}
		int sit = std::lower_bound(b + 1, b + cnt, u -> first) - b - 1;
		Hash[b[sit]] += u -> first / b[sit] * u -> second;
		ll y = u -> first % b[sit];
		if (y){
			Hash[y] += u -> second;
		}
		Hash.erase(u);
	}
	for (auto u : Hash){
		ans[u.first] = u.second;
	}
	for (int i = n - 1; i >= 1; -- i){
		ans[i] += ans[i + 1];
	}
	for (int i = 1; i <= n; ++ i){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
