#include<bits/stdc++.h>

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	int sum = 0;
	for (int i = std::max(n - 1, 2); ; ++ i){
		bool flag = true;
		for (int j = 2; j * j <= i; ++ j){
			if (i % j == 0){
				flag = false;
				break;
			}
		}
		if (flag){
			sum = i;
			break;
		}
	}
	printf("%d %d\n", sum, sum);
	for (int i = 1; i < n; ++ i){
		printf("%d %d %d\n", i, i + 1, i == n - 1 ? sum - (n - 2) : 1);
	}
	int left = m - (n - 1);
	for (int i = 1; i <= n; ++ i){
		for (int j = i + 2; j <= n; ++ j){
			if (!left){
				return 0;
			}
			-- left;
			printf("%d %d %d\n", i, j, 1000000000);
		}
	}
	return 0;
}
