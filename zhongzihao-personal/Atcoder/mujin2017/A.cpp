#include<bits/stdc++.h>

const int N = 100010;
const int moder = 1e9 + 7;

int n, a[N];

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf("%d", &a[i]);
	}
	int ans = 1, cnt = 0;
	for (int i = 0, j = 0; i < n; ++ i){
		while (j < n && 2 * j  - 2 * i + 1 <= a[j]){
			++ j;
			++ cnt;
		}
		if (j == n){
			break;
		}
		ans = 1ll * ans * (cnt + 1) % moder;
		-- cnt;
	}
	for (int i = 1; i <= cnt; ++ i){
		ans = 1ll * ans * i % moder;
	}
	return printf("%d\n", ans), 0;
}
