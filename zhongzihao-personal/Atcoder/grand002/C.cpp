#include<bits/stdc++.h>

const int N = 100010;

int a[N];

int main(){
	int n, l;
	scanf("%d%d", &n, &l);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; ++ i){
		if (a[i] + a[i + 1] >= l){
			puts("Possible");
			for (int j = 1; j < i; ++ j){
				printf("%d\n", j);
			}
			for (int j = n - 1; j > i; -- j){
				printf("%d\n", j);
			}
			printf("%d\n", i);
			return 0;
		}
	}
	puts("Impossible");
	return 0;
}
