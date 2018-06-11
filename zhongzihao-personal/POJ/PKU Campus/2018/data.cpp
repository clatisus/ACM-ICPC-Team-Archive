#include<bits/stdc++.h>

int main(){
	freopen("data.txt", "w", stdout);
	int test = 10;
	printf("%d\n", test);
	for (int i = 0; i < test; ++ i){
		int n = 100000;
		printf("%d\n", n);
		for (int i = 0; i < n; ++ i){
			printf("%d%c", i / (n / 10) + 1, " \n"[i == n - 1]);
		}
		for (int i = 0; i < n - 1; ++ i){
			printf("0%c", " \n"[i == n - 2]);
		}
	}
	return 0;
}
