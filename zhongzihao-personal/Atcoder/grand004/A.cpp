#include<bits/stdc++.h>

int main(){
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if (a % 2 == 0 || b % 2 == 0 || c % 2 == 0){
		puts("0");
		return 0;
	}
	printf("%lld\n", std::min(std::min(1ll * a * b, 1ll * b * c), 1ll * a * c));
	return 0;
}
