#include<bits/stdc++.h>
#define ll long long

const int N = 100010;

int a[N * 3];
std::multiset <int> pre, sufbig, sufsmall;
std::vector <int> vec;
int n;

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n * 3; ++ i){
		scanf("%d", &a[i]);
	}
	ll sumpre = 0;
	for (int i = 0; i < n; ++ i){
		pre.insert(a[i]);
		sumpre += a[i];
	}
	for (int i = 0; i < n << 1; ++ i){
		vec.push_back(a[i + n]);
	}
	std::sort(vec.begin(), vec.end());
	ll sumsuf = 0;
	for (int i = 0; i < n; ++ i){
		sufsmall.insert(vec[i]);
		sumsuf += vec[i];
	}
	for (int i = 0; i < n; ++ i){
		sufbig.insert(vec[i + n]);
	}
	ll ans = sumpre - sumsuf;
	for (int i = n; i < n << 1; ++ i){
		if (sufbig.count(a[i])){
			sufbig.erase(sufbig.find(a[i]));
		}
		else{
			sufsmall.erase(sufsmall.find(a[i]));
			sumsuf -= a[i];
			int x = *(sufbig.begin());
			sumsuf += x;
			sufbig.erase(sufbig.begin());
			sufsmall.insert(x);
		}
		pre.insert(a[i]);
		sumpre += a[i];
		auto u = pre.begin();
		sumpre -= *u;
		pre.erase(u);
		ans = std::max(ans, sumpre - sumsuf);
	}
	return printf("%lld\n", ans), 0;
			
}
