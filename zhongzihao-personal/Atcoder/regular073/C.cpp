#include<bits/stdc++.h>

int n, t;

int main(){
	scanf("%d%d", &n, &t);
	int now = 0, ans = 0;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		if (now + t < x){
			ans += t;
		}
		else{
			ans += x - now;
		}
		now = x;
	}
	return printf("%d\n", ans + t), 0;
}
