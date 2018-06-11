#include<bits/stdc++.h>

int main(){
	int n, x;
	scanf("%d%d", &n, &x);
	if (x == 1 || x == 2 * n - 1){
		puts("No");
		return 0;
	}
	puts("Yes");
	int begin = 1 + (x + n - 1) % (2 * n - 1);
	for (int i = 0; i < 2 * n - 1; ++ i){
		printf("%d\n", begin);
		++ begin;
		begin -= begin > 2 * n - 1 ? 2 * n - 1 : 0;
	}
	return 0;
}
