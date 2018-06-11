#include<bits/stdc++.h>

const int N = 100010;

int a[N * 3], n;

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n * 3; ++ i){
		scanf("%d", &a[i]);
	}
	std::sort(a, a + 3 * n);
	long long ans = 0;
	for (int i = 3 * n - 2, cnt = 0; i && cnt < n; i -= 2){
		ans += a[i];
		++ cnt;
	}
	return printf("%lld\n", ans), 0;
}
