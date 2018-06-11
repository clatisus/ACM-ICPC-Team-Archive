#include<bits/stdc++.h>

int powermod(int a, int exp){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret *= a;
		}
		a *= a;
	}
	return ret;
}

int main(){
	int n, exp;
	scanf("%d%d", &n, &exp);
	int ans = 0;
	while (n --){
		int x;
		scanf("%d", &x);
		x = powermod(x, exp);
		ans += x >= 0 ? x : 0;
	}
	printf("%d\n", ans);
	return 0;
}
