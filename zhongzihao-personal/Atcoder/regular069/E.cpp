#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int n, a[N];
std::map <int, int> Hash;
std::stack <int> s;
ll ans[N];

int main(){ 
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
		if (s.empty() || a[i] > a[s.top()]){
			s.push(i);
		}
		++ Hash[-a[i]];
	}
	while (!s.empty()){
		int x = s.top();
		s.pop();
		int y = s.empty() ? 0 : -a[s.top()];
		auto u = Hash.begin();
		while (u != Hash.end() && u -> first < y && u -> first){
			ans[x] += 1ll * (y - u -> first) * u -> second;
			Hash[y] += u -> second;
			Hash.erase(u);
			u = Hash.begin();
		}
	}
	for (int i = 1; i <= n; ++ i){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
