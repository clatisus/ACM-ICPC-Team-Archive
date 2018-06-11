#include<bits/stdc++.h>

const int N = 210;

int a[N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n << 1; ++ i){
		scanf("%d", &a[i]);
	}
	std::sort(a, a + (n << 1));
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		ans += std::min(a[i << 1], a[i << 1 | 1]);
	}
	return printf("%d\n", ans), 0;
}
