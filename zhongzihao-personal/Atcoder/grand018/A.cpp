#include<bits/stdc++.h>

const int N = 100010;

int n, k;

int main(){
	scanf("%d%d", &n, &k);
	int max = 0, gcd = 0;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		max = std::max(max, x);
		gcd = std::__gcd(gcd, x);
	}
	return printf(!(k % gcd) && k <= max ? "POSSIBLE\n" : "IMPOSSIBLE\n"), 0;
}
