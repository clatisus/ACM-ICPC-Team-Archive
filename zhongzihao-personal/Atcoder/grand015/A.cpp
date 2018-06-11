#include<bits/stdc++.h>

int n, a, b;

int main(){
	scanf("%d%d%d", &n, &a, &b);
	if (a > b){
		return printf("0\n"), 0;
	}
	if (n == 1 && a != b){
		return printf("0\n"), 0;
	}
	return printf("%lld\n", a + 1ll * (n - 1) * b - (b + 1ll * (n - 1) * a) + 1), 0;
}
