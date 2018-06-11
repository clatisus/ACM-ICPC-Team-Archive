#include<bits/stdc++.h>

void print(int a, int b){
	for (int i = 0; i < a; ++ i){
		printf("2 ");
	}
	for (int i = 0; i < b; ++ i){
		printf("3 ");
	}
	putchar('\n');
}

int main(){
	int n;
	scanf("%d", &n);
	if (n > 15000){
		int sz = n & 1 ? 14999 : 15000;
		for (int i = 1; i <= sz; ++ i){
			printf("%d ", i << 1);
		}
		for (int j = 0; j < n - sz; ++ j){
			printf("%d ", 6 * j + 3);
		}
		putchar('\n');
		return 0;
	}
	if (n == 3){
		printf("2 5 63\n");
		return 0;
	}
	for (int i = n - 2; ; i -= 2){
		if (i % 3 == 0 || (i + 1) % 3 == 0){
			for (int j = 1; j <= i; ++ j){
				printf("%d ", j << 1);
			}
			for (int j = 0; j < n - i; ++ j){
				printf("%d ", 6 * j + 3);
			}
			return 0;
		}
	}
	return 0;
}
