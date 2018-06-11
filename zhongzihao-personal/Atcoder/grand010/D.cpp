#include<bits/stdc++.h>

const int N = 100010;

int n, a[N];

bool solve(){
	int even = 0, odd = 0, sit;
	for (int i = 0; i < n; ++ i){
		if (a[i] & 1){
			++ odd;
			sit = i;
		}
		else{
			++ even;
		}
	}
	if (even & 1){
		return true;
	}
	if (odd > 1){
		return false;
	}
	if (a[sit] == 1){
		return false;
	}
	-- a[sit];
	int gcd = std::__gcd(a[0], a[1]);
	for (int i = 2; i < n; ++ i){
		gcd = std::__gcd(gcd, a[i]);
	}
	for (int i = 0; i < n; ++ i){
		a[i] /= gcd;
	}
	return !solve();
}

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	if (n == 1){
		return printf(n == 1 ? "Second\n" : "First\n"), 0;
	}
	return printf(solve() ? "First\n" : "Second\n"), 0;
}
