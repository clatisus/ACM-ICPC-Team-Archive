#include<bits/stdc++.h>

const int N = 100;

int a[N];
int n, k;

int main(){
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	std::sort(a, a + n);
	int ans = 0;
	for (int i = n - k; i < n; ++ i){
		ans += a[i];
	}
	return printf("%d\n", ans), 0;
}
