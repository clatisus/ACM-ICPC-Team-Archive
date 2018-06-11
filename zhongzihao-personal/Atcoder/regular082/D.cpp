#include<bits/stdc++.h>

int n;

int main(){
	scanf("%d", &n);
	int pre = 0, ans = 0;
	for (int i = 1, x; i <= n; ++ i){
		scanf("%d", &x);
		if (x != i){
			ans += i - pre >> 1;
			pre = i;
		}
	}
	ans += n + 1 - pre >> 1;
	return printf("%d\n", ans), 0;
}
