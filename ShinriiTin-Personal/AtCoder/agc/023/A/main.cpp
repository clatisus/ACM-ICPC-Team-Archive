#include <bits/stdc++.h>

using ll = long long;

std::unordered_map<ll, int> map;

int n;

ll ans, s;

int main(){
	scanf("%d", &n);
	map[0] = 1;
	for(int i=1,a;i<=n;++i){
		scanf("%d", &a);
		s += a;
		ans += map[s];
		++ map[s];
	}
	printf("%lld\n", ans);
	return 0;
}
