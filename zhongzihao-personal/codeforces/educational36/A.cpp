#include<bits/stdc++.h>

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	int ans = INT_MAX;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		if (k % x) continue;
		ans = std::min(ans, k / x);
	}
	return printf("%d\n", ans), 0;
}
