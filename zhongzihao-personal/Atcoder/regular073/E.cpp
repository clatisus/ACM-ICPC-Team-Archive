#include<bits/stdc++.h>
#define ll long long

const int N = 200010;

std::pair <int, int> p[N];
int sufmax[N], sufmin[N];
int n;

ll calc(){
	int max = 0, max1 = 0, min = INT_MAX, min1 = INT_MAX;
	for (int i = 0; i < n; ++ i){
		max = std::max(max, p[i].first);
		max1 = std::max(max1, p[i].second);
		min = std::min(min, p[i].first);
		min1 = std::min(min1, p[i].second);
	}
	return 1ll * (max - min) * (max1 - min1);
}

int main(){
	scanf("%d", &n);
	int max = 0, min = INT_MAX, sit1, sit2;
	for (int i = 0; i < n; ++ i){
		scanf("%d%d", &p[i].second, &p[i].first);
		if (p[i].first > p[i].second){
			std::swap(p[i].first, p[i].second);
		}
	}
	if (n == 1){
		return printf("0\n"), 0;
	}
	ll ans = calc();
	std::sort(p, p + n);
	sufmin[n] = INT_MAX;
	for (int i = n - 1; i >= 0; -- i){
		sufmax[i] = std::max(sufmax[i + 1], p[i].first);
		sufmin[i] = std::min(sufmin[i + 1], p[i].first);
	}
	int nowmax = 0, nowmin = INT_MAX;
	for (int i = 0; i < n; ++ i){
		int x = std::max(nowmax, sufmax[i]), y = std::min(nowmin, sufmin[i]);
		int _x = std::max(std::max(nowmax, p[i].second), sufmax[i + 1]), _y = std::min(std::min(nowmin, p[i].second), sufmin[i + 1]);
		if (_x - _y <= x - y){
			std::swap(p[i].first, p[i].second);
		}
		nowmax = std::max(nowmax, p[i].first);
		nowmin = std::min(nowmin, p[i].first);
	}
	return printf("%lld\n", std::min(calc(), ans)), 0;
}
