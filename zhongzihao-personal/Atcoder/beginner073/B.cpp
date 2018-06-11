#include<bits/stdc++.h>

int main(){
	int n;
	scanf("%d", &n);
	int ans = 0;
	for (int i = 0, l, r; i < n; ++ i){
		scanf("%d%d", &l, &r);
		ans += r - l + 1;
	}
	return printf("%d\n", ans), 0;
}
